import unittest
from SplitClass import F9Poly
from parameterized import parameterized
import random


def generate_random_complex_list():
    length = 5 # Lunghezza casuale tra 1 e 5
    return [complex(random.randint(-100, 100), random.randint(-100, 100)) for _ in range(length)]

class TestF9Poly(unittest.TestCase):
    @parameterized.expand([
        ["case1",
            [(-1-4j), 4j, (-6-4j), (-2-3j), (-1-8j)],
            [(2+2j), 1j, (0+2j), (1+0j), (2+1j)]
        ],
        ["case2",
            [(-1+0j), (0+0j), (1+3j)],
            [(2+0j), (0+0j), (1+0j)]
        ],
        ["case3",
            [(-100+344j), (2332+1209j), (100345+4242j)],
            [(2+2j), (1+0j), (1+0j)],
        ],
    ])
    def test_constructor(self,name,cof,expected):
        print(name,cof,expected)

if __name__ == '__main__':
    #print(generate_random_complex_list())
    unittest.main()

