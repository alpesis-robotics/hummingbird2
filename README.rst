##############################################################################
HummingBird 2
##############################################################################

==============================================================================
Getting Started
==============================================================================

::

    # install Qt5
    $ export Qt5Core_DIR=/usr/local/opt/qt/lib/cmake/Qt5Core
    $ export Qt5Network_DIR=/usr/local/opt/qt/lib/cmake/Qt5Network
    $ export Qt5Widgets_DIR=/usr/local/opt/qt/lib/cmake/Qt5Widgets

    $ mkdir _build && cd _build
    $ cmake ..
    $ make
    $ ./hummingbird2

Simulator Commands

- ``right click``: choose scenario;
- ``left drag``: rotate;
- ``X + left drag``: pan;
- ``arrow keys``: apply external force;
- ``C``: clear all graphs;
- ``R``: reset simulation;
- ``Space``: pause simulation.

==============================================================================
Codes
==============================================================================

::

    drone-controller/
          +---- images/              scenario images
          +---- config/              configuration files for controller and vehicle
          +---- lib/                 external libraries
          +---- ide/                 IDE configurations
          +---- src/                 codes
          +---- CMakeLists.txt
          +---- README.rst

Function Calls:

::

    main.cpp
       +---- Utility/SimpleConfig.h
       +---- Drawing/Visualizer_GLUT.h
       +                +---- Simulation/QuadDynamics.h
       +                               +---- ControllerFactory.h
       +                                           +---- QuadControl.h
       +                                                       +---- BaseController.h
       +                                                       +          +---- VehicleDatatypes.h
       +                                                       +---- Trajectory.h
       +---- Drawing/GraphManager.h
