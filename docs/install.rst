Installation
============

Using pip
---------

.. code-block:: bash

   pip install pystk

From source
-----------

.. code-block:: bash

   python setup.py build
   python setup.py install


Development
-----------

For easier development, it is recommended to install pystk directly through ``cmake``.

.. code-block:: bash

   mkdir build
   cd build
   cmake ..
   make

CMake will place a copy of the library in the top level directly, with allows any examples to run from that directory.
Make sure the fetch the game assets, if they don't already exist.

.. code-block:: bash

   python setup.py fetch_data


Documentation
-------------

.. code-block:: bash

   cd docs
   make html

