from enum import Flag, auto
from typing import Dict, Set
import numpy as np
import pystk


class VT(Flag):
    """Visualization type"""

    IMAGE = auto()
    DEPTH = auto()
    INSTANCE = auto()
    SEMANTIC = auto()

    @classmethod
    def all(cls):
        return cls.IMAGE | cls.DEPTH | cls.INSTANCE | cls.SEMANTIC

    @classmethod
    def default(cls):
        return cls.all()


class_color = np.array([
    0xffffff,  # None
    0x4e9a06,  # Kart
    0x2e3436,  # Track
    0xeeeeec,  # Background
    0x204a87,  # Pickup
    0xa40000,  # Bomb
    0xce5c00,  # Object
    0x5c3566,  # Projectile
], dtype='>u4').view(np.uint8).reshape((-1, 4))[:, 1:]

instance_color = np.array([
    0xfce94f, 0xedd400, 0xc4a000,
    0xfcaf3e, 0xf57900, 0xce5c00,
    0xe9b96e, 0xc17d11, 0x8f5902,
    0x8ae234, 0x73d216, 0x4e9a06,
    0x729fcf, 0x3465a4, 0x204a87,
    0xad7fa8, 0x75507b, 0x5c3566,
    0xef2929, 0xcc0000, 0xa40000,
    0xeeeeec, 0xd3d7cf, 0xbabdb6,
    0x888a85, 0x555753, 0x2e3436,
], dtype='>u4')
np.random.RandomState(0).shuffle(instance_color)
instance_color = instance_color.view(np.uint8).reshape((-1, 4))[:, 1:]


def _c(i, m):
    return m[i % len(m)]


def semantic_seg(instance):
    return _c((np.array(instance) >> 24) + 1, class_color)


def instance_seg(instance):
    return _c((np.array(instance) + 1) % 0xffffff, instance_color)


class BaseUI:
    visualization_type: VT
    current_action: pystk.Action

    def __init__(self, visualization_type: VT):
        self.visualization_type = visualization_type

    @staticmethod
    def _format_data(render_data: pystk.RenderData) -> Dict[VT, np.array]:
        r = dict()
        r[VT.IMAGE] = render_data.image
        r[VT.DEPTH] = render_data.depth
        r[VT.INSTANCE] = semantic_seg(render_data.instance)
        r[VT.SEMANTIC] = instance_seg(render_data.instance)
        return r

    def _update_action(self, key_state: Set[str]):
        self.current_action.acceleration = int('w' in self._ks or 'up' in self._ks) - int('s' in self._ks or 'down' in self._ks)
        self.current_action.steer = int('a' in self._ks or 'left' in self._ks) - int('d' in self._ks or 'right' in self._ks)
        # TODO: Complete

    def show(self, render_data: pystk.RenderData):
        raise NotImplemented
