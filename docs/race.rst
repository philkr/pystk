.. _race:

Race
====

To start a race create a new Race object.
You can configure your race using the ``RaceConfig`` object, see :ref:`race_config`.
You need to set the graphics settings before starting a race, see :ref:`graphics`.

.. code-block:: python

    pystk.init(pystk.GraphicsConfig.hd())

    config = pystk.RaceConfig(track='lighthouse', num_kart=2)
    config.players[0].controller = pystk.PlayerConfig.Controller.AI_CONTROL
    race = pystk.Race(config)
    race.start()

    n_steps = 100
    for step in range(n_steps):
        race.step() # Use an optional action and set controller to pystk.PlayerConfig.Controller.PLAYER_CONTROL
        # Use race.render_data[0].image
        # Use race.render_data[0].depth
        # Use race.render_data[0].instance
    race.stop()
    del race
    # You may start a new race after you delete the old race object
    pystk.clean()

.. include:: auto/race.grst

SuperTuxKart uses several global variables and thus only allows one game instance to run per process.
To check if there is already a race running use the ``is_running`` function.

.. include:: auto/is_running.grst

.. toctree::
   :hidden:
   
   config
   action
   data
   state
