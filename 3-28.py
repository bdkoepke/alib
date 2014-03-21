#!/usr/bin/python
X  = [6, 5, 3, 1, 7, 6, 2, 3]
Y  = [6*5*3, 5*3*1, 3*1*7, 1*7*6, 7*6*2, 6*2*3, 2*3*6, 3*6*5]
M = []
M.append(Y[1] * Y[4] * X[7])
M.append(Y[2] * Y[5] * X[0])
M.append(Y[3] * Y[6] * X[1])
M.append(Y[4] * Y[7] * X[2])
M.append(Y[5] * Y[0] * X[3])
M.append(Y[6] * Y[1] * X[4])
M.append(Y[7] * Y[2] * X[5])
M.append(Y[0] * Y[3] * X[6])

print(M)
