import numpy as np
from matplotlib import pyplot as plt
from matplotlib.pyplot import figure
import datetime
import os
import math
import itertools 
import scipy.interpolate
from scipy.interpolate import griddata
from matplotlib import cm

from os import listdir
from os.path import isfile, join

task = "T2"
lib = "MPI"
alg = "PSO"
partNum = 30
stop = 0.1
dim = 2
ext='png'


mypath = os.getcwd()
mypath = os.path.join(mypath, "wykresy","MPI_PSO_T2")
onlyfiles = [f for f in listdir(mypath) if isfile(join(mypath, f)) and "particlesLog" in f]

log_files_params = []

log_id=0
for f in onlyfiles:
    f= str(log_id)+'_'+f
    log_id+=1
    f = os.path.splitext(f)[0]
    f_params=f.split('_')
    log_files_params.append(f_params)

log_files_params.sort(key=lambda x: x[2]) # sort by process number

labels = [x[2]+'('+x[3]+')' for x in log_files_params]
sizes = [int(x[3]) for x in log_files_params]

fig1, ax1 = plt.subplots()
ax1.pie(sizes, labels=labels, autopct='%1.1f%%',
        shadow=True, startangle=90)
ax1.axis('equal')  
plt.title(f"{lib} - Liczba iteracji dla każdego z procesów")
plt.savefig(f"{lib}_{alg}_{task}_procIter.png", dpi = 200)

orderOfFiles = [x[0] for x in log_files_params]

allData = []

for i in range(0,len(log_files_params)):
    j = int(orderOfFiles[i])
    fileName = onlyfiles[j]

    content = []
    with open(os.path.join(mypath,fileName)) as f:
       content = [(line.rstrip()).split('_') for line in f]  
    allData.append(content)

allDataList = list(itertools.chain.from_iterable(allData)) 

costs = [float(x[4]) for x in allDataList]
globalMin = min(costs)
minpos = costs.index(globalMin) 

maxIter = max(sizes)

iterSortedLog = []
costHistory = [ [-1,float('inf') ] for _ in range(maxIter) ]

for i in range(0,minpos+1):    
    log = allDataList[i]
    it = int(log[0])-1
    if float(log[4]) < costHistory[it][1]:
        costHistory[it][1] = float(log[4])
        costHistory[it][0] = log[1] 

   
costs = [x[1] for x in costHistory]
iterations = range(0,maxIter)

monotonCost = []
lastCost = costs[0]
for elem in costs:
    if elem <= lastCost:
        monotonCost.append(elem)
        lastCost = elem
    else:
        monotonCost.append(lastCost)


plt.figure()
myTitle = f"{lib}, {alg}, {task}: n={2}, l.czastek={partNum}, stop={stop} - wartość f.kosztu"
plt.plot(iterations[1:-1], monotonCost[1:-1])
# plt.xticks(np.arange(0, max(iterations)+2, 5.0))
plt.xlabel("iteracje")
plt.ylabel("koszt")
plt.xscale("log")
plt.title(myTitle)
plt.savefig(f"{lib}_{alg}_{task}_koszt_monotoniczny.png",dpi=200)

plt.figure()
myTitle = f"{lib}, {alg}, {task}: n={2}, l.czastek={partNum}, stop={stop} - wartość f.kosztu"
plt.plot(iterations[1:-1], costs[1:-1])
# plt.xticks(np.arange(0, max(iterations)+2, 5.0))
plt.xlabel("iteracje")
plt.ylabel("koszt")
plt.xscale("log")
plt.title(myTitle)
plt.savefig(f"{lib}_{alg}_{task}_koszt.png",dpi=200)  

##########################################################################################


N = 100 # resolution for given range x_min - x_max

#ograniczenie 
half = 40
area_min = -half
area_max = half
x=np.linspace(area_min, area_max, N, endpoint=True)
y=np.linspace(area_min, area_max, N, endpoint=True)

meshList = list(itertools.product(x, y))

#funkcje ogolne, wielowymiarowe

def task1(particlesList):
    suma = 0
    product = 1
    
    for i in range(0,len(particlesList)):    
        suma = suma + pow(particlesList[i], 2)
        product = product * math.cos(particlesList[i] / (i + 1))

    return 1.0 / 40.0 * suma + 1 - product

def task2(particlesList):
    costFunctionValue = 0
    for i in range(0,len(particlesList)-1):    
        costFunctionValue = costFunctionValue + (math.pow((particlesList[i + 1] - math.pow(particlesList[i], 2)), 2) * 100 + math.pow((1 - particlesList[i]), 2))
    return costFunctionValue
    
#zmodyfikowane do przekrojow

