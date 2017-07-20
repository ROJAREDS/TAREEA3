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
