import numpy as np 
import matplotlib.pyplot as plt
from matplotlib import animation 

#inicializacion
c=1.0
x=30.0
y=30.0
c=1.0
r=0.5
puntos=300
#matrices
inicio=np.zeros((302,302))
inicio[100,151]=-0.5
momento1=np.zeros((302,302))
momento2=np.zeros((302,302))
momento3=np.zeros((302,302))
lista=[]
dx=x/299.0
dy=y/299.0
dt=(dx*r)/c
#print dx,dy,dt
def f(t):
    mascara=np.ones((302, 302))
    mascara[200,:]=np.zeros((1,302))
    mascara[200,140:170]=np.ones((1,30))
#plt.imshow(mascara)
#plt.show()
    k=(2.0*dt*(c**2.0))/dx
#primera derivada
    for i in range(1,299):
        for j in range(1,299):
            momento2[i,j]=k*((inicio[i+1,j])-(inicio[i-1,j]))+k*((inicio[i,j+1])-inicio[i,j-1])
        #print momento1
    momento3=inicio.copy()
    momento1=momento2.copy()*mascara
    lista.append(momento1)

    s=((c**2)*(dt**2))/(dx**2)
    for i in range (1,t):
        for j in range(1,299):
            for l in range(1,299):
                momento2[j,l]=s*((momento1[j+1,l])-(2*momento1[j,l])+(momento1[j-1,l]))+s*(momento1[j,l+1]-2*(momento1[j,l])+momento1[j,l-1])+(2*momento1[j,l])-momento3[j,l]
        momento3=momento1.copy()
        momento1=momento2.copy()*mascara
        lista.append(momento1)
        
    return momento1, lista
t60=1200
t30=600
#print f(t60)

plt.imshow(f(t60)[0])
plt.title('Onda en 60s')
color = plt.colorbar()
color.ax.set_ylabel(r'[$\frac{AMPLITUD}',rotation=0)
plt.ylabel('$x$')
plt.xlabel('$y$')
plt.savefig('ondaen60.png')
plt.close()

plt.imshow(f(t30)[0],cmap="hot")
plt.title('Onda en 30s')
color = plt.colorbar()
color.ax.set_ylabel(r'[$\frac{AMPLITUD}',rotation=0)
plt.ylabel('$x$')
plt.xlabel('$y$')
plt.savefig("ondaen20.png")
plt.close()

cte=f(t60)[1]
fig=plt.figure()
cte1=plt.imshow(np.abs(cte[0]),extent=(30+dx,30-dx,30+dy,30-dy))
#plt.colorbar()

def ani(time):
    cte1.set_array(abs(cte[time]))
    return cte1
Writer = animation.writers['ffmpeg']
writer = Writer(fps=15,metadata=dict(artist='ROJAREDS'), bitrate=1800)

movim=animation.FuncAnimation(fig,ani, np.arange(1,len(lista)), interval=20,blit=False)
plt.title('Movimiento de la onda')
color = plt.colorbar()
color.ax.set_ylabel(r'[$\frac{AMPLITUD}',rotation=0)
plt.ylabel('$x$')
plt.xlabel('$y$')
#plt.show()
im_ani.save('Onda.mp4', write=write)
             
   
