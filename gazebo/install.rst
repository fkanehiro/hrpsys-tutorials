=========
 Install
=========

Install from source
===================

To install from source, we first need to install depending hrpsys-base with libraries.

.. code-block:: bash

   $ sudo add-apt-repository ppa:hrg/daily
   $ sudo apt-get update
   $ sudo apt-get install hrpsys-base libsdl1.2-dev

We also need to install gazebo.
Please refer to following page for installation of gazebo with DRC plugins and models:

https://bitbucket.org/osrf/drcsim/wiki/DRC/Install

.. code-block:: bash

   $ sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu trusty main" > /etc/apt/sources.list.d/ros-latest.list'
   $ sudo sh -c 'echo "deb http://packages.osrfoundation.org/drc/ubuntu trusty main" > /etc/apt/sources.list.d/drc-latest.list'
   $ wget http://packages.ros.org/ros.key -O - | sudo apt-key add -
   $ wget http://packages.osrfoundation.org/drc.key -O - | sudo apt-key add -
   $ sudo apt-get update
   $ sudo apt-get install drcsim

Clone most recent source from github.

.. code-block:: bash

   $ git clone https://github.com/fkanehiro/hrpsys-gazebo-simulator.git

Then, run cmake and make to configure, compile and install.

.. code-block:: bash

   $ cd hrpsys-gazebo-simulator
   $ cmake .
   $ make
   $ sudo make install
