#!/usr/bin/python
from random import Random
rand = Random()
n = 75
S = []

min = 0
max = 255

while len(S) < n:
	i = rand.randint(min, max)
	if not i in S:
		S.append(i)

print(S)
