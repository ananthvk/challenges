import itertools
import numpy as np
import sys


def is_perm(seq):
    return len(set(seq)) == len(seq)

def check_if_super(n):
    arr = np.arange(1, n + 1)
    for perm in itertools.permutations(arr):
        p = (np.cumsum(perm) % n) + 1
        if is_perm(p):
            print(perm)
            return
    print("-1")

check_if_super(int(sys.argv[1]))

"""
> python bruteforce.py 2
(2, 1)
> python bruteforce.py 3
-1
> python bruteforce.py 4
(4, 1, 2, 3)
> python bruteforce.py 5
-1
> python bruteforce.py 6
(6, 1, 4, 3, 2, 5)
> python bruteforce.py 7
-1
> python bruteforce.py 8
(8, 1, 2, 3, 4, 5, 6, 7)
> python bruteforce.py 10
(10, 1, 2, 3, 6, 7, 5, 4, 9, 8)
Note: For odd numbers other than 1, there is no solution
"""
