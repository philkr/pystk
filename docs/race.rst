.. automodule:: pystk

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



.. autoclass:: Race
   :members:
   :special-members: __init__

SuperTuxKart uses several global variables and thus only allows one game instance to run per process.
To check if there is already a race running use the ``is_running`` function.

.. autofunction:: is_running

.. _race_config:

Configuration
*************

The player configuration is used to add agents to the race.
Each agent can be an AI or player controlled, and produces a separate ``render_data`` output.

.. autoclass:: PlayerConfig
   :members:
   :undoc-members:

The main race configuration specified everything from the track to use, the race type, number of agents and additional AI agents.

.. autoclass:: RaceConfig
   :members:
   :undoc-members:

.. autofunction:: list_tracks

.. autofunction:: list_karts


.. _race_action:

Action
******

The `Race.step` function takes an optional action or list of actions as an input.

.. autoclass:: Action
   :members:
   :special-members: __init__
