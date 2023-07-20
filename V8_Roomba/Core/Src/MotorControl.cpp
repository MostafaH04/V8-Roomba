#include "MotorControl.hpp"
#include "math.h"
#include "main.h"

Motor::Motor(TIM_HandleTypeDef *timerF, TIM_HandleTypeDef *timerB,
  unsigned int channelF, unsigned int channelB):
  timer_f(timerF), timer_b(timerB), channel_f(channelF), channel_b(channelB)
{}

void Motor::init(void)
{
	 HAL_TIM_PWM_Start(timer_f, channel_f);
	 HAL_TIM_PWM_Start(timer_b, channel_b);
}

void Motor::drive(void) const
{
  TIM_HandleTypeDef *currentTimer;
  unsigned int currentChannel;

  TIM_HandleTypeDef *offTimer;
  unsigned int offChannel;

  if (speed > 0)
  {
	  offTimer = timer_b;
	  offChannel = channel_b;
	  currentTimer = timer_f;
	  currentChannel = channel_f;
  }
  else if (speed <= 0)
  {
    
    currentTimer = timer_b;
    currentChannel = channel_b;
    offTimer = timer_f;
    offChannel = channel_f;
  }

  unsigned int pwm_comp = fabs(speed * 100);
  __HAL_TIM_SET_COMPARE(currentTimer, currentChannel, pwm_comp);
  __HAL_TIM_SET_COMPARE(offTimer, offChannel, 0);

  return;
}

void Motor::target(float speed_in)
{
  if (speed_in > 1)
    speed = 1;
  else if (speed_in < -1)
    speed = -1;
  else
    speed = speed_in;

  return;
}

Chasis::Chasis(double botLen, Motor *r1, Motor *r2, Motor *l1, Motor *l2):
  right_1(r1), right_2(r2), left_1(l1), left_2(l2), bot_length(botLen)
{}

Chasis::Chasis(double botLen, Motor *r1, Motor *r2, Motor *l1, Motor *l2, bool omni):
  right_1(r1), right_2(r2), left_1(l1), left_2(l2), bot_length(botLen),
  omniDrive(omni)
{}

void Chasis::init(void)
{
  right_1->init();
  right_2->init();

  left_1->init();
  left_2->init();
}

void Chasis::steer(float angular_rate, float speed)
{
  // speed = (speed_w1 + speed_w2)/2
  // angular_rate = (speed_w1 - speed_w2)/(2*length_bot)
  speed *= 2;

  float rotFactor = angular_rate * 2 * bot_length;

  float speed_left = (speed + rotFactor)/2;
  float speed_right = speed - speed_left;

  left_1->target(speed_left);
  left_2->target(speed_left);
  
  right_1->target(speed_right);
  right_2->target(speed_right);
}

bool Chasis::omni_steer(float angle, float speed)
{
  if (!omniDrive)
    return false;

  // TODO: impliment omni drive (refer to old code)
  
  return true;
}

void Chasis::drive(void)
{
  right_1->drive();
  right_2->drive();

  left_1->drive();
  left_2->drive();

  return;
}
