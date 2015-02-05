====================
 Physics simulation
====================

This tutorial explains how to configure and apply physics simulation in choreonoid.

Configuration
=============

From main menu:

* Create World item (select "File" -> "New..." -> "World").
* Create AISTSimulator item (select "File" -> "New..." -> "AISTSimulator").
* Load model item (select "File" -> "Open..." -> "OpenHRP Model File").

In item panel:

Drag and drop the items to following order (model and simulator item must belong to the world item).

.. image:: physics-config.png


Set initial pose
================

Change the robot to initial pose (see :doc:`kinematics`).

Click "store initial state" button.

.. image:: store-initial.png


Run the simulation
==================

Click "start simulation" button.

.. image:: start-simulation.png
