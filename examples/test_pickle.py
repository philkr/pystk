import argparse
import pystk
import numpy as np

def recursive_cmp(a, b, name=''):
    assert type(a) == type(b), 'Type mismatch for %s: %s vs %s' % (name, type(a), type(b))
    if isinstance(a, list):
        assert len(a) == len(b), 'List mismatch for len(%s): %d vs %d' % (name, len(a), len(b))
        for i in range(len(a)):
            recursive_cmp(a[i], b[i], name+'[%d]' % i)
    elif isinstance(a, float):
        assert abs(a-b) < 1e-5, 'Value mismatch for %s: %s vs %s' % (name, a, b)
    elif isinstance(a, (int, str, type(None))):
        if len(name) < 3 or name[-3:] != '.id':
            assert a == b, 'Value mismatch for %s: %s vs %s' % (name, a, b)
    elif callable(a):
        pass
    elif isinstance(a, object):
        for p in dir(a):
            if p[0] != '_' and type(getattr(a, p)) != type(a):
                assert hasattr(b, p), 'b.%s.%s not not exist!' % (name, p)
                p_a = getattr(a, p)
                p_b = getattr(b, p)
                recursive_cmp(p_a, p_b, name+'.'+p)
    else:
        assert False, 'unknown object type %s' % type(a)


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

    random_sa = np.random.rand(1000, 2)

    states = {}
    for config in [pystk.GraphicsConfig.ld(), pystk.GraphicsConfig.sd(), pystk.GraphicsConfig.hd()]:
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

        for a, s in random_sa:
            w = pystk.WorldState()
            w.update()
            s_vec.append(w)

            race.step(pystk.Action(acceleration=a, steer=s))
        race.stop()
        del race
        pystk.clean()

    state_names = list(states)
    for i in range(len(states[state_names[0]])):
        mismatch = False
        for k, n in enumerate(state_names):
            for m in state_names[k+1:]:
                try:
                    recursive_cmp(states[n][i], states[m][i], 'state[%d]' % i)
                except AssertionError as e:
                    print('State mismatch between %s and %s' % (n, m))
                    print(e.args)
                    mismatch = True
        if mismatch:
            break
