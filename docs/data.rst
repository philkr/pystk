.. automodule:: pystk

.. _data:

Data
====

.. autoclass:: RenderData
   :members:
   :special-members: __init__

Each instance label is spit into an ``ObjectType`` and instance label.
Right shift (``>>``) the instance label by ``ObjectType.object_type_shift`` to retrieve the object type.


.. autoclass:: ObjectType
   :members:
   :undoc-members:

   .. attribute:: object_type_shift

      Number of bits for the instance label (shift of the object type)
