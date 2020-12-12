import numpy as np
from matplotlib import pyplot as plt
import datetime
import os

# def stringToDate(dateStr):
#     d = dateStr.replace('-','')
#     d = d.replace('_','')
#     d = d.replace(':','')
#     return datetime.datetime.strptime(d,'%Y%m%d%H%M%S')


# dateStr = ""
# paramsDict = {}
# loopType = ""
# logContent = []
# indices = []

# keywords = ["$INFO$", "$DATE$", "$PARAMS$", "$TYPE$", "$DATA$"]

# #open log file and read data

# with open("logs/log_2020-12-12_20:39:58.txt", "r") as f:
#     logContent = f.readlines()

# #remove ends of line
# logContent = [x.rstrip() for x in logContent] 

# #get ids of log keywords
# for elem in keywords:
#     indices.append(logContent.index(elem))

# #date 
# date = stringToDate(logContent[indices[1]+1])

# #params
# #read paramteres of the algorithm to dictionary
# for elem in logContent[(indices[2]+1):indices[3]]:
#     currentline = elem.split(",")
#     paramsDict[currentline[0]]=currentline[1]

# #type - serial or openMP
# loopType = logContent[indices[3]+1]

# #data
# #get data
# iterations = []
# costs = []

# for elem in logContent[indices[4]+1:len(logContent)]:
#     currentline = elem.split(",")
#     iterations.append(int(currentline[0]))
#     costs.append(float(currentline[1]))

# #plot
# plt.figure(0)
# myTitle = "PSO_"+loopType+" dla: "+paramsDict["AmountOfParticles"] + " czastek"
# plt.plot(iterations, costs)
# plt.xticks(np.arange(0, max(iterations)+2, 5.0))
# plt.xlabel("iteracje")
# plt.ylabel("koszt")
# plt.title(myTitle)
# plt.show()
# #plt.savefig("PSO_koszt.png")    

# ######################################################################
# # Funkcje ktore optymalizujemy

# import math

# N = 100 # resolution for given range x_min - x_max
# x_min = -10
# x_max = 10

# x_range=np.linspace(x_min, x_max, N, endpoint=True)

# def funkcja1(x,n):

#     suma = np.sum(math.pow(x,2))   
#     x = np.repeat(x,n)
#     n = np.arange(1,n+1,1)
#     x2 = x/n
#     arg = [math.cos(i) for i in x2]    
#     prod = np.prod(arg)   

#     return 1/40 * suma + 1 - prod

# #tylko dla n=2
# def funkcja2(x, xi):

#     return 100*math.pow((xi-math.pow(x,2)),2) + math.pow((1-x),2)

# n=2
# y = [funkcja1(x, n) for x in x_range]

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

# file: iteracja, id, x, y , vx, vy

with open("logs/particlesLog_2020-12-12_20:30:15.txt", "r") as f:
    logParticles = f.readlines()

logParticles = [x.rstrip() for x in logParticles] 

n = 2 # wymiary
N = 25 # czastki
arr = np.empty((0,6), float)

for line in logParticles:
    lineSplit = line.split(",")
    lineFloat = [float(x) for x in lineSplit]
    arr = np.append(arr, np.array([lineFloat]), axis=0)

rows = arr.shape[0]
iterations =int(rows / N)
arr = np.reshape(arr,(iterations, N, 6))



plt.figure(3)
plt.scatter(arr[0,:,2], arr[0,:,3])
plt.show()


from matplotlib import cm
import numpy as np
from celluloid import Camera

camera = Camera(plt.figure())
for i in range(iterations):
    plt.scatter(arr[i,:,2], arr[i,:,3])
    camera.snap()
anim = camera.animate(blit=True)
anim.save('scatter.mp4')











