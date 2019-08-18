from .base import VT, class_color, instance_color, NoUI

try:
    from . import mpl as _mlp
    UI = _mlp.MplUI
except ImportError:
    UI = NoUI
