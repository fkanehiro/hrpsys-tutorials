=========
 Install
=========

Install using ppa (recommended)
===============================

.. code-block:: bash

   $ sudo add-apt-repository ppa:hrg/ppa
   $ sudo apt-get update
   $ sudo apt-get install choreonoid

Install from source
===================

.. warning::

   Source based installation is hard way.
   ppa based installation is highly recommended.

Clone most recent source from github.

.. code-block:: bash

   $ git clone https://github.com/s-nakaoka/choreonoid.git

Install depending libraries.

.. code-block:: bash

   $ cd choreonoid
   $ ./misc/script/install-requisites-ubuntu-14.04.sh

Then, run cmake and make to configure, compile and install.

.. code-block:: bash

   $ cmake .
   $ make
   $ sudo make install
