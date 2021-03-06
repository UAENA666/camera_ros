namespace galaxy_camera {
    class GalaxyCamera {
    public:
        GalaxyCamera(const ros::NodeHandle &nh,
                     image_transport::CameraPublisher &pub,
                     sensor_msgs::CameraInfo info,
                     uint32_t height, uint32_t width, uint32_t step,
                     uint32_t offset_x, uint32_t offset_y,
                     const std::string &encoding);

        ~GalaxyCamera();

        static sensor_msgs::Image image_;

    private:

        void writeConfig();

        GX_DEV_HANDLE dev_handle_;

        int last_channel_ = 0;
        ros::NodeHandle nh_;

        static char *img;
        static image_transport::CameraPublisher pub_;
        static sensor_msgs::CameraInfo info_;

        static void GX_STDC onFrameCB(GX_FRAME_CALLBACK_PARAM *pFrame);

    };
}
