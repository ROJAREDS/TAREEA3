import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import mpl_toolkits.mplot3d.axes3d as p3
import matplotlib.animation as animation
datos = np.loadtxt('datr.txt',delimiter=",")
print len(datos)

sun=datos[0:1000,0:3]
merc=datos[1000:2000,0:3]
ven=datos[2000:3000,0:3]
tie=datos[3000:4000,0:3]
mar=datos[4000:5000,0:3]
jup=datos[5000:6000,0:3]
sat=datos[6:7000,0:3]
ura=datos[7000:8000,0:3]
nep=datos[8000:9000,0:3]
plu=datos[9000:10000,0:3]
step = 50
total= np.array([sun,merc,ven,tie,mar,jup,sat,ura,nep,plu])

fig= plt.figure()
ax= Axes3D(fig)

ax.plot(sun[:,0],sun[:,1],sun[:,2], label='Orbita Sol')
ax.plot(merc[:,0],merc[:,1],merc[:,2],label='Orbita Mercurio')
ax.plot(ven[:,0],ven[:,1],ven[:,2],label='Orbita Venus')
ax.plot(tie[:,0],tie[:,1],tie[:,2],label='Orbita Tierra')
ax.plot(mar[:,0],mar[:,1],mar[:,2],label='Orbita Marte')
ax.plot(jup[:,0],jup[:,1],jup[:,2],label='Orbita Jupiter')
ax.plot(sat[:,0],sat[:,1],sat[:,2],label='Orbita Saturno')
ax.plot(ura[:,0],ura[:,1],ura[:,2],label='Orbita Urano')
ax.plot(nep[:,0],nep[:,1],nep[:,2],label='Orbita Neptuno')
ax.plot(plu[:,0],plu[:,1],plu[:,2],label='Orbita Pluton')
plt.ylabel('$x$')
plt.xlabel('$y$')
ax.legend()
plt.savefig('orbit.png')


#plt.show()


