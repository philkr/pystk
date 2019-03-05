import pystk
import matplotlib.pyplot as plt
from time import time

config = pystk.Config.sd()
config.screen_width = 200
config.screen_height = 150
k = pystk.SuperTuxKart(config)

k.start()
k.step(0.1)

I = k.render_data[0].image
D = k.render_data[0].depth

fig = plt.figure()
axI = fig.add_subplot(2, 1, 1)
axD = fig.add_subplot(2, 1, 2)

fig.canvas.draw()

hI = axI.imshow(I)
hD = axD.imshow(D)

axI.axis('off')
axD.axis('off')

t0 = time()

for i in range(100):
	k.step(0.01)
	I = k.render_data[0].image
	D = k.render_data[0].depth
	
	hI.set_data(I)
	hD.set_data(D)
	
	fig.canvas.draw()
	fig.canvas.flush_events()

	plt.pause(1e-8) 

print(100./(time()-t0), 'FPS')


t0 = time()

for i in range(1000):
	k.step(0.01)

print(1000./(time()-t0), 'FPS')

plt.pause(100) 

k.stop()


#from PySide2.QtCore import Slot, Qt
#height, width, channel = cvImg.shape
#bytesPerLine = 3 * width
#qImg = QImage(cvImg.data, width, height, bytesPerLine, QImage.Format_RGB888)
