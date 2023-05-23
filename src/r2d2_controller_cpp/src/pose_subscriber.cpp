#include "rclcpp/rclcpp.hpp"
#include "turtlesim/msg/pose.hpp"

class PoseSubscriberNode : public rclcpp::Node{
    private:
        void pose_callback(const turtlesim::msg::Pose::SharedPtr msg){
            RCLCPP_INFO(this->get_logger(),"(%f, %f)", msg->x, msg->y);
        }
        rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr pose_subscriber;

    public:
        PoseSubscriberNode():Node("pose_subscriber"){
            pose_subscriber = this->create_subscription<turtlesim::msg::Pose>("/turtle1/pose", 10, std::bind(&PoseSubscriberNode::pose_callback, this, std::placeholders::_1));
            RCLCPP_INFO(this->get_logger(), "The Subscriber has been successfully initialised");
        }
};

int main(int argc, char **argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PoseSubscriberNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}