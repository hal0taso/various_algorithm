#!/usr/bin/env python3
# -*- coding : utf-8 -*-
from z3 import *
import sys

n = 4

x = [[Int("x[%d,%d]" % (i,j)) for j in range(n)] for i in range(n)]
s = Solver()

for i in range(n):
    for j in range(n):
        s.add(1 <= x[i][j], x[i][j] <= n*n)

# all numbers are unique
s.add(Distinct(sum(x, [])))

# all rows have same sum
for i in range(1, n):
    s.add(sum(x[0]) == sum(x[i]))

# all columns have same sum
for j in range(1, n):
    s.add(sum(map(lambda row: row[0], x)) == sum(map(lambda row: row[j], x)))

s.check()
m = s.model()

for i in range(n):
    for j in range(n):
        sys.stdout.write(" %2d" % m[ x[i][j] ].as_long())
    sys.stdout.write("\n")

