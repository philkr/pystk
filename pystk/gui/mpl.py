from .base import *
import matplotlib.pyplot as plt
from typing import Dict, Set
import pystk


class MplUI(BaseUI):
    _ax: Dict[VT, plt.Axes]
    _fig: plt.Figure
    _ks: Set[str]

    def __init__(self, visualization_type: VT = VT.default(), hide_menu=True):
        super().__init__(visualization_type)

        n_vis = sum([t in visualization_type for t in VT])
        print(n_vis)

        self._fig = plt.figure()
        self._ax = {}
        k = 1
        for t in VT:
            if t in visualization_type:
                self._ax[t] = self._fig.add_subplot(2, n_vis//2, k)
                self._ax[t].axis('off')
                k += 1
        self._fig.tight_layout(pad=0)
        self._fig.subplots_adjust(left=0, bottom=0, right=1, top=1, wspace=0, hspace=0)

        if hide_menu:
            self._fig.canvas.toolbar.pack_forget()

        # Add the keyboard handling
        self._ks = set()
        self._fig.canvas.mpl_connect('key_press_event', self._key_press)
        self._fig.canvas.mpl_connect('key_release_event', self._key_release)
        self._fig.canvas.mpl_connect('figure_enter_event', lambda *a, **ka: self._ks.clear())
        self._fig.canvas.mpl_connect('figure_enter_event', lambda *a, **ka: self._ks.clear())
        # disable the default keys
        self._fig.canvas.mpl_disconnect(self._fig.canvas.manager.key_press_handler_id)

    def _set_action(self):
        super()._update_action(self._ks)

    def _key_press(self, e):
        self._ks.add(e.key)
        self._set_action()
        return True

    def _key_release(self, e):
        self._ks.remove(e.key)
        self._set_action()
        return True

    def show(self, render_data: pystk.RenderData):
        data = self._format_data(render_data)
        for t, a in self._ax.items():
            d = data[t]
            if hasattr(a, '_im'):
                a._im.set_data(d)
            else:
                a._im = a.imshow(d)

        self._fig.canvas.draw()
        self._fig.canvas.flush_events()

        plt.pause(1e-8)


if __name__ == "__main__":
    ui = MplUI()
