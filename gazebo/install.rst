=========
 Install
=========

Install using ppa (recommended)
===============================

.. code-block:: bash

   $ sudo add-apt-repository ppa:hrg/daily
   $ sudo apt-get update
   $ sudo apt-get install hrpsys-base-gazebo

Install from source
===================

.. warning::

   Source based installation is hard way.
   ppa based installation is highly recommended.

To install from source, we first need to install depending hrpsys-base with libraries.
Please refer to :doc:`../basics/install` for details.

Clone most recent source from github.

.. code-block:: bash

   $ git clone https://github.com/fkanehiro/hrpsys-base-gazebo.git

Then, run cmake and make to configure, compile and install.

.. code-block:: bash

   $ cd hrpsys-base-gazebo
   $ cmake .
   $ make
   $ sudo make install
