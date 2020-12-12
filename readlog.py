import numpy as np
from matplotlib import pyplot as plt
import datetime


def stringToDate(dateStr):
    d = dateStr.replace('-','')
    d = d.replace('_','')
    d = d.replace(':','')
    return datetime.datetime.strptime(d,'%Y%m%d%H%M%S')


dateStr = ""
paramsDict = {}
loopType = ""
logContent = []
indices = []

keywords = ["$INFO$", "$DATE$", "$PARAMS$", "$TYPE$", "$DATA$"]

#open log file and read data
with open("log.txt", "r") as f:
    logContent = f.readlines()

#remove ends of line
logContent = [x.rstrip() for x in logContent] 

#get ids of log keywords
for elem in keywords:
    indices.append(logContent.index(elem))

#date 
date = stringToDate(logContent[indices[1]+1])

#params
#read paramteres of the algorithm to dictionary
for elem in logContent[(indices[2]+1):indices[3]]:
    currentline = elem.split(",")
    paramsDict[currentline[0]]=currentline[1]

#type - serial or openMP
loopType = logContent[indices[3]+1]

#data
#get data
iterations = []
costs = []

for elem in logContent[indices[4]+1:len(logContent)]:
    currentline = elem.split(",")
    iterations.append(int(currentline[0]))
    costs.append(float(currentline[1]))

#plot
myTitle = "PSO_"+loopType+" dla: "+paramsDict["AmountOfParticles"] + " czastek"
plt.plot(iterations, costs)
plt.xticks(np.arange(0, max(iterations)+2, 5.0))
plt.xlabel("iteracje")
plt.ylabel("koszt")
plt.title(myTitle)
plt.savefig("PSO_koszt.png")    