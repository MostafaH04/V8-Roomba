#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
import serial

from more_interfaces.msg import Controls
from more_interfaces.msg import Readings

class RoombaController(Node):
    def __init__(self):
        super().__init__("roomba_controller")
        self.controlBuffer = {
            "speed": "",
            "angle": ""
        }

        self.controlSub = self.create_subscription(
            Controls,
            "/roomba/controls",
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

        self.timer = self.create_timer(0.005, self.readData)

        self.serPort = serial.Serial("/dev/ttyS0", 115200, timeout=1)

        self.get_logger().info("V8-Roomba Comms Controller Initialized")

    def controlCallBack(self, control: Controls):
        speedIn = int(Controls.speed*1000)
        speedByte = speedIn.to_bytes(2,"big")

        steeringIn = int(Controls.steering*1000)
        steeringByte = speedIn.to_bytes(2,"big")

        self.controlBuffer['speed'] = speedByte
        self.controlBuffer['angle'] = steeringByte

    def readData(self):
        InfoByte = self.serPort.read()
        Acc1_XByte = self.serPort.read(2)
        Acc1_YByte = self.serPort.read(2)
        Acc1_ZByte = self.serPort.read(2)
        Gyr1_XByte = self.serPort.read(2)
        Gyr1_YByte = self.serPort.read(2)
        Gyr1_ZByte = self.serPort.read(2)

        Acc2_XByte = self.serPort.read(2)
        Acc2_YByte = self.serPort.read(2)
        Acc2_ZByte = self.serPort.read(2)
        Gyr2_XByte = self.serPort.read(2)
        Gyr2_YByte = self.serPort.read(2)
        Gyr2_ZByte = self.serPort.read(2)

        imu1_reading = Readings()
        imu2_reading = Readings()

        imu1_reading.acc_x = float(int.from_bytes(Acc1_XByte, byteorder='big'))/1000
        imu1_reading.acc_y = float(int.from_bytes(Acc1_YByte, byteorder='big'))/1000
        imu1_reading.acc_z = float(int.from_bytes(Acc1_ZByte, byteorder='big'))/1000
        imu1_reading.gyr_x = float(int.from_bytes(Gyr1_XByte, byteorder='big'))/1000
        imu1_reading.gyr_y = float(int.from_bytes(Gyr1_YByte, byteorder='big'))/1000
        imu1_reading.gyr_z = float(int.from_bytes(Gyr1_ZByte, byteorder='big'))/1000

        imu2_reading.acc_x = float(int.from_bytes(Acc2_XByte, byteorder='big'))/1000
        imu2_reading.acc_y = float(int.from_bytes(Acc2_YByte, byteorder='big'))/1000
        imu2_reading.acc_z = float(int.from_bytes(Acc2_ZByte, byteorder='big'))/1000
        imu2_reading.gyr_x = float(int.from_bytes(Gyr2_XByte, byteorder='big'))/1000
        imu2_reading.gyr_y = float(int.from_bytes(Gyr2_YByte, byteorder='big'))/1000
        imu2_reading.gyr_z = float(int.from_bytes(Gyr2_ZByte, byteorder='big'))/1000

        self.get_logger().info("Sending")

        self.serPort.write((255).to_bytes(1,'big'))
        self.serPort.write((self.controlBuffer['angle']))
        self.serPort.write((self.controlBuffer['speed']))

        self.readingPub_1.publish(imu1_reading)
        self.readingPub_2.publish(imu2_reading)
        
def main(args = None):
    rclpy.init(args = args)
    node = RoombaController()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()