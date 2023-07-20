#ifndef MOTOR_CONTROL_HPP
#define MOTOR_CONTROL_HPP

#include "tim.h"
#include "main.h"

class Motor
{
  private:
    TIM_HandleTypeDef *timer_f, *timer_b;
    unsigned int channel_f, channel_b;
    float speed{0};
  public:
    Motor(TIM_HandleTypeDef *timerF, TIM_HandleTypeDef *timerB,
      unsigned int channelF, unsigned int channelB);
    void init(void);
    void drive(void) const;
    void target(float speed_in);
};

class Chasis
{
  private:
    Motor *right_1, *right_2, *left_1, *left_2;
    double bot_length;
    bool omniDrive;
  public:
    Chasis(double botLen, Motor *r1, Motor *r2, Motor *l1, Motor *l2);
    Chasis(double botLen, Motor *r1, Motor *r2, Motor *l1, Motor *l2, bool omni);
    void init(void);
    void steer(float angular_rate, float speed);
    bool omni_steer(float angle, float speed);
    void drive(void);
};

#endif
