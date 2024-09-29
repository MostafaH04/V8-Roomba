#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
import serial
import struct

from geometry_msgs.msg import Twist
from more_interfaces.msg import Readings

class RoombaController(Node):
    def __init__(self):
        super().__init__("roomba_controller")
        self.controlBuffer = {
            "speed": "",
            "angle": ""
        }

        self.controlSub = self.create_subscription(
            Twist,
            "/roomba/cmd_vel",
            self.controlCallBack,
            10
        )
        self.readingPub_1 = self.create_publisher(
            Readings,
            "/roomba/readings/imu1",
            10
        )
        self.readingPub_2 = self.create_publisher(
            Readings,
            "/roomba/readings/imu2",
            10
        )

        self.timer = self.create_timer(0.001, self.readData)

        self.serPort = serial.Serial("/dev/ttyS0", 115200, timeout=1)
        self.serPort.flushInput()
        self.serPort.flushOutput()
        self.controls = [0, 0, 0, 0, 0, 0]

        self.MAX_BUFFER = 255

        self.buffer_start = 0
        self.buffer_end = 0
        self.buffer_size = 0
        self.buffer = [0]*self.MAX_BUFFER

        self.INCOMING_BYTES = 14

        self.data_pointer = 0
        self.data = [0] * self.INCOMING_BYTES

        self.need_sync = True

        self.get_logger().info("V8-Roomba Comms Controller Initialized")

    def controlCallBack(self, inTwist):
        linear = inTwist.linear
        linearArr = [linear.x, linear.y, linear.z]
        angular = inTwist.angular
        angularArr = [angular.x, angular.y, angular.z]
        self.controls = linearArr + angularArr

        roomba_control_vector = self.controls
        self.serPort.write(b'\xff')
        print(roomba_control_vector)
        for val in roomba_control_vector:
            self.serPort.write(struct.pack('f', val))
            print(struct.pack('f', val))
    

    def readData(self):
        if self.serPort.in_waiting and self.buffer_size < self.MAX_BUFFER:
            temp = self.serPort.read()
            #print(temp)
            if not self.need_sync:
                for i in range(self.INCOMING_BYTES*4):
                    if temp == b'\xff': break
                    self.buffer[self.buffer_end] = temp
                    self.buffer_end = (self.buffer_end + 1) % self.MAX_BUFFER
                    self.buffer_size += 1
                    if i != 55:
                        temp = self.serPort.read()

            if temp == b'\xff' or self.serPort.in_waiting > 60:
                self.need_sync = False
                self.buffer_start = 0
                self.buffer_end = 0
                self.buffer_size = 0
                self.buffer = [0]*self.MAX_BUFFER
                self.data_pointer = 0
                self.data = [0] * self.INCOMING_BYTES
                if self.serPort.in_waiting > 60:
                    self.serPort.flushInput() # YEET we need latest info
                

        while self.buffer_size >= 4 and not self.need_sync:
            data_bytes = []
            for i in range(4):
                data_bytes.append(self.buffer[self.buffer_start])
                self.buffer_start = (self.buffer_start + 1) % self.MAX_BUFFER
                self.buffer_size -= 1
            #print(data_pointer, b''.join(data_bytes))
            self.data[self.data_pointer] = struct.unpack('f', b''.join(data_bytes))
            self.data_pointer += 1
            if self.data_pointer >= self.INCOMING_BYTES:
                self.data_pointer = 0
                need_sync = True
                imu_1_data = Readings()
                
                for i in range(len(self.data)):
                    self.data[i] = self.data[i][0]

                imu_1_data.acc_x = self.data[0]
                imu_1_data.acc_y = self.data[1]
                imu_1_data.acc_z = self.data[2]
                imu_1_data.gyr_x = self.data[3]
                imu_1_data.gyr_y = self.data[4]
                imu_1_data.gyr_z = self.data[5]
                imu_1_data.temp = self.data[6]

                imu_2_data = Readings()
                imu_2_data.acc_x = self.data[7]
                imu_2_data.acc_y = self.data[8]
                imu_2_data.acc_z = self.data[9]
                imu_2_data.gyr_x = self.data[10]
                imu_2_data.gyr_y = self.data[11]
                imu_2_data.gyr_z = self.data[12]
                imu_2_data.temp = self.data[13]

                self.readingPub_1.publish(imu_1_data)
                self.readingPub_2.publish(imu_2_data)
        
def main(args = None):
    rclpy.init(args = args)
    node = RoombaController()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()
