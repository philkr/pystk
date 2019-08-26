import argparse
import pystk
from time import time
from . import gui

if __name__ == "__main__":
    soccer_tracks = {"soccer_field", "icy_soccer_field"}

    parser = argparse.ArgumentParser()
    parser.add_argument('-t', '--track')
    parser.add_argument('-k', '--kart', default='')
    parser.add_argument('-s', '--step_size', type=float)
    parser.add_argument('-n', '--num_player', type=int, default=1)
    parser.add_argument('-v', '--visualization', type=str, choices=list(gui.VT.__members__), nargs='+',
                        default=['IMAGE'])
    parser.add_argument('--verbose', action='store_true')
    args = parser.parse_args()

    config = pystk.GraphicsConfig.hd()
    config.screen_width = 800
    config.screen_height = 600
    pystk.init(config)

    config = pystk.RaceConfig()
    config.num_kart = 2
    if args.kart is not None:
        config.players[0].kart = args.kart
    config.players[0].controller = pystk.PlayerConfig.Controller.AI_CONTROL

    for i in range(1, args.num_player):
        config.players.append(pystk.PlayerConfig(args.kart, pystk.PlayerConfig.Controller.AI_CONTROL))

    if args.track is not None:
        config.track = args.track
        if args.track in soccer_tracks:
            config.mode = config.RaceMode.SOCCER
    if args.step_size is not None:
        config.step_size = args.step_size

    race = pystk.Race(config)

    race.start()

    uis = [gui.UI([gui.VT[x] for x in args.visualization]) for i in range(args.num_player)]

    state = pystk.WorldState()
    t0 = time()
    n = 0
    while all(ui.visible for ui in uis):
        if not all(ui.pause for ui in uis):
            race.step(uis[0].current_action)
            state.update()
            if args.verbose and config.mode == config.RaceMode.SOCCER:
                print('Score ', state.soccer_score)
        for ui, d in zip(uis, race.render_data):
            ui.show(d)
        # Make sure we play in real time
        n += 1
        delta_d = n * config.step_size - (time() - t0)
        if delta_d > 0:
            ui.sleep(delta_d)

    race.stop()
    del race
    pystk.clean()
