import numpy as np
from matplotlib import pyplot as plt
import datetime
import os

# def stringToDate(dateStr):
#     d = dateStr.replace('-','')
#     d = d.replace('_','')
#     d = d.replace(':','')
#     d = d.replace(".txt",'')
#     return datetime.datetime.strptime(d,'%Y%m%d%H%M%S')

# # keywords = ["$INFO$", "$DATE$", "$PARAMS$", "$TYPE$", "$DATA$"]

# #MAIN LOG ANALYSIS

# fileName = "log_10_2_0.001_2020-12-14_01:32:29_s1a.txt"
# fileNamePattern = fileName.split("_")

# name = fileNamePattern[0]
# partNum = fileNamePattern[1]
# dim = fileNamePattern[2]
# stop = fileNamePattern[3]
# date = fileNamePattern[4]
# time = fileNamePattern[5]
# taskType = fileNamePattern[6]

# pyDate = stringToDate(date+time)

# with open("logs/"+fileName, "r") as f:
#     logContent = f.readlines()

# #remove ends of line
# logContent = [x.rstrip() for x in logContent] 

# iterations = []
# costs = []
# bestIds = []

# for elem in logContent:
#     currentline = elem.split(",")
#     iterations.append(int(currentline[0]))
#     costs.append(float(currentline[1]))
#     bestIds.append(int(currentline[2]))

# #plot

# plt.figure(0)
# myTitle = f"PSO_OpenMP: n={dim}, l.czastek{partNum}, stop={stop}"
# plt.plot(iterations, costs)
# plt.xticks(np.arange(0, max(iterations)+2, 5.0))
# plt.xlabel("iteracje")
# plt.ylabel("koszt")
# plt.title(myTitle)
# plt.savefig("PSO_koszt2.png")    

######################################################################
# Funkcje ktore optymalizujemy

import math

N = 100 # resolution for given range x_min - x_max
x_min = -10
x_max = 10

x_range=np.linspace(x_min, x_max, N, endpoint=True)

def funkcja1(x,n):

    suma = np.sum(math.pow(x,2))   
    x = np.repeat(x,n)
    n = np.arange(1,n+1,1)
    x2 = x/n
    arg = [math.cos(i) for i in x2]    
    prod = np.prod(arg)   

    return 1/40 * suma + 1 - prod

# #tylko dla n=2
# def funkcja2(x, xi):

#     return 100*math.pow((xi-math.pow(x,2)),2) + math.pow((1-x),2)

n=2
y = [funkcja1(x, n) for x in x_range]

# plt.figure(1)
# plt.plot(x_range, y)
# plt.title(f"Wykres dla n ={n}")
# plt.show()

# y=[]

# for i in range(0,N-1):
#    y.append(funkcja2(x_range[i],x_range[i+1]))

# plt.figure(2)
# plt.plot(x_range[0:len(y)], y)
# plt.title(f"Wykres dla n ={n}")
# plt.show()


######################################################################
#best particles


######################################################################
#all particles

# file: iteracja, id, x, y , vx, vy, cost

fileNameParticles = "particlesLog_10_2_0.001_2020-12-14_01:32:29_s1a.txt"

fileNameParticlesSplit = fileNameParticles.split("_") #TODO - put into function

name = fileNameParticlesSplit[0]
partNum = int(fileNameParticlesSplit[1])
dim = int(fileNameParticlesSplit[2])
stop = float(fileNameParticlesSplit[3])
date = fileNameParticlesSplit[4]
time = fileNameParticlesSplit[5]
taskType = fileNamePattern[6]

title = ""
if(taskType == "s1aP"):
    title = "PSO_OMP_zad1_academic"  #TODO - make list of title types - #16

pyDate = stringToDate(date+time)

with open("logs/"+fileNameParticles, "r") as f:
    logParticles = f.readlines()

logParticles = [x.rstrip() for x in logParticles] 

cols= len(logParticles[0].split(',')) #iteracja, id, x, y , vx, vy, cost
arr = np.empty((0,cols), float)

for line in logParticles:
    lineSplit = line.split(",")
    lineFloat = [float(x) for x in lineSplit]
    arr = np.append(arr, np.array([lineFloat]), axis=0)

costMax =max(arr[:,6])
rows = arr.shape[0]
iterations =int(rows / partNum)
arr = np.reshape(arr,(iterations, partNum, cols))

marker_size=25
plt.figure(4)
plt.xlim(-40, 40)
plt.ylim(-40, 40)
plt.scatter(arr[0,:,2], arr[0,:,3], marker_size,c=arr[0,:,6])
plt.title(f"PSO n={dim}, l.czastek{partNum}")
plt.xlabel("x1")
plt.ylabel("x2")
cbar= plt.colorbar()
cbar.set_label("koszt", labelpad=+1)
plt.savefig("PSO_scatter.png")    

from matplotlib import cm

for i in range(iterations):
    plt.clf()
    plt.xlim(-40, 40)
    plt.ylim(-40, 40)
    plt.xticks(np.arange(-40,50,10))
    plt.yticks(np.arange(-40,50,10))
    plt.scatter(arr[i,:,2], arr[i,:,3], marker_size, c=arr[i,:,6],vmin=0, vmax=costMax)
    plt.title(f"PSO n={dim}, l.czastek{partNum}, iter: {i}")
    plt.xlabel("x1")
    plt.ylabel("x2")
    cbar= plt.colorbar()
    cbar.set_label("koszt")
    plt.savefig(f"plots/plot_{i}.png")

os.system("ffmpeg -r 5 -i plots/plot_%d.png -vcodec mpeg4 -y plots/scatter3.mp4")








