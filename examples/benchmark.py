import argparse
import pystk
from time import time

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('-t', '--track')
    parser.add_argument('-k', '--kart', default='')
    parser.add_argument('-s', '--step_size', type=float)
    parser.add_argument('-n', '--num_player', type=int, default=1)
    args = parser.parse_args()

    for config in [pystk.GraphicsConfig.ld(), pystk.GraphicsConfig.sd(), pystk.GraphicsConfig.hd(), None]:
        print(config)
        t0 = time()
        render = True
        if config is None:
            config = pystk.GraphicsConfig.ld()
            render = False
        config.screen_width = 200
        config.screen_height = 150
        pystk.init(config)
        init_time, t0 = time() - t0, time()

        config = pystk.RaceConfig(render=render)
        if args.kart != '':
            config.players[0].kart = args.kart
        if args.track is not None:
            config.track = args.track
        if args.step_size is not None:
            config.step_size = args.step_size
        for i in range(1, args.num_player):
            config.players.append(pystk.PlayerConfig(args.kart, pystk.PlayerConfig.Controller.AI_CONTROL))

        race = pystk.Race(config)
        race_time, t0 = time() - t0, time()

        race.start()
        start_time, t0 = time() - t0, time()

        for it in range(500):
            race.step()
        step_time, t0 = time() - t0, time()
        for it in range(5):
            race.restart()
        restart_time, t0 = time() - t0, time()

        print('  graphics', init_time)
        print('  race config', race_time)
        print('  start', start_time)
        print('  restart', restart_time / 5.)
        print('  step FPS', 500. / step_time)

        race.stop()
        del race
        pystk.clean()
