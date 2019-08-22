Python SuperTuxKart
===================

This is a heavily modified version of the free SuperTuxKart_ racing game for sensorimotor control experiments.

.. _SuperTuxKart: https://github.com/supertuxkart/stk-code

Many parts that make SuperTuxKart fun and entertaining to play were removed, and replaced with a highly efficient and customizable python interface to the game.
The python interface supports the full rendering engine and all assets of the original game, but no longer contains any sound playback, networking, or user interface.

If you find a bug in this version of supertuxkart please do not report it to the original project, this project significantly diverged from the original intention of the video game.

Hardware Requirements
---------------------

To run SuperTuxKart, make sure that your computer's specifications are equal or higher than the following specifications:

 * A graphics card capable of 3D rendering - NVIDIA GeForce 8 series and newer (GeForce 8100 or newer), AMD/ATI Radeon HD 4000 series and newer, Intel HD Graphics 3000 and newer. OpenGL >= 3.3
 * You should have a CPU that's running at 1 GHz or faster. 
 * You'll need at least 512 MB of free VRAM (video memory).
 * Minimum disk space: 800 MB 


License
-------

The software is released under the GNU General Public License (GPL).
Information about the licenses for the artwork is contained in ``data/licenses``.


.. toctree::
   :maxdepth: 2
   :caption: The Basics
   :hidden:

   install
   start

.. toctree::
   :maxdepth: 2
   :caption: Advanced Topics
   :hidden:

   setup
   race
   log
