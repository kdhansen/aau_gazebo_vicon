#include "ros_transform_gazebo_plugin/ros_transform_gazebo_plugin.h"

namespace gazebo
{   
  void RosTransformPlugin::Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf) 
  {
    // Store the pointer to the model
    model = _parent;

    // Get ros transform topic and target link from the model .sdf file.
    transform_topic = "/transform";
    if (!_sdf->HasElement("transformTopic"))
    {
      ROS_WARN("RosTransformPlugin plugin missing <transformTopic>, "
          "defaults to \"%s\"",
          transform_topic.c_str());
    }
    else
    {
      transform_topic = _sdf->GetElement("transformTopic")->Get<std::string>();
    }

    target_link = "link";
    if (!_sdf->HasElement("targetLink"))
    {
      ROS_WARN("RosTransformPlugin plugin missing <targetLink>, "
          "defaults to \"%s\"",
          target_link.c_str());
    }
    else
    {
      target_link = _sdf->GetElement("targetLink")->Get<std::string>();
    }

    ROS_INFO_STREAM("Connected to topic: " << transform_topic << " and link: " << target_link);

    // Make sure the ROS node for Gazebo has already been initialized                                                                                    
    if (!ros::isInitialized())
    {
      ROS_FATAL_STREAM("A ROS node for Gazebo has not been initialized, unable to load plugin. "
        << "Load the Gazebo system plugin 'libgazebo_ros_api_plugin.so' in the gazebo_ros package)");
      return;
    }
    rosnode.reset(new ros::NodeHandle());

    // Listen to the update event. This event is broadcast every
    // simulation iteration.
    this->updateConnection = event::Events::ConnectWorldUpdateBegin(
        boost::bind(&RosTransformPlugin::OnUpdate, this, _1));

    // Subscribe to the ros topic
    sub = rosnode->subscribe<geometry_msgs::TransformStamped>(transform_topic, 1, &RosTransformPlugin::TransformCallback, this);
  }

  // Called by the world update start event
  void RosTransformPlugin::OnUpdate(const common::UpdateInfo & _info)
  {
    this->model->SetLinkWorldPose(math::Pose(translation, rotation), target_link);
  }

  // Called when new transform message arrives.
  void RosTransformPlugin::TransformCallback(geometry_msgs::TransformStamped msg)
  {
    translation.x = msg.transform.translation.x;
    translation.y = msg.transform.translation.y;
    translation.z = msg.transform.translation.z;
    rotation.x = msg.transform.rotation.x;
    rotation.y = msg.transform.rotation.y;
    rotation.z = msg.transform.rotation.z;
    rotation.w = msg.transform.rotation.w;
    return;
  }

  // Register this plugin with the simulator
  GZ_REGISTER_MODEL_PLUGIN(RosTransformPlugin)
}