Installation
============

Using pip
---------

.. code-block:: bash

   pip install PySuperTuxKart

From source
-----------

.. code-block:: bash

   python setup.py build
   python setup.py install


Development
-----------

Clone the repository `https://github.com/philkr/pystk <https://github.com/philkr/pystk>`_.
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

PySTK does not compile on `readthedocs.org <http://readthedocs.org>`_ due to some missing dependencies.
This means that autodoc does not work there. In order to circumvent this, the autodoc parts of the documentation are split off and can be built using

.. code-block:: bash

   make rst

Make sure to build the html again after.
