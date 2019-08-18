import pystk
import numpy as np

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
    print(np.asarray(state.players[0].camera.view), np.asarray(state.players[0].camera.projection))
    print(state, state.karts, state.players)
    # print( '\n'.join([' * '+str((k.name, k.location, k.front, k.velocity)) for k in state.karts]) )
    # print( '\n'.join([' * '+str((k.id, k.location, k.type)) for k in state.items]) )

    import pylab as plt
    from matplotlib import collections as mc

    lc = mc.LineCollection(track.path_nodes[:, :, ::2])
    fig, ax = plt.subplots()
    ax.add_collection(lc)
    ax.autoscale()
    ax.margins(0.1)

    items = np.array([k.location for k in state.items])
    plt.scatter(items[:, 0], items[:, 2])

    karts = np.array([k.location for k in state.karts])
    plt.scatter(karts[:, 0], karts[:, 2])

    plt.show()

k.stop()
del k
pystk.clean()
