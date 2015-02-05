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
Please refer to following page for installation of gazebo itself:

http://gazebosim.org/tutorials?tut=install_ubuntu&cat=installation

Or refer to this page to install gazebo with DRC plugins and models:

https://bitbucket.org/osrf/drcsim/wiki/DRC/Install

Clone most recent source from github.

.. code-block:: bash

   $ git clone https://github.com/fkanehiro/hrpsys-base-gazebo.git

Then, run cmake and make to configure, compile and install.

.. code-block:: bash

   $ cd hrpsys-base-gazebo
   $ cmake .
   $ make
   $ sudo make install
