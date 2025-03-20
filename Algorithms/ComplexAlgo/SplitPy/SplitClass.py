import numpy as np
from numpy.lib.polynomial import polymul
from numpy.polynomial import Polynomial
class F9Poly:
    def __init__(self, coef):
        cof = np.array(coef, dtype=complex)
        cof_mod = np.vectorize(lambda z: complex(int(z.real) % 3, int(z.imag) % 3))(cof)
        self.p = Polynomial(cof_mod)

    def mul_img(self):
        ris = self.p * complex(0,1)
        return F9Poly(ris.coef)

    def poly_mul(self, p2):
        ris = self.p * p2.p
        return F9Poly(ris.coef)

    def poly_cof(self):
        return self.p.coef

    def print_poly(self):
        print(self.p)
