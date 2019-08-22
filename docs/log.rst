.. _logging:

Logging
=======

.. automodule:: pystk
   :noindex:

PySTK uses a global logging mechanism.
You can select one of the log levels below.

.. autoclass:: LogLevel
   :members:
   :undoc-members:

.. autofunction:: set_log_level

You may also set the log level through an environment variable ``PYSTK_LOG_LEVEL`` using a string corresponding to the log level.
