import matplotlib.pyplot as plt
import time
import numpy as np
from pystk import gui
import scipy.ndimage
import png
import os
import PIL
import json

SCREEN_WIDTH = 320
SCREEN_HEIGHT = 240


def write_png16(x, filename):
    with open(filename, 'wb') as f:
        writer = png.Writer(width=x.shape[1], height=x.shape[0], bitdepth=16, greyscale=True)
        writer.write(f, x.tolist())


def project(P, V, x):
    X = np.ones(4)
    X[:3] = x
    px = P.T @ V.T @ X
    px /= px[-1]
    return (px[0] + 1) * SCREEN_WIDTH / 2, (1 - px[1]) * SCREEN_HEIGHT / 2, (px[2] + 1) / 2


def generate(args):
    os.system('mkdir -p data_temp/%s' % args.split)
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

    state = pystk.WorldState()
    track = pystk.Track()
    track.update()

    cnt = 0
    for t in range(args.num_images):
        for i in range(15):
            k.step()
        k.step()
        state.update()


        im = np.array(k.render_data[0].image)

        depth = np.array(k.render_data[0].depth)
        depth12 = (depth * ((1 << 12)-1)).astype(np.uint16)

        labels = np.array(k.render_data[0].instance).astype(np.uint32)
        label_cat = labels >> 24
        label_ins = labels & 0xffffff
        oor = (label_cat == 0) | (label_cat == 3) | (label_cat == 7) | (label_cat > 8)
        label_cat[oor] = 0
        label_cat[label_cat == 8] = 3
        label_ins[oor] = 0
        if np.any(label_ins >= (1 << 13)):
            print('instance label messed up', np.unique(label_ins))
        label16 = (label_cat << 13) | (label_ins & 0x1fff)
        label16 = label16.astype(np.uint16)

        OT_NONE = 0,
        OT_KART = 1,
        OT_TRACK = 2,
        OT_PROJECTILE = 3,
        OT_PICKUP = 4,
        OT_NITRO = 5,
        OT_BOMB = 6,
        info = {}
        c = state.players[0].camera
        P = np.array(c.projection)
        V = np.array(c.view)
        info['projection'] = P.tolist()
        info['view'] = V.tolist()
        info['karts'] = []
        visible_karts = np.unique(label_ins[label_cat == 1])
        for kart in state.karts:
            kart_info = {}
            kart_info['id'] = kart.id
            kart_info['name'] = kart.name
            kart_info['world_position'] = list(kart.location)
            kart_info['screen_position'] = list(project(P, V, kart.location))
            kart_info['visible'] = kart.id in visible_karts
            info['karts'].append(kart_info)


        info['items'] = []
        visible_items = np.unique(labels)
        for item in state.items:
            cat = (item.id >> 24) & 0xff
            ins = item.id & 0xffffff
            if cat == 0 or cat == 3 or cat == 7 or cat > 8:
                cat, ins = 0, 0
            if cat == 8:
                cat = 3
            id16 = (cat << 13) | (ins & 0x1fff)

            item_info = {}
            item_info['id'] = id16
            item_info['world_position'] = list(item.location)
            item_info['screen_position'] = list(project(P, V, item.location))
            item_info['visible'] = item.id in visible_items
            info['items'].append(item_info)

        # from pylab import imshow, show, Circle, subplots
        # fig, ax = plt.subplots()
        # imshow(label16)
        # for item in info['items']:
        #     x, y, z = item['screen_position']
        #     ax.add_artist(Circle((x, y), fill=False))
        #     if item['visible']:
        #         ax.annotate(item['id'], xy=(x,y), ha="center")
        # show()


        num = str(cnt).zfill(5)
        cnt += 1
        with open('data_temp/%s/info_%s_%s.json' % (args.split, args.track_name+'_'+args.prefix, num), 'w') as f:
            json.dump(info, f)
        write_png16(depth12, 'data_temp/%s/depth_%s_%s.png' % (args.split, args.track_name+'_'+args.prefix, num))
        write_png16(label16, 'data_temp/%s/label_%s_%s.png' % (args.split, args.track_name+'_'+args.prefix, num))
        PIL.Image.fromarray(im).save('data_temp/%s/image_%s_%s.jpg' % (args.split, args.track_name+'_'+args.prefix, num))


if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('track_name')
    parser.add_argument('-s', '--split', type=str, default='train')
    parser.add_argument('-n', '--num_images', type=int, default=100)
    parser.add_argument('-k', '--num_karts', type=int, default=10)
    parser.add_argument('-x', '--prefix', default='')
    args = parser.parse_args()

    generate(args)
