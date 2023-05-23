#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

class DrawCircleNode : public rclcpp::Node{
    public:
        DrawCircleNode() : Node("draw_circle"){
            publisher = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel",10);
            timer = this->create_wall_timer(std::chrono::milliseconds(500),
                                            std::bind(&DrawCircleNode::sendVel, this));
            RCLCPP_INFO(this->get_logger(), "Draw Circle node is started");
        }

    private:
        void sendVel(){
            auto msg = geometry_msgs::msg::Twist();
            msg.linear.x = 4.0;
            msg.angular.z = 2.0;
            publisher->publish(msg);
        }
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher;
        rclcpp::TimerBase::SharedPtr timer;
};

int main(int argc, char **argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<DrawCircleNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}