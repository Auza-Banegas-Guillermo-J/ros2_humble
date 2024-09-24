#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.h>

#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <geometric_shapes/shape_operations.h>
#include <shape_msgs/msg/solid_primitive.hpp>
#include <moveit_msgs/msg/collision_object.hpp>

int main(int argc, char * argv[])
{
  // Initialize ROS and create the Node
  rclcpp::init(argc, argv);
  auto const node = std::make_shared<rclcpp::Node>(
    "hello_moveit",
    rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true)
  );

  // Create a ROS logger
  auto const logger = rclcpp::get_logger("hello_moveit");

  // Create the MoveGroupInterface
  static const std::string PLANNING_GROUP = "panda_arm";
  moveit::planning_interface::MoveGroupInterface move_group(node, PLANNING_GROUP);

  // Create a PlanningSceneInterface
  moveit::planning_interface::PlanningSceneInterface planning_scene_interface;

  // Define a collision object ROS message
  moveit_msgs::msg::CollisionObject collision_object;
  collision_object.header.frame_id = move_group.getPlanningFrame();
  
  collision_object.id = "box1";

  // Define the primitive and its dimensions
  shape_msgs::msg::SolidPrimitive primitive;
  primitive.type = primitive.BOX;
  primitive.dimensions.resize(3);
  primitive.dimensions[0] = 0.4;  // x size
  primitive.dimensions[1] = 0.1;  // y size
  primitive.dimensions[2] = 0.4;  // z size

  // Define the pose of the box (relative to the robot frame)
  geometry_msgs::msg::Pose box_pose;
  box_pose.orientation.w = 1.0;
  box_pose.position.x = 0.5;
  box_pose.position.y = 0.0;
  box_pose.position.z = 0.2;

  collision_object.primitives.push_back(primitive);
  collision_object.primitive_poses.push_back(box_pose);
  collision_object.operation = collision_object.ADD;

  // Add the collision object to the planning scene
  planning_scene_interface.applyCollisionObject(collision_object);

  // Set a target pose
  geometry_msgs::msg::Pose target_pose;
  target_pose.orientation.w = 1.0;
  target_pose.position.x = 0.35;
  target_pose.position.y = -0.2;
  target_pose.position.z = 0.5;
  move_group.setPoseTarget(target_pose);
  
  // Plan to the target pose
  moveit::planning_interface::MoveGroupInterface::Plan my_plan;
  
  
  geometry_msgs::msg::Pose target_pose_2;
  target_pose_2.orientation.w = 1.0;
  target_pose_2.position.x = -0.1;
  target_pose_2.position.y = 0.25;
  target_pose_2.position.z = 0.3;
  move_group.setPoseTarget(target_pose_2);
  
  moveit::planning_interface::MoveGroupInterface::Plan my_plan_2;

  bool success = (move_group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);

  if (success) {
    RCLCPP_INFO(logger, "Plan successful, executing...");
    move_group.execute(my_plan);
    move_group.execute(my_plan_2);
  } else {
    RCLCPP_ERROR(logger, "Planning failed!");
  }



  // Shutdown ROS
  rclcpp::shutdown();
  return 0;
}