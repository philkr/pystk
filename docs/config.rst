.. _race_config:

Configuration
-------------

.. automodule:: pystk
   :noindex:

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

