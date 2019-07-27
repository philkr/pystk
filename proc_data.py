import os
import shutil
import data
import random
from PIL import Image

TEMP_DIR = 'hw1_temp'
DATA_DIR = 'hw1_data'

TRACK_TRAIN = ['cornfield_crossing', 'black_forest', 'snowmountain', 'fortmagma', 'olivermath',
       'scotland', 'hacienda', 'abyss']
TRACK_TEST = ['volcano_island', 'zengarden', 'snowtuxpeak',
       'lighthouse', 'minigolf']
TRACK_VAL = ['candela_city', 'xr591', 'ravenbridge_mansion', 'sandtrack']


output = {s: 'file,label,track\n' for s in ['train', 'valid', 'test']}
cnt = {s: 0 for s in output}
label = ''
imgs = os.listdir(TEMP_DIR)
random.shuffle(imgs)

for filename in sorted(imgs):
    if filename.endswith(".png"):
        track, _, label, __ = filename.rsplit('_', maxsplit=3)
        split = None
        if track in TRACK_TRAIN:
            split = 'train'
        elif track in TRACK_VAL:
            split = 'valid'
        elif track in TRACK_TEST:
            split = 'test'
        else:
            continue
        cnt[split] += 1
        new_filename = str(cnt[split]).zfill(5) + '.jpg'
        Image.open(os.path.join(TEMP_DIR, filename)).save(os.path.join(DATA_DIR, split, new_filename))
        output[split] += new_filename + ',' + label + ',' + track + '\n'

for s in output:
    f = open(os.path.join(DATA_DIR, s, 'labels.csv'), 'w')
    f.write(output[s])
    f.close()
