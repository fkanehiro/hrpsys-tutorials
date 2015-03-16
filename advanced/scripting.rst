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

* Import hrpsys library (line 1)
* Invoke pkg-config command as a child process to get OpenHRP sample folder (line 4-5)
* Load the simulator (line 7-8)
* Load two box models and set its locations (line 9-11)
* Set collision between the boxes (line 12)
* Initialize and run the simulation for one second time period (line 13-14)

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

* Import hrpsys library (line 1)
* Load the simulator (line 3-4)
* Create the body model by using cube primitive and color it as red (line 6-10)
* Create rotation joint and set each physical properties (line 12-18)
* Create second cube connected to the joint (line 19-21)
* Initialize and run the simulation for three seconds time period (line 23-24)
