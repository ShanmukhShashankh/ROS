#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

class NumberPublisherNode : public rclcpp::Node{
    private:
        void publishNumber(){
            auto msg = example_interfaces::msg::Int64();
            msg.data = number;
            publisher->publish(msg);
        }

        rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher;
        rclcpp::TimerBase::SharedPtr timer;
        int number = 69;

    public:
        NumberPublisherNode() : Node("number_publisher"){
            publisher = this->create_publisher<example_interfaces::msg::Int64>("number", 10);
            timer = this->create_wall_timer(std::chrono::seconds(2), std::bind(&NumberPublisherNode::publishNumber, this));
            RCLCPP_INFO(this->get_logger(), "Number Publisher Node is succesfully implemented");
        }

};

int main(int argc, char **argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberPublisherNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}