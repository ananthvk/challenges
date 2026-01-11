# generate 100 random numbers
import random
import sys
num = 1000
maxval = 100
if(len(sys.argv) > 2):
    try:
        maxval = int(sys.argv[1])
        num = int(sys.argv[2])
    except Exception as e:
        sys.exit(-1)

nums = ['%s' %random.randint(1,maxval) for i in range(num)]
print(num, ' '.join(nums))
