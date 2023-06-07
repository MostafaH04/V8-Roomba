#include "Filter.hpp"
#include "matmul/matmul.cpp"

state::state()
{
    positionX = positionY = positionZ = 0;
    velocityX = velocityY = velocityZ = 0;
    q1 = q2 = q3 = 0;
    q0 = 1;
}

Filter::Filter(MPU_6050* imu1, MPU_6050* imu2)
{
    robot_state = new state();
    error_state = new state();

    imu1_state = new state();
    imu2_state = new state();

    imu1 = imu1;
    imu2 = imu2;
    delta_t = 0;
    prev_time = millis() * 1000; 
}

void Filter::getState(state* e_state, state* r_state)
{
    e_state = error_state;
    r_state = robot_state;
}

void Filter::updateState()
{
    float curr_time = millis();
    delta_t = curr_time * 1000 - prev_time;
    prev_time = curr_time;
    IMU_Data* imuData_1_temp = imu1->generateNewResult();
    IMU_Data* imuData_2_temp = imu2->generateNewResult();

    updatePrediction();
    propagateUncertainty();
    updateKalmanGain();
    updateErrorState();
    correctState();
    updateCovariance();
    
    imuData_1 = imuData_1_temp;
    imuData_2 = imuData_2_temp;
}

void rotMatCalc(float rotMat[3][3], float q[4])
{
    float identity[3][3];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            identity[i][j] = 0;
            if (i == j)
            {
                identity[i][j] = 1;
            }
        }
    }

    //q_w^2 - q_v.T @ q_v
    float q_w = q[0];
    float q_v[3] = {q[1],q[2],q[3]};

    float qvT_qv = 0;
    for (unsigned int i = 0; i < 3; i++)
    {
        qvT_qv += q[i] * q[i];
    }
    
    float term_1[3][3];
    scalarMult3_3(identity, q_w * q_w - qvT_qv, term_1);

    float term_2_temp[3][3];
    float term_2[3][3];
    vecMultTranspose_3(q_v,term_2_temp);
    scalarMult3_3(term_2, 2, term_2);

    float skew_qv[3][3];
    skewSymetric(q_v, skew_qv);
    float term_3[3][3];
    scalarMult3_3(skew_qv, q_w * 2, term_3);
    addMat(term_1, term_2);
    addMat(term_1, term_3);

    rotMat = term_1;
}

void ohm(float q[4], float ohmMat [4][4])
{
    float identity[4][4];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            identity[i][j] = 0;
            if (i == j)
            {
                identity[i][j] = 1;
            }
        }
    }

    float q_w = q[0];
    float q_v[3] = {q[1],q[2],q[3]};

    float term_1[4][4];
    scalarMult4_4(identity, q_w, term_1);

    float skew_qv[3][3];
    skewSymetric(q_v, skew_qv);
    float term_2[4][4];
    term_2[0][0] = 0;
    for (int i = 1; i < 4; i++)
    {
        term_2[0][i] = -q_v[i-1];
        term_2[i][0] = q_v[i-1];
        for (int j = 1; j < 4; j++)
        {
            term_2[i][j] = skew_qv[i-1][j-1];
        }
    }
    addMat_4(term_1, term_2);
    ohmMat = term_1;
}   

void quaternionCalc(float omega[3], float delta_t, float q[4])
{
    float theta[3];
    float thetaMag;
    for (int i = 0; i < 3; i++)
    {
        theta[i] = omega[i] * delta_t;
        thetaMag += theta[i] * theta[i];
    }
    thetaMag = pow(thetaMag, (1/2));
    
    q[0] = cos(thetaMag / 2);

    for (int i = 0; i < 3; i++)
    {
        q[i+1] = theta[i]/thetaMag * sin(thetaMag / 2);
    }
}

void Filter::predictPosition(state* imuState, IMU_Data* imuData, float rotMat[3][3])
{
    float p_check[3] = {0,0,0};
    float p_prev[3] = {0};
    p_prev[0] = robot_state->positionX;
    p_prev[1] = robot_state->positionY;
    p_prev[2] = robot_state->positionZ;

    float v_check[3] = {0,0,0};
    float v_prev[3] = {0};
    v_prev[0] = robot_state->velocityX;
    v_prev[1] = robot_state->velocityY;
    v_prev[2] = robot_state->velocityZ;    
    
    float q_check[4] = {1,0,0,0};
    float q_prev[4] = {0};
    q_prev[0] = robot_state->q0;
    q_prev[1] = robot_state->q1;
    q_prev[2] = robot_state->q2;
    q_prev[3] = robot_state->q3;
    
    float g[3] = {0, 0, grav};
    float f_k[3] = {imuData->AccX, imuData->AccY, imuData->AccZ};
    float omega_k[3] = {imuData->GyroX, imuData->GyroY, imuData->GyroZ};
    quaternionCalc(omega_k, delta_t, q_check);
    float ohmMat[4][4];
    ohm(q_check, ohmMat);
    matVecMult_4(ohmMat, q_prev,q_check); 

    // orientation prediction
    imuState->q0 = q_check[0];
    imuState->q1 = q_check[1];
    imuState->q2 = q_check[2];
    imuState->q3 = q_check[3];

    rotMatCalc(rotMat, q_check);
    float rotatedForce[3];
    matVecMult_3(rotMat, f_k, rotatedForce);

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            F_k[i][j] = 0;
            if (i == j)
                F_k[i][j] = 1;
        }
    }

    float subF_k[3][3];
    float skewRotatedForce[3][3];
    skewSymetric(rotatedForce, skewRotatedForce);
    scalarMult3_3(skewRotatedForce, -delta_t, subF_k);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3 ; j++)
        {
            F_k[i][j+3] = 0;
            if (i == j)
                F_k[i][j+3] = delta_t;

            F_k[i+3][j+6] = subF_k[i][j];
        }
    }

    for (int i = 0; i < 3; i ++)
    {
        p_check[i] = p_prev[i] + v_prev[i] * delta_t + delta_t * delta_t / 2 * (rotatedForce[i] + g[i]);
        v_check[i] = v_prev[i] + delta_t * (rotatedForce[i] + g[i]);
    }

    imuState->positionX = p_check[0];
    imuState->positionY = p_check[1];
    imuState->positionZ = p_check[2];

    imuState->velocityX = v_check[0];
    imuState->velocityY = v_check[1];
    imuState->velocityZ = v_check[2];

}

void Filter::updatePrediction()
{
    // imu1 prediction
    predictPosition(imu1_state, imuData_1, rotMat1);
    // imu2 prediction
    predictPosition(imu2_state, imuData_2, rotMat2);
}



