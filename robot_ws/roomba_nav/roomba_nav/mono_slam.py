import rclpy
from rclpy.node import Node
import cv2
from sensor_msgs.msg import Image
from cv_bridge import CvBridge

class MonoSlam(Node):

  def __init__(self):
    super().__init__('MonoSlam')
    self.cam_sub = self.create_subscription(
      Image, '/camera/image_raw', self.image_callback, 10)
    self.bridge = CvBridge()
    self.img_buffer = []

  def get_features(self, image):
    orb = cv2.ORB_create(nfeatures = 5000)
    keypoints, descriptors = orb.detectAndCompute(image, None)


  def image_callback(self, msg):
    cv_image = self.bridge.imgmsg_to_cv2(msg, "bgr8")
    gray = cv2.cvtColor(cv_image, cv2.COLOR_BGR2GRAY)
    cv2.imshow("Grayscale", gray)
    cv2.waitKey(1)


def main(args=None):
  rclpy.init(args=args)
  rclpy.spin(MonoSlam())
  rclpy.shutdown()

if __name__ == '__main__':
  main()
