#ifndef ROS_TRANSFORM_PLUGIN_H
#define ROS_TRANSFORM_PLUGIN_H

#include <string>

#include <gazebo/common/common.hh>
#include <gazebo/physics/physics.hh>

#include <ros/ros.h>
#include <geometry_msgs/TransformStamped.h>

#include <boost/shared_ptr.hpp>

namespace gazebo {

  class RosTransformPlugin : public ModelPlugin
  {
  public: 
    void Load(physics::ModelPtr, sdf::ElementPtr);

    void OnUpdate(const common::UpdateInfo&);

    void TransformCallback(geometry_msgs::TransformStamped);

  private: 
    physics::ModelPtr model;
    event::ConnectionPtr updateConnection;

    ros::Subscriber sub;
    boost::shared_ptr<ros::NodeHandle> rosnode;
    std::string transform_topic;
    std::string target_link;

    math::Vector3 translation;
    math::Quaternion rotation;
  };

}

#endif /* end of include guard: ROS_TRANSFORM_PLUGIN_H */