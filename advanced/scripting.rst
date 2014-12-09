==================
 Python scripting
==================

You can use python script to control the simulation as well.

Following is the example script:

.. code-block:: python
   :linenos:

   import hrpsys
   import commands

   openhrp_dir = commands.getoutput("pkg-config --variable=prefix openhrp3.1")
   model_dir="file://"+openhrp_dir+"/share/OpenHRP-3.1/sample/model/"

   sim = hrpsys.Simulator()
   sim.initViewer()
   box  = sim.loadBody("box",  model_dir+"box.wrl")
   box.rootLink().R = [0,0,0]
   box2 = sim.loadBody("box2", model_dir+"box2.wrl")
   sim.addCollisionCheckPair(box, box2)
   sim.initialize()
   sim.simulate(1.0)

This script will:

* Import hrpsys library (line 1)
* Invoke pkg-config command as a child process to get OpenHRP sample folder (line 4-5)
* Load the simulator (line 7-8)
* Load two box models and set its locations (line 9-11)
* Set collision between the boxes (line 12)
* Initialize and run the simulation for one second time period (line 13-14)
