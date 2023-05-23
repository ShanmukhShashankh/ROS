#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"

class NumberCounterNode : public rclcpp::Node{
    private:
        void callback(const example_interfaces::msg::Int64::SharedPtr msg){
            int new_msg = msg->data;
            RCLCPP_INFO(this->get_logger(), "%d", new_msg);
            counter++;
            auto number = example_interfaces::msg::Int64();
            number.data = counter;
            publisher->publish(number);
        }

        rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscriber;
        rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher;
        int counter=0;

    public:
        NumberCounterNode() : Node("number_counter"){
            subscriber = this->create_subscription<example_interfaces::msg::Int64>("number", 10, std::bind(&NumberCounterNode::callback, this, std::placeholders::_1));
            publisher = this->create_publisher<example_interfaces::msg::Int64>("number_count", 10);
            RCLCPP_INFO(this->get_logger(), "Number Counter node is succesfully implemented");
        }

};

int main(int argc, char **argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberCounterNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}