def funkcja1(x,n):

    suma = np.sum(math.pow(x,2))   
    x = np.repeat(x,n)
    n = np.arange(1,n+1,1)
    x2 = x/n
    arg = [math.cos(i) for i in x2]    
    prod = np.prod(arg)   

    return 1/40 * suma + 1 - prod


def funkcja2(x, xi):
    return 100*math.pow((xi-math.pow(x,2)),2) + math.pow((1-x),2)

#przekroj resenbrocka

# funk2=[]

# for i in range(0,N-1):
#    funk2.append(funkcja2(x[i],x[i+1]))

# plt.plot(x[0:len(funk2)], funk2)
# plt.title("Zad 2 - Funkcja rosenbrocka - przekrój")
# plt.show()

# wykres  naszej funkcji - poziomice/heatmapa oraz przekroj

# plt.figure(2)
# figure(num=None, figsize=(15, 6), dpi=200, facecolor='w', edgecolor='k')

#obliczenia
#przekroj
# res_2d_task1 = [task1([i]) for i in x] #TASK1
# res_2d_task2 = [task2([i]) for i in x] #TASK2

arr_task1 = np.empty((N*N,1), float)
arr_task2 = np.empty((N*N,1), float)

for i in range(0, len(meshList)):
    arr_task1[i,0] = task1(meshList[i])

for i in range(0, len(meshList)):
     arr_task2[i,0] = task2(meshList[i])


# plt.subplot(121)
# plt.plot(x[0:len(res_2d_task1)], res_2d_task1)
# plt.title(f"{task} - przekrój x1=0")
# plt.xlabel("x2")
# plt.ylabel("z")

z = 0
z1 = np.reshape(arr_task1,(N,N))
z2 = np.reshape(arr_task2,(N,N))

if(task == "T1"):
    z = z1
else:
    z = z2

# plt.subplot(122)

# plt.imshow(z, vmin=z.min(), vmax=z.max(), origin='lower', extent=[x.min(), x.max(), y.min(), y.max()])
# # plt.contour(x, y, z1) #TASK2
# plt.title(f"{task} - wykres dla n=2")
# plt.xlabel("x1")
# plt.ylabel("x2")
# cbar = plt.colorbar()
# cbar.set_label("wartość funkcji kosztu")
# # plt.savefig(f"{task}_2d_heatmap_.{ext}")  
# plt.show()

# plt.clf()

######################################################################
#WCZYTANIE WSZYSTKICH CZASTEK

# file: iteracja, id, x, y , vx, vy, cost

for elem in allDataList:
   elem[0] = int(elem[0])
   elem[1] = int(elem[1])
   elem[2] = float(elem[2])
   elem[3] = float(elem[3])
   elem[4] = float(elem[4])
allCosts = [x[4] for x in allDataList]
costMax = max(allCosts)
costMin = min(allCosts)
iterOfMin =  allCosts.index(costMin)
algIterMin = allDataList[iterOfMin][0]
iterations = maxIter


iterSortAllData = [ [] for _ in range(maxIter) ]

for elem in allDataList:
    iterSortAllData[elem[0]-1].append(elem)

initPosX = [x[2] for x in iterSortAllData[0]]
initPosY = [x[3] for x in iterSortAllData[0]]
initCost = [x[4] for x in iterSortAllData[0]]

# RYSOWANIE

plt.figure()
marker_size=50
plt.xlim(-40, 40)
plt.ylim(-40, 40)
plt.scatter(initPosX, initPosY, marker_size,c=initCost, vmin = 0, vmax = costMax)
plt.title(f"{lib}, {alg}, {task}: n={2}, l.czastek={partNum}, stop={stop} - iteracja 1")
plt.xlabel("x1")
plt.ylabel("x2")
cbar= plt.colorbar()
cbar.set_label("koszt czasteczki", labelpad=+5)
# plt.show()
plt.savefig(f"{lib}_{alg}_{task}_startPositions.{ext}", dpi=200)    

# wykresy do zrobienia gifa

for i in range(101):
    plt.clf()
    plt.xlim(-40, 40)
    plt.ylim(-40, 40)
    plt.xticks(np.arange(-40,50,10))
    plt.yticks(np.arange(-40,50,10))
    plt.scatter([x[2] for x in iterSortAllData[i]], [x[3] for x in iterSortAllData[i]], marker_size, c=[x[4] for x in iterSortAllData[i]],vmin=0, vmax=costMax)
    plt.title(f"{lib}, {alg}, {task}: n={dim}, l.czastek = {partNum}, iter: {i}")
    plt.xlabel("x1")
    plt.ylabel("x2")
    cbar= plt.colorbar()
    cbar.set_label("koszt")
    plt.savefig(f"plots/plot_{i}.png")

