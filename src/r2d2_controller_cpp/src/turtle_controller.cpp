#include "rclcpp/rclcpp.hpp"
#include "turtlesim/msg/pose.hpp"
#include "turtlesim/srv/set_pen.hpp"
#include "geometry_msgs/msg/twist.hpp"

class TurtleControllerNode : public rclcpp::Node{
    public:
        TurtleControllerNode() : Node("turtle_controller"){
            publisher = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
            pose_subscriber = this->create_subscription<turtlesim::msg::Pose>("/turtle1/pose", 10, std::bind(&TurtleControllerNode::pose_callback, this, std::placeholders::_1));
            RCLCPP_INFO(this->get_logger(), "Turtle Controller Started!");
        }

    private:
        void pose_callback(const turtlesim::msg::Pose::SharedPtr pose){
            auto cmd = geometry_msgs::msg::Twist();
            if(pose->x > 9.0 || pose->x < 2.0 || pose->y > 9.0 || pose->y < 2.0){
                cmd.linear.x = 3.0;
                cmd.angular.z = 3.0;
            }
            else{
                cmd.linear.x = 5.0;
                cmd.angular.z = 0.0;
            }
            publisher->publish(cmd);

            if((pose->x < 5.5 && previous_x >= 5.5 && pose->y >= 5.5) || (pose->x < 5.5 && pose->y >=5.5 && previous_y < 5.5)){
                previous_x = pose->x;
                previous_y = pose->y;
                RCLCPP_INFO(this->get_logger(), "Set Color to Red");
                this->call_set_pen_service(255,0,0,3,0);
            }
            else if((pose->x >= 5.5 && previous_x < 5.5 && pose->y >= 5.5) || (pose->x >= 5.5 && pose->y >= 5.5 && previous_y < 5.5)){
                previous_x = pose->x;
                previous_y = pose->y;
                RCLCPP_INFO(this->get_logger(), "Set Color to Green");
                this->call_set_pen_service(0,255,0,3,0);
            }
            else if((pose->x < 5.5 && previous_x >= 5.5 && pose->y < 5.5) || (pose->x < 5.5 && pose->y < 5.5 && previous_y >= 5.5)){
                previous_x = pose->x;
                previous_y = pose->y;
                RCLCPP_INFO(this->get_logger(), "Set Color to Blue");
                this->call_set_pen_service(0,0,255,3,0);
            }
            else if((pose->x >= 5.5 && previous_x < 5.5 && pose->y < 5.5) || (pose->x >= 5.5 && pose->y < 5.5 && previous_y >=5.5)){
                previous_x = pose->x;
                previous_y = pose->y;
                RCLCPP_INFO(this->get_logger(), "Set Color to Yellow");
                this->call_set_pen_service(255,255,0,3,0);
            }
        }

        void call_set_pen_service(int r, int g, int b, int width, int off){
            auto client = this->create_client<turtlesim::srv::SetPen>("/turtle1/set_pen");
            while(!client->wait_for_service(std::chrono::seconds(1))){
                RCLCPP_WARN(this->get_logger(), "Waiting for the service...");
            } 

            auto request = std::make_shared<turtlesim::srv::SetPen::Request>();
            request->r = r;
            request->g = g;
            request->b = b;
            request->width = width;
            request->off = off;

            auto future = client->async_send_request(request);
            try{
            }
            catch(const std::exception &e){
                RCLCPP_ERROR(this->get_logger(), "Service call failed: %s", e.what());
            }
        }
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher;
        rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr pose_subscriber;
        float previous_x=0;
        float previous_y=0;
};

int main(int argc, char **argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtleControllerNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}