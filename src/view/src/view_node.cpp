#include <ros/ros.h>
#include <image_transport/image_transport.h>// 用来发布和订阅图像信息
#include <cv_bridge/cv_bridge.h>// 将ROS下的sensor_msgs/Image消息类型转化为cv::Mat数据类型
#include <sensor_msgs/image_encodings.h> // ROS下对图像进行处理
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>

int main(int argc, char** argv){
  ros::init(argc, argv, "view_node");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("camera/image", 1);
  ros::Rate loop_rate(41);//设置刷新率
  cv::VideoCapture capture;
  capture.open(0);  //打开摄像头，只要一个摄像头，默认是0; 笔记本上有自带的摄像头,再插入usb摄像头应该是1
  if(capture.isOpened()){  
       //打开摄像头
       std::cout<<"video is open"<<std::endl;
  }else{//打开失败
       std::cout<<"video is not open"<<std::endl;
  }
  cv::Mat imageRaw;  // 原始图像保存 
  while (nh.ok()) {
    capture.read(imageRaw);          // 读取当前图像到imageRaw
    cv::imshow("veiwer", imageRaw);  // 将图像输出到窗口
    sensor_msgs::ImagePtr  msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", imageRaw).toImageMsg();  // 图像格式转换
    pub.publish(msg);         // 发布图像信息
    ros::spinOnce();                // 没什么卵用，格式像样
    loop_rate.sleep();              // 照应上面设置的频率
    if(cv::waitKey(2) >= 0)         // 延时ms,按下任何键退出(必须要有waitKey，不然是看不到图像的)
       break;        
  }
  return 0;
}
