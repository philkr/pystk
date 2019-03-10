import pystk
import matplotlib.pyplot as plt
from time import time
import numpy as np

# pystk.set_log_level(pystk.LogLevel.warn)

config = pystk.Config.sd()
config.screen_width = 400
config.screen_height = 300
k = pystk.SuperTuxKart(config)

k.start()
k.step(0.1)

I = k.render_data[0].image
D = k.render_data[0].depth
L = k.render_data[0].instance
L = np.array(L)

fig = plt.figure()
axI = fig.add_subplot(2, 2, 1)
axD = fig.add_subplot(2, 2, 2)
axS = fig.add_subplot(2, 2, 3)
axL = fig.add_subplot(2, 2, 4)

fig.canvas.draw()

hI = axI.imshow(I)
hD = axD.imshow(D)
hS = axS.imshow(L >> 24)
hL = axL.imshow((L << 8) >> 8)

axI.axis('off')
axD.axis('off')

t0 = time()

for i in range(100):
	k.step(0.01)
	I = k.render_data[0].image
	D = k.render_data[0].depth
	L = k.render_data[0].instance
	L = np.array(L)
	
	hI.set_data(I)
	hD.set_data(D)
	hL.set_data((L << 8) >> 8)
	hS.set_data(L >> 24)
	
	fig.canvas.draw()
	fig.canvas.flush_events()

	plt.pause(1e-8) 

print(100./(time()-t0), 'FPS')

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
