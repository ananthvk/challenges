import random

def gen_test(max_tests, max_n, max_a):
    print(max_tests)
    for i in range(max_tests):
        n = random.randint(1, max_n)
        tc = [str(random.randint(0, max_a)) for i in range(max_n)]
        print(n)
        print(' '.join(tc))

gen_test(10, 10, 100)