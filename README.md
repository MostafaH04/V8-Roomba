# Autonomous-Cleaning-Robot (V8-Roomba)🧹🚨

![image](https://media.discordapp.net/attachments/1034262061577945100/1148242776849391616/image.png?width=400&height=300)
![image](https://media.discordapp.net/attachments/779417429126152203/1152750586933026817/Untitled_Diagram.drawio_3.png?width=2296&height=1184)

## Introduction
V8-Roomba is an autonomous cleaning robot project that is currently under development. It currently uses 4 geared DC motors controlled by 2 L298N motor drivers, 2 MPU6050 6-Axis IMUs used to estimate the robot's position and a Raspberry Pi 3A+ running ROS Humble which is also connected to the onboard camera used for monocular vSLAM.

## Scope
**Hardware**: Designed the chassis in AutoCAD to be laser cut out of acrylic along with 3D printed mounts for the electronics and motors designed in Solidworks. For low level control an STM32F411 (blackpill) is used, and interfaces with 2 MPU6050 sensors over I2C, and handles 8 different PWM outputs to control each of the 4 motors'. The STM32F411 interfaces with the onboard Raspberry Pi 3A+ using UART, transmitting IMU measurements, and receiving steering and speed commands. Lastly, the Raspberry Pi is connected to a small camera at the front of the chassis, mounted using a quick snap design.

**Software**: Programmed low level drivers to interface with the onboard MPU6050 sensors using the HAL I2C library, and a differential drive motor controller that converts speed and angular velocity to individual motor speeds communicated through PWM signals to the onboard motor drivers. Furthermore, the Raspberry Pi is running ROS Humble, most notably running a node that publishes IMU readings for each IMU to a respective topic on the ROS network, while subscribing to the controls topic on the ROS network to send these controls to the MCU. This allows me to use my computer to subscribe and publish to these topics through ROS running on a VM.

## Constraints
The main constraints for the project is budget. The project started off as a simple robot car that would use ultrasonic sensors to avoid obstacles, then expanded over time as the budget and my knowledge increased. Moving towards using CV for pose estimation, and now using ROS and attempting to implement vSLAM and incorporate some of the concepts I have learned from the Coursera Northwestern University Modern Robotics and UofT Self Driving Car Specializations.

More over, as the budget continues to grow as I continue to work on this project, I have plans to incorporate a LIDAR sensor to further the robot's navigational stack.

Lastly, at the current stages I am yet to design / attach a vacuuming system. Funny to see a Roomba that doesn't vacuum I know 😅. However, I am planning on tackling that once I have a formidable autonomy system as I envision that to be by far the easiest portion of this project.
