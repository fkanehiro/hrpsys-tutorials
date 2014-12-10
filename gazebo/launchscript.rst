==========================
 Integrate with ros stack
==========================

Subscription to ros topic in hrpsys-gazebo-simulator can be targeted to any of the topics.

For example, we first setup a pipeline to apply image processing (image undistortion based on the camera parameter) to the original virtual camera input by using "image_proc" ros stack::

  $ ROS_NAMESPACE=simple_vehicle_with_camera/VISION_SENSOR1/left rosrun image_proc image_proc

Then modify the topic name defined in the previous project file from "image_raw" to "image_rect_color":

.. code-block:: xml
   :linenos:

   <?xml version="1.0" encoding="UTF-8" standalone="no"?>
   <grxui>
        ..snip..
        <item class="com.generalrobotix.ui.item.GrxModelItem" name="simple_vehicle_with_camera" select="true" url="model://simple_vehicle_with_camera">
            <property name="isRobot" value="true"/>
            <property name="rtcName" value="vehicle0"/>
            <property name="inport" value="qRef:JOINT_VALUE"/>
            <property name="inport" value="dqRef:JOINT_VELOCITY"/>
            <property name="inport" value="ddqRef:JOINT_ACCELERATION"/>
            <property name="outport" value="q:JOINT_VALUE"/>
            <property name="outport" value="VISION_SENSOR1:/simple_vehicle_with_camera/VISION_SENSOR1/left/image_rect_color:VISION_SENSOR"/>
        </item>
        ..snip..
      </mode>
   </grxui>

Now, we have finished configuring our system. Let's open the project in hrpsys-gazebo-simulator::

  $ hrpsys-gazebo-simulator myproject.xml $HOME/.gazebo/models/simple_vehicle_with_camera.world -endless

