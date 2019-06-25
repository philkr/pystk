import argparse
from . import pystk_cpp as pystk, gui
from time import time, sleep

parser = argparse.ArgumentParser()
parser.add_argument('-lt', '--list-tracks', action='store_true')
parser.add_argument('-lk', '--list-karts', action='store_true')
parser.add_argument('-v', '--visualization', type=str, choices=list(gui.VT.__members__), nargs='+', default=['IMAGE'])
parser.add_argument('-p', '--play', action='store_true')
parser.add_argument('-b', '--benchmark', action='store_true')
parser.add_argument('-t', '--track')
parser.add_argument('-k', '--kart')
parser.add_argument('-s', '--step_size', type=float)
args = parser.parse_args()

if args.list_tracks:
    pystk.init(pystk.GraphicsConfig.ld())
    tracks = pystk.list_tracks()
    pystk.clean()
    print('List of tracks [%d]:' % len(tracks))
    for l in tracks:
        print(' * \'%s\''%l)
    print()

if args.list_karts:
    pystk.init(pystk.GraphicsConfig.ld())
    karts = pystk.list_karts()
    pystk.clean()
    print('List of karts [%d]:' % len(karts))
    for l in karts:
        print(' * \'%s\''%l)
    print()

if args.play:
    config = pystk.GraphicsConfig.hd()
    config.screen_width = 800
    config.screen_height = 600
    pystk.init(config)

    config = pystk.RaceConfig()
    if args.kart is not None:
        config.players[0].kart = args.kart
    config.players[0].controller = pystk.PlayerConfig.Controller.AI_CONTROL
    if args.track is not None:
        config.track = args.track
    if args.step_size is not None:
        config.step_size = args.step_size

    k = pystk.SuperTuxKart(config)

    k.start()

    ui = gui.UI([gui.VT[x] for x in args.visualization]) # eval FTW

    t0 = time()
    n = 0
    while ui.visible:
        if not ui.pause:
            k.step(ui.current_action)
        ui.show(k.render_data[0])
        # Make sure we play in real time
        n += 1
        delta_d = n * config.step_size - (time() - t0)
        if delta_d > 0:
            ui.sleep(delta_d)

    k.stop()
    del k
    pystk.clean()

if args.benchmark:
    for config in [pystk.GraphicsConfig.ld(),pystk.GraphicsConfig.sd(),pystk.GraphicsConfig.hd()]:
        print( config )
        t0 = time()
        config.screen_width = 200
        config.screen_height = 150
        pystk.init(config)

        config = pystk.RaceConfig()
        if args.kart is not None:
            config.kart = args.kart
        if args.track is not None:
            config.track = args.track
        if args.step_size is not None:
            config.step_size = args.step_size

        t1 = time()
        k = pystk.SuperTuxKart(config)

        k.start()

        t2 = time()
        for it in range(1000):
            k.step()
        t3 = time()
        print( '  graphics', (t1-t0))
        print( '  load', (t2-t1))
        print( '  step FPS', 1000. / (t3-t2))

        k.stop()
        del k
        pystk.clean()
