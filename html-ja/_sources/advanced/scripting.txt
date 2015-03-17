==================
 Python scripting
==================

In the previous tutorials, we have defined our simulation project in xml. But, you can use python script to configure the simulation as well.

Below is the example script:

.. code-block:: python
   :linenos:

   import hrpsys
   import hrpsysext
   import commands

   openhrp_dir = commands.getoutput("pkg-config --variable=prefix openhrp3.1")
   model_dir="file://"+openhrp_dir+"/share/OpenHRP-3.1/sample/model/"

   sim = hrpsysext.Simulator()
   sim.initViewer()
   box  = sim.loadBody("box",  model_dir+"box.wrl")
   box.rootLink().R = [0,0,0]
   box2 = sim.loadBody("box2", model_dir+"box2.wrl")
   sim.addCollisionCheckPair(box, box2)
   sim.initialize()
   sim.simulate(1.0)

This script will:

* Import hrpsys and hrpsysext libraries (line 1-2)
* Invoke pkg-config command as a child process to get OpenHRP sample folder (line 5-6)
* Load the simulator (line 8-9)
* Load two box models and set its locations (line 10-12)
* Set collision between the boxes (line 13)
* Initialize and run the simulation for one second time period (line 14-15)

You can also construct whole the simulation world only by python script:

.. code-block:: python
   :linenos:

   import hrpsys
   import hrpsysext

   sim = hrpsysext.Simulator()
   sim.initViewer()

   body = sim.createBody("body")

   root = body.rootLink()
   s1 = root.addCube(0.2, 1.0, 0.2)
   s1.diffuse = [1,0,0,1]

   child = root.addChildLink("child")
   child.b = [0,0.5,0]
   child.jointType = "rotate"
   child.a = [1,0,0]
   child.m = 1.0
   child.c = [0,0.5,0]
   child.I = [1,0,0,0,1,0,0,0,1]
   s2 = child.addCube(0.5, 1.0, 0.1)
   s2.b = [0,0.5,0]
   s2.diffuse = [0,1,0,1]

   sim.initialize()
   sim.simulate(3)

This script will:

* Import hrpsys and hrpsysext libraries (line 1-2)
* Load the simulator (line 4-5)
* Create the body model by using cube primitive and color it as red (line 7-11)
* Create rotation joint and set each physical properties (line 13-19)
* Create second cube connected to the joint (line 20-22)
* Initialize and run the simulation for three seconds time period (line 24-25)
