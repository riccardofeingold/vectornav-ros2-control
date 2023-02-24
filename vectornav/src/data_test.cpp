#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "vectornav_msgs/msg/common_group.hpp"

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
  public:
    MinimalSubscriber()
    : Node("minimal_subscriber")
    {
      subscription_ = this->create_subscription<vectornav_msgs::msg::CommonGroup>(
      "vectornav/raw/common", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
    }

  private:
    void topic_callback(const vectornav_msgs::msg::CommonGroup & msg) const
    {
      RCLCPP_INFO(this->get_logger(), "I heard: '%f'", msg.imu_accel.x);
    }
    rclcpp::Subscription<vectornav_msgs::msg::CommonGroup>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}