=======
Install
=======

Install using ppa (recommended)
===============================

.. code-block:: bash

   $ sudo add-apt-repository ppa:hrg/daily
   $ sudo apt-get update
   $ sudo apt-get install hrpsys-base

Install from source
===================

.. warning::

   Source based installation is hard way.
   ppa based installation is highly recommended.

To install from source, we first need to install depending libraries.

.. code-block:: bash

   $ sudo apt-get install git jython doxygen ipython cmake libxml2-dev libsdl-dev libcv-dev libcvaux-dev libhighgui-dev libqhull-dev libglew-dev freeglut3-dev libxmu-dev python-dev libboost-python-dev libboost-thread-dev libboost-program-options-dev libboost-signals-dev libboost-regex-dev liblapack-dev libopencv-dev liblas-dev libeigen3-dev

Clone most recent source from github.

.. code-block:: bash

   $ git clone https://github.com/fkanehiro/hrpsys-base.git

Then, run cmake and make to configure, compile and install.

.. code-block:: bash

   $ cd hrpsys-base
   $ cmake .
   $ make
   $ sudo make install
