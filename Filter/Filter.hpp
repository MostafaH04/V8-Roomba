#ifndef FILTER_HPP
#define FILTER_HPP

#include "Arduino.h"
#include "matmul/matmul.hpp"
#include "../MPU_6050_Driver/MPU_6050_Driver.hpp"

#define grav 9.80665

struct state {
    state();
    float positionX, positionY, positionZ;
    float velocityX, velocityY, velocityZ;
    float q0, q1, q2, q3;
    float uncertainty[9][9];
};

class Filter
{
    private:
        state* robot_state;
        state* imu1_state;
        state* imu2_state;
        state* error_state;
        MPU_6050* imu1;
        MPU_6050* imu2;
        IMU_Data* imuData_1;
        IMU_Data* imuData_2;
        float rotMat1[3][3];
        float rotMat2[3][3];
        float identity[3][3];
        float F_k[9][9];
        float L_k[9][6];
        float covarMat[6][6];
        float Q_k[6][6];
        float K_k; // fix size
        float H_k[3][3]; // fix size
        float R; // fix size
        float delta_t;
        float prev_time;

        void predictPosition(state* imuState, IMU_Data* imuData, float rotMat[3][3]);
    public:
        Filter(MPU_6050* imu1, MPU_6050* imu2);
        void getState(state* e_state, state* r_state); 
        void updateState();
        void updatePrediction();
        void propagateUncertainty();
        void updateKalmanGain();
        void updateErrorState();
        void correctState();
        void updateCovariance();
};

#endif