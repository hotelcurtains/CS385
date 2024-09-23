import math

for n in range(1, 10000):
    if ((4*math.pow(n,3)) < (64*n*math.log2(n))): 
        print(n)
        break