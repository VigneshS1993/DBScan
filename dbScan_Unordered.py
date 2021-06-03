# -*- coding: utf-8 -*-
"""
Created on Thu Jun  3 21:34:17 2021

@author: Vignesh
@Topic: DBScan Unordered
"""

from dataclasses import dataclass
import matplotlib.pyplot as plt
import math as mt
import numpy as np

def distance(x1, y1, x2, y2):
    return mt.sqrt((x1 - x2)**2 + (y2 - y1)**2)

@dataclass
class Point:
    x: float
    y: float
    status: int = 0
    pointType: int = -1    

def orderedDBScan(x, y, epsilon):
    p = [Point(x[i], y[i]) for i in range(len(x))]
    len1 = len(p)
    print(len1)
    i = 0
    count = 0
    cluster = 0
    j = 0
    while i < len1:
        if p[i].pointType == -1:   # New cluster
            cluster += 1
            j = 0
            while(j < len1):
                if j != i:
                    if distance(p[i].x, p[i].y, p[j].x, p[j].y) < epsilon:
                        p[i].pointType = cluster
                        p[j].pointType = cluster
                        count += 1
                j += 1
            if count == 0:
                cluster -= 1
            count = 0
        else:
            j = 0
            while(j < len1):
                if j != i:
                    if distance(p[i].x, p[i].y, p[j].x, p[j].y) < epsilon:
                        p[j].pointType = p[i].pointType
                j += 1
        i += 1
    return p

if __name__ == '__main__':
    #num = int(input('Enter the number of coordinates..'))
    ## Sample x, y data
    x = [19.111841, 19.137815, 19.119677, 19.119677, 19.119677, 19.120217, 19.120217, 19.119677, 19.119677, 19.119677,19.111342, 19.111342,  19.11186, 19.11186, 19.119677, 19.119677, 19.119677, 19.137815, 19.11538, 19.11538, 19.116168, 19.119677, 19.137815, 19.137815, 19.112955, 19.112955, 19.112955, 19.119677, 19.119677, 19.11538, 19.119677, 19.119677, 19.119677, 19.119677, 19.119677, 19.11186, 19.111841, 19.131674, 19.119677, 19.11186, 19.11186, 19.111841, 19.111841, 19.111841, 19.11538, 19.116625, 19.115671, 19.119677, 19.119677, 19.119677, 19.116183, 19.113827, 19.119677, 19.1141, 19.107491, 19.119677]
    y = [72.910729, 72.908387, 72.914085, 72.905081, 72.905081, 72.905081, 72.907121, 72.907121, 72.905081, 72.905081, 72.905081, 72.908387,  72.911346, 72.911346, 72.905081, 72.905081, 72.905081, 72.914085, 72.909144, 72.909144, 72.909573, 72.905081, 72.914085, 72.914085, 72.910102, 72.910102, 72.910102, 72.905081, 72.905081, 72.909144, 72.905081, 72.905081, 72.905081, 72.905081, 72.905081, 72.911346, 72.910729, 72.91851, 72.905081, 72.911346, 72.911346, 72.910729, 72.910729, 72.910729, 72.909144, 72.909185, 72.908985, 72.905081, 72.905081, 72.905081, 72.909646, 72.893833, 72.905081, 72.894985, 72.90176, 72.905081]
    epsilon = 0.005
    p = orderedDBScan(x, y, epsilon)
    list1 = []
    list2 = []
    for i in range(len(p)):
        print(p[i].pointType)
        list1.append(p[i].pointType)
    
    unique_labels = set(list1)
    colors = [plt.cm.Spectral(each) for each in np.linspace(0, 1, len(unique_labels))]
    print(len(colors))
    print(unique_labels)
    for k, col in zip(unique_labels, colors):
        print(col)
    for i in range(len(p)):
        if p[i].pointType != -1:
            plt.plot(p[i].x, p[i].y, 'o', markerfacecolor=tuple(colors[p[i].pointType - 1]), markersize=20)
        else:
            plt.plot(p[i].x, p[i].y, 'o', markerfacecolor=tuple([0, 0, 0, 1]), markersize=20)
    plt.show()
        
                    
    
    
    

