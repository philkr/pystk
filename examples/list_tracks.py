import pystk

pystk.init(pystk.GraphicsConfig.ld())
tracks = pystk.list_tracks()
pystk.clean()
print('List of tracks [%d]:' % len(tracks))
for l in tracks:
    print(' * \'%s\''%l)
print()
