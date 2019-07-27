import matplotlib.pyplot as plt
import time
import numpy as np
from pystk import gui
import scipy.ndimage
import PIL

BACKGROUND_LABEL = 4294967295
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600


# pystk.set_log_level(pystk.LogLevel.warn)

def bbox(im):
    a = np.nonzero(im)
    return np.min(a[0]), np.min(a[1]), np.max(a[0]), np.max(a[1])


def bbox_extend(b, px=16):
    return max(b[0] - px, 0), max(b[1] - px, 0), min(b[2] + px, SCREEN_HEIGHT), min(b[3] + px, SCREEN_WIDTH)


cnt = [0] * 20

cats = [None, "kart", "track", "background", "pickup", "nitro", "bomb", "object", "projectile"]


def get_category(o):
    c = o >> 24
    if 0 <= c < len(cats):
        cnt[c] += 1
        return cats[c]


class Timer:
    def __init__(self):
        self.t0 = time.time()
        self.measure = {}

    def start(self):
        self.t0 = time.time()

    def add(self, n):
        if n not in self.measure:
            self.measure[n] = 0
        t1 = time.time()
        self.measure[n] += t1 - self.t0
        self.t0 = t1

    def __str__(self):
        return str(self.measure)

def generate(args):
    import pystk
    config = pystk.GraphicsConfig.hd()
    config.screen_width = SCREEN_WIDTH
    config.screen_height = SCREEN_HEIGHT
    pystk.init(config)

    config = pystk.RaceConfig(num_kart=args.num_karts, laps=1000000, seed=0)
    config.track = args.track_name

    config.players[0].controller = pystk.PlayerConfig.Controller.AI_CONTROL
    config.players[0].kart = np.random.choice(pystk.list_karts())

    k = pystk.SuperTuxKart(config)

    k.start()

    # ui = gui.UI()

    state = pystk.WorldState()
    track = pystk.Track()

    timer = Timer()

    count = {c: 0 for c in cats}
    for t in range(1000000):
        timer.start()
        k.step()
        timer.add('step')
        im = np.asarray(k.render_data[0].image)
        labels = np.asarray(k.render_data[0].instance)
        objects = np.unique(labels)
        timer.add('object_id')
        for o in objects:
            if o > 0:
                cat = get_category(o)
                if cat not in args.valid_cat:
                    continue
                count[cat] += 1
                if count[cat] <= args.num_images:
                    n = count[cat]-1
                else:
                    n = np.random.randint(count[cat])

                timer.add('object select')
                if n < args.num_images:
                    object_mask = labels == o
                    if np.sum(object_mask) < 300:
                        # Ignore small objects
                        count[cat] -= 1
                        timer.add('object cat')
                        continue
                    timer.add('object cat')
                    b = bbox(object_mask)
                    b = bbox_extend(b, args.padding)
                    PIL.Image.fromarray(im[b[0]:b[2], b[1]:b[3], :]).resize((64, 64)).save('hw1_temp/' + args.track_name + '_' + str(args.prefix) + '_' + cat + '_' + str(n) + '.png')
                    timer.add('object save')

        if all([count[k] > args.num_images for k in args.valid_cat]):
            break
        if t % 1000 == 0:
            print(t, count)
    print(t, count)
    print(timer)


if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('track_name')
    parser.add_argument('-n', '--num_images', type=int, default=1000)
    parser.add_argument('-k', '--num_karts', type=int, default=10)
    parser.add_argument('-p', '--padding', type=int, default=4)
    parser.add_argument('-x', '--prefix', default='')
    parser.add_argument('-f', '--valid_cat', nargs='+', default=["kart", "background", "pickup", "nitro", "bomb", "projectile"])
    args = parser.parse_args()

    generate(args)