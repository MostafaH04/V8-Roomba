#include "Filter.hpp"

state::state()
{
    positionX = positionY = positionZ = 0;
    velocityX = velocityY = velocityZ = 0;
    q0 = q1 = q2 = q3 = 0;
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
    imuData_1 = imu1->generateNewResult();
    imuData_2 = imu2->generateNewResult();

    updatePrediction();
    propagateUncertainty();
    updateKalmanGain();
    updateErrorState();
    correctState();
    updateCovariance();
}

void Filter::predictPosition(state* imuState, IMU_Data* imuData)
{
    float p_check[3] = {0,0,0};
    float p_prev_x = robot_state->positionX;
    float p_prev_y = robot_state->positionY;
    float p_prev_z = robot_state->positionZ;
}

void Filter::updatePrediction()
{
    // imu1 prediction
    
    // imu2 prediction
}



