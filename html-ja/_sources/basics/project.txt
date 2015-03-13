=======================
Create your own project
=======================

In this tutorial, we will learn how to create your own project.

Project file in hrpsys-simulatior is written in xml format. You can use your favorite text editor to create the project file.

We will first copy the sample project file to local directory to create our own project::

  $ cp `pkg-config --variable=prefix hrpsys-base`/share/hrpsys/samples/PA10/PA10simulation.xml mysimulation.xml

Open the project file with your favorite text editor (here, we use emacs)::

  $ emacs mysimulation.xml


Basic structure of project file
===============================

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

To create our simulation project, we have to edit each configuration items.
Each types of configuration items are distinguished with **class attributes**.
hrpsys-simulator currently has following configuration item types:

com.generalrobotix.ui.item.GrxRTSItem
    Defines initialization and connection of RT-components.

com.generalrobotix.ui.item.GrxModelItem
    Defines robot model and initial attitudes.

com.generalrobotix.ui.item.GrxWorldStateItem
    Defines physics simulation parameters.

com.generalrobotix.ui.item.GrxPythonScriptItem
    Defines python script to be run behind the simulation.

com.generalrobotix.ui.view.Grx3DView
    Defines initial view angle and visualization settings.

There are some other configuration item types such as com.generalrobotix.ui.grxui.GrxUIPerspectiveFactory. These are the legacy item types used in previous eclipse based OpenHRP simulator. These items are kept for compatibility reason and has no effect to hrpsys-simulator.

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

   <item class="com.generalrobotix.ui.item.GrxModelItem" name="vehicle0" select="true" url="$(PROJECT_DIR)/../model/simple_vehicle_with_camera.wrl">


"$(PROJECT_DIR)" will be replaced with the place you have installed OpenHRP sample project (usually under /usr/local/share/OpenHRP-3.1/samples/project directory).

Next, we configure each properties applied to the robot model. **rtcName** and **in[out]port** are the properties to create interface for the robot model as a RT-component. For **rtcName**, let's set the value to "vehicle0". For **in[out]port**, just copy the property from the original is fine (these properties mean we can get full position, velocity, acceleration based control interface to the robot).

Specifically for this model, we can also use virtual camera. The final outport definition in below example is for the virtual camera. "VISION_SENSOR1" is the name for the virtual camera, which should be correspond to the name defined in the model file. The last "VISION_SENSOR" part specifies the data type.

The final "BODY.translation" part specifies the position of the robot model in the simulation world.

.. code-block:: xml
   :linenos:

   <item class="com.generalrobotix.ui.item.GrxModelItem" name="vehicle0" select="true" url="$(PROJECT_DIR)/../model/simple_vehicle_with_camera.wrl">
      <property name="isRobot" value="true"/>
      <property name="rtcName" value="vehicle0"/>
      <property name="inport" value="qRef:JOINT_VALUE"/>
      <property name="inport" value="dqRef:JOINT_VELOCITY"/>
      <property name="inport" value="ddqRef:JOINT_ACCELERATION"/>
      <property name="outport" value="q:JOINT_VALUE"/>
      <property name="outport" value="VISION_SENSOR1:VISION_SENSOR1:VISION_SENSOR"/>
      <property name="BODY.translation" value="0.0 0.0 0.2"/>
   </item>

Now, we have finished creating our own simulation project. Let's open the project in hrpsys-simulator::

  $ hrpsys-simulator mysimulation.xml -showsensors

Can you see the robot in the world? You have probably seen empty world! In fact, we had to create a floor to support our vehicle to stay within our sight.

Please add following lines to the project file:

.. code-block:: xml
   :linenos:
   :emphasize-lines: 11-18

   <item class="com.generalrobotix.ui.item.GrxModelItem" name="vehicle0" select="true" url="$(PROJECT_DIR)/../model/simple_vehicle_with_camera.wrl">
      <property name="isRobot" value="true"/>
      <property name="rtcName" value="vehicle0"/>
      <property name="inport" value="qRef:JOINT_VALUE"/>
      <property name="inport" value="dqRef:JOINT_VELOCITY"/>
      <property name="inport" value="ddqRef:JOINT_ACCELERATION"/>
      <property name="outport" value="q:JOINT_VALUE"/>
      <property name="outport" value="VISION_SENSOR1:VISION_SENSOR1:VISION_SENSOR"/>
      <property name="BODY.translation" value="0.0 0.0 0.2"/>
   </item>
   <item class="com.generalrobotix.ui.item.GrxModelItem" name="longfloor" select="true" url="$(PROJECT_DIR)/../model/longfloor.wrl">
      <property name="isRobot" value="false"/>
      <property name="WAIST.translation" value="0.0 0.0 -0.1 "/>
   </item>
   <item class="com.generalrobotix.ui.item.GrxCollisionPairItem" name="CP#floor#vehicle0" select="true">
      <property name="objectName2" value="vehicle0"/>
      <property name="objectName1" value="longfloor"/>
   </item>

Now, let's open the project in hrpsys-simulator::

  $ hrpsys-simulator mysimulation.xml -showsensors

In the next tutorial, we will learn how to connect the robot to our own controller.
