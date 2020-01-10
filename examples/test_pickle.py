import argparse
import pystk


def recursive_cmp(a, b, name=''):
    import inspect
    assert type(a) == type(b), 'Type mismatch for %s: %s vs %s' % (name, type(a), type(b))
    if isinstance(a, list):
        print('%s L' % name, len(a), len(b))
    elif isinstance(a, (float, int, str, type(None))):
        assert a == b, 'Value mismatch for %s: %s vs %s' % (name, a, b)
        print('%s V' % name)
    elif callable(a):
        pass
    elif inspect.isclass(a):
        for p in dir(a):
            if p[0] != '_':
                assert hasattr(b, p), 'b.%s.%s not not exist!' % (name, p)
                p_a = getattr(a, p)
                p_b = getattr(b, p)
                recursive_cmp(p_a, p_b, name+'.'+p)
    else:
        print('UNKNOWN', name, a.__class__.__name__, dir(a.__class__))


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('-t', '--track')
    parser.add_argument('-k', '--kart', default='')
    parser.add_argument('-s', '--step_size', type=float)
    parser.add_argument('-n', '--num_player', type=int, default=1)
    args = parser.parse_args()

    race_config = pystk.RaceConfig()
    if args.kart != '':
        race_config.players[0].kart = args.kart
    if args.track is not None:
        race_config.track = args.track
    if args.step_size is not None:
        race_config.step_size = args.step_size
    for i in range(1, args.num_player):
        race_config.players.append(pystk.PlayerConfig(args.kart, pystk.PlayerConfig.Controller.AI_CONTROL))

    states = {}
    for config in [pystk.GraphicsConfig.ld(), pystk.GraphicsConfig.sd(), pystk.GraphicsConfig.hd(), None]:
        s_vec = []
        states[config] = s_vec

        race_config.render = config is not None
        if not race_config.render:
            config = pystk.GraphicsConfig.ld()
        config.screen_width = 320
        config.screen_height = 240
        pystk.init(config)

        race = pystk.Race(race_config)
        race.start()
        race.step()

        for it in range(10):
            w = pystk.WorldState()
            w.update()
            s_vec.append(w)

            race.step()
        race.stop()
        del race
        pystk.clean()

    state_names = list(states)
    for i in range(len(states[None])):
        for k, n in enumerate(state_names):
            for m in state_names[k+1:]:
                recursive_cmp(states[n][i], states[m][i])
