=========================
Run your first simulation
=========================

hrpsys-gazebo-simulator command
===============================

The hrpsys-gazebo-simulator command loads and runs a simulation. It is called like follows::
  
  $ hrpsys-gazebo-simulator [project file] [gazebo world file] [options]

Where **project file** is the xml file which defines system configuration (explained later).
**gazebo world file** is the xml file which defines simulation world.

The hrpsys-gazebo-simulator command has following options:

.. program:: hrpsys-gazebo-simulator

.. option:: -nodisplay

   Headless mode.

.. option:: -realtime
   
   Synchronize to real world time.

.. option:: -endless

   Endless mode.

.. option:: -h --help

   Show help message.

Running sample project
======================

Run following command to convert the robot model and create simulation world::
  
  $ simtrans -i `pkg-config openhrp3.1 --variable=prefix`/share/OpenHRP-3.1/sample/model/PA10/pa10.main.wrl -o $HOME/.gazebo/models/pa10.world

For project file, copy from hrpsys samples::

  $ cp `pkg-config --variable=prefix hrpsys-base`/share/hrpsys/samples/PA10/PA10simulation.xml mysimulation.xml

Before running the simulation, open new terminal and run roscore service::

  $ roscore

Open the project and simulation world in hrpsys-gazebo-simulator::

  $ hrpsys-gazebo-simulator mysimulation.xml $HOME/.gazebo/models/pa10.world -endless


Interact with the simulation window
===================================

Simulation window is just as same as the gazebo.

To translate the simulation world **left click and drag**.

You can rotate the simulation world by **shift key + left click and drag**.

.. image:: main-window.png
