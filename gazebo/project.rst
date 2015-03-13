=======================
Create your own project
=======================

In this tutorial, we will learn how to create your own project.

Project file in hrpsys-gazebo-simulator is written in xml format. You can use your favorite text editor to create the project file.

We will first copy the sample project file to local directory to create our own project::

  $ cp `pkg-config --variable=prefix hrpsys-base`/share/hrpsys/samples/PA10/PA10simulation.xml mysimulation.xml


Convert the robot model and create simulation world
===================================================

hrpsys-gazebo-simulator internally use gazebo simulator, so we can use any robot model distributed in sdf format, but here we will use the same robot model introduced in previous tutorials.
Run following command to convert the robot model and create simulation world::
  
  $ simtrans -i `pkg-config openhrp3.1 --variable=prefix`/share/OpenHRP-3.1/sample/model/simple_vehicle_with_camera.wrl -o $HOME/.gazebo/models/simple_vehicle_with_camera.world


Basic structure of project file
===============================

Open the project file with your favorite text editor::

  $ emacs mysimulation.xml

After the editor is opened, you will see following contents.

.. code-block:: xml
   :linenos:

   <?xml version="1.0" encoding="UTF-8" standalone="no"?>
   <grxui>
      <mode name="Simulation">
        <item class="com.generalrobotix.ui.item.GrxRTSItem" name="untitled" select="true">
            <property name="PA10Controller(Robot)0.period" value="0.005"/>
            <property name="HGcontroller0.period" value="0.005"/>
            <property name="HGcontroller0.factory" value="HGcontroller"/>
            <property name="connection" value="HGcontroller0.qOut:PA10Controller(Robot)0.qRef"/>
            <property name="connection" value="HGcontroller0.dqOut:PA10Controller(Robot)0.dqRef"/>
            <property name="connection" value="HGcontroller0.ddqOut:PA10Controller(Robot)0.ddqRef"/>
        </item>
        <item class="com.generalrobotix.ui.item.GrxModelItem" name="pa10" select="true" url="$(PROJECT_DIR)/../model/PA10/pa10.main.wrl">
            <property name="rtcName" value="PA10Controller(Robot)0"/>
            <property name="inport" value="qRef:JOINT_VALUE"/>
            <property name="inport" value="dqRef:JOINT_VELOCITY"/>
            <property name="inport" value="ddqRef:JOINT_ACCELERATION"/>
            <property name="outport" value="q:JOINT_VALUE"/>
      ..snip..
      </mode>
   </grxui>

Change robot model
==================

In this tutorial, we will use "simple_vehicle_with_camera" robot model which comes from OpenHRP samples.

We first, modify the model name and the url. Edit the following line:

.. code-block:: xml
   :linenos:

   <item class="com.generalrobotix.ui.item.GrxModelItem" name="pa10" select="true" url="$(PROJECT_DIR)/../model/PA10/pa10.main.wrl">

as follows:

.. code-block:: xml
   :linenos:

   <item class="com.generalrobotix.ui.item.GrxModelItem" name="simple_vehicle_with_camera" select="true" url="model://simple_vehicle_with_camera">

Next, we configure each properties applied to the robot model. **rtcName** and **in[out]port** are the properties to create interface for the robot model as a RT-component. For **rtcName**, let's set the value to "vehicle0". For **in[out]port**, just copy the property from the original is fine (these properties mean we can get full position, velocity, acceleration based control interface to the robot).

Specifically for this model, we can also use virtual camera. The final outport definition in below example is for the virtual camera. "/simple_vehicle_with_camera/VISION_SENSOR1/left/image_raw" is the name of the ros topic, which is published by the gazebo-ros plugin. The last "VISION_SENSOR" part specifies the data type.

.. code-block:: xml
   :linenos:

   <item class="com.generalrobotix.ui.item.GrxModelItem" name="simple_vehicle_with_camera" select="true" url="model://simple_vehicle_with_camera">
      <property name="isRobot" value="true"/>
      <property name="rtcName" value="vehicle0"/>
      <property name="inport" value="qRef:JOINT_VALUE"/>
      <property name="inport" value="dqRef:JOINT_VELOCITY"/>
      <property name="inport" value="ddqRef:JOINT_ACCELERATION"/>
      <property name="outport" value="q:JOINT_VALUE"/>
      <property name="outport" value="VISION_SENSOR1:/simple_vehicle_with_camera/VISION_SENSOR1/left/image_raw:VISION_SENSOR"/>
   </item>

Now, we have finished creating our own simulation project. Let's open the project in hrpsys-simulator::

  $ hrpsys-gazebo-simulator mysimulation.xml $HOME/.gazebo/models/simple_vehicle_with_camera.world -endless

In the next tutorial, we will learn how to connect the robot to our own controller.