# os.system("convert -delay 2 -loop 0 plots/plot_{0..500}.png plots/scatter.gif") 

# marker_size=25

# plt.figure()
# for i in range(iterations):
#     # plt.clf()
#     plt.xlim(-40, 40)
#     plt.ylim(-40, 40)
#     plt.xticks(np.arange(-40,50,10))
#     plt.yticks(np.arange(-40,50,10))
#     plt.scatter(arr[i,:,2], arr[i,:,3], marker_size, c=arr[i,:,6],vmin=0, vmax=costMax)


#     # plt.savefig(f"plots/plot_{i}.png")
# plt.title(f"{alg} n={dim}, l.czastek{partNum}, l.iteracji{iterations}")
# plt.xlabel("x1")
# plt.ylabel("x2")
# cbar= plt.colorbar()
# cbar.set_label("koszt")
# plt.savefig(f"{alg}_{task}_scatter_allIters.{ext}")    

# get positions of particles with certain id or certain ids

def getBestSolutionHistory(dataArray, idVector):
    for i in range(0, (dataArray.shape)[0]):        
        array = dataArray[i][np.where(dataArray[i][:,1] == idVector[i])]
        global particlesBestArray
        particlesBestArray = np.append(particlesBestArray, array, axis=0)

def getParticleHistory(data, id, maxiter):
    particleHistory = []
    for itr in data[0:maxiter]:
        log = itr[id]
        particleHistory.append([log[2], log[3],log[4]])
    return particleHistory



# particlesArray = np.empty((0,cols), float)
# getParticleHistory(arr,5)    

# particlesBestArray = np.empty((0,cols), float)
# getBestSolutionHistory(arr,bestIds)

marker_size = 50
#TASK1

#TRAJEKTORIE WSZYSTKIE

# for i in range (0,partNum):

#     particlesArray = np.empty((0,cols), float)
#     getParticleHistory(arr,i)  
#     fig = plt.figure(i)
#     plt.clf()
#     plt.xlim(-40, 40)
#     plt.ylim(-40, 40)
#     plt.xticks(np.arange(-40,50,10))
#     plt.yticks(np.arange(-40,50,10))
#     plt.imshow(z, vmin=z.min(), vmax=z.max(), origin='lower', extent=[x.min(), x.max(), y.min(), y.max()], alpha=0.35, zorder = 0)
#     plt.plot(particlesArray[:,2],particlesArray[:,3],'b', zorder=1)
#     plt.scatter(particlesArray[:,2],particlesArray[:,3], marker_size, c=particlesArray[:,6],vmin=0, vmax=costMax, zorder=2)
#     plt.title(f"{alg} n={dim}, id.czastki{i}, l.iteracji{iterations}")
#     plt.xlabel("x1")
#     plt.ylabel("x2")
#     cbar= plt.colorbar()
#     cbar.set_label("koszt")
#     plt.savefig(f"trajectories/{task}_{alg}_plot_{i}.{ext}")


#BEST particles for solution    

# particlesBestArray = np.empty((0,cols), float)
# getBestSolutionHistory(arr,bestIds)  

id = 10
particleTrj = getParticleHistory(iterSortAllData, id, 150)

posXTrj = [x[0] for x in particleTrj]
posYTrj = [x[1] for x in particleTrj]
costTrj = [x[2] for x in particleTrj]

marker_size = 20

fig = plt.figure()
plt.clf()
plt.xlim(-40, 40)
plt.ylim(-40, 40)
plt.xticks(np.arange(-40,50,10))
plt.yticks(np.arange(-40,50,10))
plt.imshow(z, vmin=z.min(), vmax=z.max(), origin='lower', extent=[x.min(), x.max(), y.min(), y.max()], alpha=0.35, zorder = 0)
plt.plot(posXTrj, posYTrj,'b', zorder=1)
plt.scatter(posXTrj, posYTrj, marker_size, c=costTrj,vmin=0, vmax=costMax, zorder=2)
plt.title(f"{lib}, {alg}, {task}: n={dim}, cząstka o id:{id}, l.iteracji={100} - trajektoria")
plt.xlabel("x1")
plt.ylabel("x2")
cbar= plt.colorbar()
cbar.set_label("koszt")
plt.savefig(f"{lib}_ {alg}_{task}_trajectory_id{id}.{ext}")


#os.system("ffmpeg -r 5 -i plots/plot_%d.png -vcodec mpeg4 -y plots/scatter3.mp4")
#os.system("convert -delay 20 -loop 0 plots/plot_{0..33}.png plots/scatter4.gif") 
# gifCommand = "convert -delay 20 -loop 0 plot_{0..33}.png MC_zad1_ANIM.gif"