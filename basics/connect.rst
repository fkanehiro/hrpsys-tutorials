=======
Connect
=======

In this tutorial, we will learn how to connect simulation to our own controller.

.. note::

   Please finish :doc:`project` tutorial, before proceed.


Configuration
=============

Before proceed, create configuration file named "rtc.conf" under the current folder (or place it to /etc/rtc.conf if you want to apply the configuration globally) with following content.

.. code-block:: ini
   :linenos:

   corba.nameservers: 127.0.0.1
   naming.formats: %n.rtc
   logger.enable: YES
   logger.log_level: NORMAL
   logger.file_name: stdout
   manager.shutdown_onrtcs: NO
   manager.is_master: YES
   manager.modules.load_path: /usr/lib,/usr/local/lib


Basic structure of project file
===============================

As we have learned in previous tutorial, project file in hrpsys-simulatior is written in xml format. You can use your favorite text editor to create the project file.

Open the project file with your text editor::

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
        ..snip..
      </mode>
   </grxui>

To connect the simulator to the external control process, we will modify **com.generalrobotix.ui.item.GrxRTSItem** configuration item type.

In  **com.generalrobotix.ui.item.GrxRTSItem** configuration item type, the name "*.period" is used to specify execution cycle of each RT-components. The name "*.factory" is used to specify the name of shared library used to create the instance of the component (described later). Properties with name "connection" specify the connection between the components.

Create instance of RT-component
===============================

hrpsys-base is not only a simulation environment, but also provide various components which can be used in your system.

Please refer to this page to see list of all the available components:

http://fkanehiro.github.io/hrpsys-base/

In the previous tutorial, we have configured our project to use "simple_vehicle_with_camera" robot model which has virtual camera interface. In this tutorial, let's use **CameraImageViewer** component to monitor the camera input.

To use the component, we first define the **factory** property to create an instance of the component. In below example, "CameraImageViewer0" is the name of the instance. "CameraImageViewer" is the name of the component itself. We also define the **period** property to set the execution cycle to 0.5 (twice a second).

Then, we also define a connection from "VISION_SENSOR1" port of "vehicle0" robot model to "imageIn" port of "CameraImageViewer0" component instance.

.. code-block:: xml
   :linenos:

   <item class="com.generalrobotix.ui.item.GrxRTSItem" name="untitled" select="true">
      <property name="vehicle0.period" value="0.005"/>
      <property name="CameraImageViewer0.factory" value="CameraImageViewer"/>
      <property name="CameraImageViewer0.period" value="0.5"/>
      <property name="connection" value="vehicle0.VISION_SENSOR1:CameraImageViewer0.imageIn"/>
   </item>

As a result, following system will be generated from this configuration:

.. graphviz::

   digraph foo {
      rankdir=LR
      "vehicle0" -> "CameraImageViewer0" [headlabel="VISION_SENSOR1", taillabel="imageIn", labeldistance=6];
   }

Now, we have finished configuring our system. Let's open the project in hrpsys-simulator::

  $ hrpsys-simulator myproject.xml

Configure behavior of RT-component
==================================

In addition to **CameraImageViewer** component, add following lines to instantiate and connect the **PDController** component.

.. code-block:: xml
   :linenos:

   <item class="com.generalrobotix.ui.item.GrxRTSItem" name="untitled" select="true">
      <property name="vehicle0.period" value="0.005"/>
      <property name="CameraImageViewer0.factory" value="CameraImageViewer"/>
      <property name="CameraImageViewer0.period" value="0.5"/>
      <property name="PDController0.factory" value="PDController"/>
      <property name="PDController0.period" value="0.05"/>
      <property name="connection" value="vehicle0.VISION_SENSOR1:CameraImageViewer0.imageIn"/>
      <property name="connection" value="PDController0.torqueOut:vehicle0.ddqRef"/>
      <property name="connection" value="vehicle0.q:PDController0.angle"/>
   </item>

As a result, following system will be generated from this configuration:

.. graphviz::

   digraph foo {
      rankdir=LR
      edge [minlen=2];
      "PDController0" -> "vehicle0" [headlabel="torqueOut", taillabel="ddqRef", labeldistance=1];
      "vehicle0" -> "PDController0" [headlabel="q", taillabel="angle", labeldistance=1];
      edge [minlen="1"];
      "vehicle0" -> "CameraImageViewer0" [headlabel="VISION_SENSOR1", taillabel="imageIn", labeldistance=6];
   }

**PDController** component will apply PD control to the joint angles of the robot, however in beforehand, we need to adjust the PD parameter match to kinematic character of each robot.
To change the PD parameter, we can use configuration parameter given to RT-component.

.. code-block:: xml
   :linenos:

   <item class="com.generalrobotix.ui.item.GrxRTSItem" name="untitled" select="true">
      <property name="vehicle0.period" value="0.005"/>
      <property name="CameraImageViewer0.factory" value="CameraImageViewer"/>
      <property name="CameraImageViewer0.period" value="0.5"/>
      <property name="PDController0.factory" value="PDController"/>
      <property name="PDController0.period" value="0.05"/>
      <property name="connection" value="vehicle0.VISION_SENSOR1:CameraImageViewer0.imageIn"/>
      <property name="connection" value="PDController0.torqueOut:vehicle0.ddqRef"/>
      <property name="connection" value="vehicle0.q:PDController0.angle"/>
   </item>


Now, we have finished configuring our system. Let's open the project in hrpsys-simulator::

  $ hrpsys-simulator myproject.xml

After the simulator has opened, set a reference parameter to the "angleRef" port of "PDController0" component instance by following rtshell command::

  $ rtinject -c 'RTC.TimedDoubleSeq({time}, [100,100])' /localhost/vehicle0.rtc:ddqRef

