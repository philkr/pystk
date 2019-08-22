.. _graphics:

Graphics Setup
==============

Before you can use pystk you need to setup the OpenGL rendering engine and graphics settings.
There are three default settings ``GraphicsConfig::ld`` (lowest),  ``GraphicsConfig::sd`` (medium),  ``GraphicsConfig::hd`` (high).
Depending on your graphics hardware each setting might perform slightly differently (``ld`` fastest, ``hd`` slowest).
To setup pystk call:

.. code-block:: python

    pystk.init(pystk.GraphicsConfig.hd())
    # Only call init once per process
    ... # use pystk
    pystk.clean() # Optional, will be called atexit
    # Do not call pystk after clean

.. include:: auto/graphicsconfig.grst
