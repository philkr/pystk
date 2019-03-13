import pystk
import matplotlib.pyplot as plt
from time import time
import numpy as np
from pystk import gui

# pystk.set_log_level(pystk.LogLevel.warn)

config = pystk.GraphicsConfig.sd()
config.screen_width = 400
config.screen_height = 300
pystk.init(config)

config = pystk.RaceConfig()
if args.kart is not None:
	config.kart = args.kart
if args.track is not None:
	config.track = args.track
if args.step_size is not None:
	config.step_size = args.step_size

k = pystk.SuperTuxKart(config)

k.start()

ui = gui.UI()

t0 = time()
n = 0
while ui.visible:
	k.step(ui.current_action)
	ui.show(k.render_data[0])
	n += 1
	if n > 100:
		print('FPS = ', 100. / (time() - t0))
		n = 0
		t0 = time()

k.stop()
pystk.clean()

t0 = time()

for i in range(1000):
	k.step()

print(1000./(time()-t0), 'FPS')

#t0 = time()

#for i in range(100):
	#k.step(0.0001)

#print(100./(time()-t0), 'FPS')

plt.pause(10)

k.stop()


#from PySide2.QtCore import Slot, Qt
#height, width, channel = cvImg.shape
#bytesPerLine = 3 * width
#qImg = QImage(cvImg.data, width, height, bytesPerLine, QImage.Format_RGB888)
