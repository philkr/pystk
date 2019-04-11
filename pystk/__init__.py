from os import environ, path
if 'SUPERTUXKART_DATADIR' not in environ:
    environ['SUPERTUXKART_DATADIR'] = path.dirname(path.abspath(__file__))
from .pystk_cpp import *
from . import gui
