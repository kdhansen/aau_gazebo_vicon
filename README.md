aau_gazebo_vicon
================

Interact with Gazebo through a Vicon system.

A Vicon system provides acurate position estimates of objects in space. This is useful in e.g. control labs,
when prototyping systems like quadcopters. The Vicons system acts like an IMU, so that you don't need to mount
one on your quadcopter.

This package lets you use the Vicon system to set the pose of models in the Gazebo simulator. This makes it
possible to emulate sensors like LIDARs and depth cameras, that is nearly impossible to mount on smaller robots
like quads. Further it lets you repeat sensor stimuli very accurately.

Version 0.1
-----------

The libros_transform.so Gazebo plugin subscribes to a ROS topic with geometry_msgs/TransformStamped messages.
(This is the output of vicon_bridge from ETHZ, which we use.)
