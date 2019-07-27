from glob import glob
from os import path, makedirs

import numpy as np
from PIL import Image
import json
import shutil
import random

TEMP_DIR = 'data_temp'
DATA_DIR = 'dense_data'

merge_label = {6: 3, 5: 4}
# OT_NONE = 0,
# OT_KART = 1,
# OT_TRACK = 2,
# OT_PROJECTILE = 3,
# OT_PICKUP = 4,
# OT_NITRO = 5, -> 4
# OT_BOMB = 6, -> 3
n_image = {'train': 10000, 'valid': 2500, 'test': 7500}

def remap(seg):
    for k, v in merge_label.items():
        seg[seg == k] = v
    return seg

HEX_PALLETE = [0xeeeeec, 0xfcaf3e, 0x2e3436, 0x204a87, 0xa40000]
PALLETE = [(h >> s) & 0xff for h in HEX_PALLETE for s in [16, 8, 0]]
PALLETE.extend([0] * (768 - len(PALLETE)))


def save_seg_label(label, path):
    im = Image.new('P', label.shape[::-1])
    im.putpalette(PALLETE)
    im.putdata(label.astype(np.uint8).flatten())
    im.save(path)


def save_info(src, dst):
    with open(src) as fp:
        info = json.load(fp)
    kart_ids = np.array([k['id'] for k in info['karts']], dtype=np.uint32)
    kart_info = np.array([k['screen_position'] + [k['visible']] for k in info['karts']], dtype=np.float32)
    item_ids = np.array([k['id'] for k in info['items']], dtype=np.uint32)
    item_info = np.array([k['screen_position'] + [k['visible']] for k in info['items']], dtype=np.float32)
    np.savez(dst, kart_ids, kart_info, item_ids, item_info, allow_pickle=False)


for s in n_image:
    dist = {}
    for f in glob(path.join(TEMP_DIR, s, 'label*.png')):
        label = np.array(Image.open(f))
        d = np.bincount(label.flatten() >> 13, minlength=16)
        for k, v in merge_label.items():
            d[v] += d[k]
            d[k] = 0
        dist[f] = d
    total_dist = sum([d for d in dist.values()])
    print(total_dist / sum(total_dist))

    # Create the output dir
    try:
        makedirs(path.join(DATA_DIR, s))
    except FileExistsError:
        pass

    # Select some images
    selected_images = [f for _, f in sorted([(d[3] + d[4], f) for f, d in dist.items()])[-n_image[s]:]]
    with open(path.join(DATA_DIR, s+'.txt'), 'w') as f:
        f.write('\n'.join([path.basename(f).replace('label_','') for f in selected_images]))

    select_dist = sum([dist[f] for f in selected_images])
    print(select_dist / sum(select_dist))

    random.shuffle(selected_images)
    n_im = 0
    for f in selected_images:
        label = remap(np.array(Image.open(f)) >> 13)
        save_seg_label(label, path.join(DATA_DIR, s, '%05d_seg.png' % n_im))
        shutil.copy(f.replace('label_', 'image_').replace('.png', '.jpg'), path.join(DATA_DIR, s, '%05d_im.jpg' % n_im))
        save_info(f.replace('label_', 'info_').replace('.png', '.json'), path.join(DATA_DIR, s, '%05d_info.npz' % n_im))
        n_im += 1
