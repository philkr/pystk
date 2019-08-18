import pystk
pystk.init( pystk.GraphicsConfig.hd() )
k = pystk.Race(pystk.RaceConfig(num_kart=1, laps=1))
k.start()
k.step()
raise Exception()
