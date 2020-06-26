import time

def timer(func):
    def inner(*args):
        s = time.time()
        func(*args)
        e = time.time()
        print(f'run time is {e-s} seconds')
    return inner

class Cache(object):
    def __init__(self, func):
        self.func = func
        self.cache = {}

    def __call__(self, *args):
        if args not in self.cache:
            self.cache[args] = self.func(*args)
        return self.cache[args]

@Cache
def fibonacci(n):
    if n <= 0:
        return 0
    if n == 1:
        return 1
    return fibonacci(n-1)+fibonacci(n-2)

@timer
def test_runtime():
    print(f'fibonacci(30) = {fibonacci(30)}')

test_runtime()