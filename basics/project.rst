=======================
Create your own project
=======================

In this tutorial, we will learn how to create your own project.

Project file in hrpsys-simulatior is written in xml format. You can use your favorite text editor to create the project file.

We will first copy the sample project file to create our own project::

  $ cp `pkg-config --variable=prefix hrpsys-base`/share/hrpsys/samples/PA10/PA10simulation.xml mysimulation.xml

Open the project file with your text editor (just want to share my love with emacs ;))::

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
hrpsys-simulator currently has following configuration items:

com.generalrobotix.ui.item.GrxRTSItem
    Defines initialization and connection of RT-components.

com.generalrobotix.ui.item.GrxModelItem
    Defines robot model and initial attitude.

com.generalrobotix.ui.item.GrxWorldStateItem
    Defines physics simulation parameters.

com.generalrobotix.ui.item.GrxPythonScriptItem
    Defines python script to be run behind the simulation.

com.generalrobotix.ui.view.Grx3DView
    Defines initial view angle and visualization.

There are some other configuration item types such as com.generalrobotix.ui.grxui.GrxUIPerspectiveFactory. These are the legacy item types used in eclipse based OpenHRP simulator. These items are kept for compatibility and has no effect to hrpsys-simulator.

Change robot model
==================

In this tutorial, we will use "simple_vehicle_with_camera" model which comes from OpenHRP samples.

We first, modify the model name and the url. Edit the following line:

.. code-block:: xml
   :linenos:

   <item class="com.generalrobotix.ui.item.GrxModelItem" name="pa10" select="true" url="$(PROJECT_DIR)/../model/PA10/pa10.main.wrl">

as follows:

.. code-block:: xml
   :linenos:

   <item class="com.generalrobotix.ui.item.GrxModelItem" name="vehicle" select="true" url="$(PROJECT_DIR)/../model/simple_vehicle_with_camera.wrl">


"$(PROJECT_DIR)" will be replaced with the place you have installed OpenHRP sample project (usually /usr/local/share/OpenHRP-3.1/samples/project).

Next, we

.. code-block:: xml
   :linenos:

   <item class="com.generalrobotix.ui.item.GrxModelItem" name="vehicle" select="true" url="$(PROJECT_DIR)/../model/simple_vehicle_with_camera.wrl">
      <property name="rtcName" value="PA10Controller(Robot)0"/>
      <property name="inport" value="qRef:JOINT_VALUE"/>
      <property name="inport" value="dqRef:JOINT_VELOCITY"/>
      <property name="inport" value="ddqRef:JOINT_ACCELERATION"/>
      <property name="outport" value="q:JOINT_VALUE"/>
   </item>
