=======
Install
=======

Install using ppa (recommended)
===============================

.. code-block:: bash

   $ sudo add-apt-repository ppa:hrg/ppa
   $ sudo apt-get update
   $ sudo apt-get install hrpsys-base

Install from source
===================

.. warning::

   Source based installation is hard way.
   ppa based installation is highly recommended.

To install from source, we first need to install depending libraries.

.. code-block:: bash

   $ sudo apt-get install git jython libxml2-dev libsdl-dev libcv-dev libcvaux-dev libhighgui-dev libqhull-dev libglew-dev freeglut3-dev libxmu-dev python-dev libboost-python-dev ipython

Clone most recent source from github.

.. code-block:: bash

   $ git clone https://github.com/fkanehiro/hrpsys-base.git

Then, run cmake and make to configure, compile and install.

.. code-block:: bash

   $ cd hrpsys-base
   $ cmake .
   $ make
   $ sudo make install
