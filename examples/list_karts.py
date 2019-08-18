import pystk

pystk.init(pystk.GraphicsConfig.ld())
karts = pystk.list_karts()
pystk.clean()
print('List of karts [%d]:' % len(karts))
for l in karts:
    print(' * \'%s\''%l)
print()
