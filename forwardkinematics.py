#####   七自由度机械臂“织女”的运动学正解函数    #####
#DH参数：
#input： 关节角（theta1，theta2，theta3，theta4，theta5，theta6，theta7）
#output： 三维坐标点，机械臂基座标系下，

import numpy
from numpy import *
theta1 = 0
theta2 = 0
theta3 = 0
theta4 = 0
theta5 = 0
theta6 = 0
theta7 = 0

DH = mat([ 0 , 0 , 405.5 , theta1],
         [90 , 0 ,  0 ,    theta2]
         [-90 , 0 , 0 ,    theta3],
         [ 90 , -68 , 355.5 , theta4],
         [ -90 , 68 , 390.5 , theta5],
         [ 90 , 0 , 0 ,    theta6],
         [ 90 , 90 , 130.2 , theta7],)
#### 转换矩阵
T01 = mat([])
T12 = mat([])
T23 = mat([])
T34 = mat([])
T45 = mat([])
T56 = mat([])
T67 = mat([])
T07 = T01*T12*T23*T34*T45*T56*T67
#### 坐标转换 ###
P7 = mat()
P0 = T07*P7
###


