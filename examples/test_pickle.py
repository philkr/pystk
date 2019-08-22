import pystk


def test(o):
    from pickle import dumps, loads
    print(o)
    s = dumps(o)
    print(len(s))
    print(loads(s))


test(pystk.GraphicsConfig.ld())
test(pystk.RaceConfig())

pystk.init(pystk.GraphicsConfig.ld())
config = pystk.RaceConfig()
k = pystk.Race(config)

k.start()

state = pystk.WorldState()
track = pystk.Track()

for it in range(10):
    k.step()
    state.update()
    track.update()
    test(state)
    test(track)
    test(k.last_action)
    test(k.render_data)

k.stop()
del k
pystk.clean()
