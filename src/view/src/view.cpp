#include <ros/ros.h>
#include <image_transport/image_transport.h>// 用来发布和订阅图像信息
#include <cv_bridge/cv_bridge.h>// 将ROS下的sensor_msgs/Image消息类型转化为cv::Mat数据类型
#include <sensor_msgs/image_encodings.h> // ROS下对图像进行处理
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <camera_info_manager/camera_info_manager.h>
#include "GxIAPI.h"
#include "DxImageProc.h"
#include "ViewImage.h"


int main(int argc, char** argv){
  ros::init(argc,argv,"view_node");
  ros::NodeHandle nh_;
  image_transport::CameraPublisher image_pub_;
  boost::shared_ptr<camera_info_manager::CameraInfoManager> info_;
  galaxy_camera::GalaxyCamera *galaxy_camera_;
  std::string camera_name_, camera_info_url_, pixel_format_;
  int image_width_, image_height_, image_offset_x_, image_offset_y_;

  image_transport::ImageTransport it(nh_);
  image_pub_ = it.advertiseCamera("DAHENG/image_raw", 1);
  nh_.param("camera_frame_id", galaxy_camera::GalaxyCamera::image_.header.frame_id, std::string("pitch_camera"));
  nh_.param("camera_name", camera_name_, std::string("pitch_camera"));
  nh_.param("camera_info_url", camera_info_url_, std::string(""));
  nh_.param("image_width", image_width_, 1920);
  nh_.param("image_height", image_height_, 1200);
  nh_.param("image_offset_x", image_offset_x_, 0);
  nh_.param("image_offset_y", image_offset_y_, 0);
  nh_.param("pixel_format", pixel_format_, std::string("bgr8"));
  info_.reset(new camera_info_manager::CameraInfoManager(nh_, camera_name_, camera_info_url_));
  galaxy_camera::GalaxyCamera galaxy_camera(nh_,image_pub_, info_->getCameraInfo(),
                             image_height_, image_width_, image_width_ * 3,image_offset_x_, image_offset_y_, pixel_format_);
  ros::spin();
  return 0;
}
