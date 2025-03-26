import numpy as np
from numpy.polynomial import Polynomial
import math

class F9Poly:
    def __init__(self, coef):
        cof = np.array(coef, dtype=complex)
        if len(cof) == 0:
            self.p = Polynomial([complex(0,0)])
            return
        cof_mod = np.vectorize(lambda z: complex(int(z.real) % 3, int(z.imag) % 3))(cof)
        self.p = Polynomial(cof_mod)

    def mul_img(self):
        ris = self.p * complex(0,1)
        return F9Poly(ris.coef)

    def poly_mul(self, p2):
        ris = self.p * p2.p
        return F9Poly(ris.coef)

    def poly_neg(self):
        ris = self.p * -1
        return F9Poly(ris.coef)

    def poly_sum(self, p2):
        ris = self.p + p2.p
        return F9Poly(ris.coef)

    def poly_cof(self):
        return self.p.coef

    def poly_num_terms(self):
        return len(self.p.coef)

    def print_poly(self):
        print(self.p)

    def redux(self):
        p_cof = self.p.coef
        while p_cof[-1] == complex(0,0):
            p_cof = p_cof[:-1]
        return  F9Poly(p_cof)

def get_3split_params(m, i):
    n_min = math.ceil(m / i)
    n_max = math.floor((2*m) / ((2*i)-1))
    return [n_min, n_max]

def params(m,i):
    n = get_3split_params(m,i)[0]
    k = m - (2*n)
    return n,k

def split3_recursive(p1, p2, m):
    ##assert p1.poly_num_terms() == p2.poly_num_terms() == m, (p1.poly_cof(),p2.poly_cof(),m)
    n, k = params(p1.poly_num_terms(),3)
    tot_dim = (2 * n) + k

    if tot_dim < 6 :
        ris = p1.poly_mul(p2)
        return ris

    A0 = F9Poly(p1.poly_cof()[0:n])
    A1 = F9Poly(p1.poly_cof()[n:2*n])
    A2 = F9Poly(p1.poly_cof()[2*n:])

    B0 = F9Poly(p2.poly_cof()[0:n])
    B1 = F9Poly(p2.poly_cof()[n:2*n])
    B2 = F9Poly(p2.poly_cof()[2*n:])


    P0 = split3_recursive(A0,B0, n)

    P1 = split3_recursive(A0.poly_sum(A1).poly_sum(A2), B0.poly_sum(B1).poly_sum(B2), n)

    neg_A1 = A1.poly_neg()
    neg_B1 = B1.poly_neg()
    P2 = split3_recursive(A0.poly_sum(neg_A1).poly_sum(A2), B0.poly_sum(neg_B1).poly_sum(B2), n)

    neg_A2 = A2.poly_neg()
    neg_B2 = B2.poly_neg()
    A1w =  A1.mul_img()
    B1w = B1.mul_img()
    P3 = split3_recursive(A0.poly_sum(A1w).poly_sum(neg_A2), B0.poly_sum(B1w).poly_sum(neg_B2), n)

    P4 = split3_recursive(A2,B2,k)

    Q1 = P1.poly_sum(P2.poly_neg())
    Q2 = P1.poly_sum(P2)
    Q3 = P0.poly_sum(P4)
    R2 = Q2.poly_neg().poly_sum(Q3.poly_neg())
    Q5 = Q2.poly_sum(Q3.poly_neg())
    Q6 = Q5.poly_sum(P3.poly_neg())
    R1 = Q1.poly_sum(Q6.mul_img().poly_neg())
    R3 = Q1.poly_sum(Q6.mul_img())

    P0_c,R1_c,R2_c,R3_c,P4_c = P0.poly_cof(), R1.poly_cof(), R2.poly_cof(), R3.poly_cof(), P4.poly_cof()
    ris_degree = (2*tot_dim)-1
    #result = [complex(0,0)] * ris_degree
    result = [complex(0,0)] * ris_degree*2


    for i in range(P0.poly_num_terms()): # P0 * X^0
        result[i] += P0_c[i]
    #print(result)

    for i in range(R1.poly_num_terms()): # R1 * X^n
        #assert i+n < ris_degree, (i+n,R1.poly_cof())
        result[i + n] += R1_c[i]
    #print(result)

    for i in range(R2.poly_num_terms()): # R2 * X^(2n)
        if R2_c[i] == complex(0,0):
            continue
        #assert i+2*n < ris_degree, (i+2*n,R2.poly_cof())
        result[i + 2 * n] += R2_c[i]
    #print(result)

    for i in range(R3.poly_num_terms()): # R3 * X^(3n)
        if R3_c[i] == complex(0,0):
            continue
        #assert i+3*n < ris_degree, (i+3*n,R3.poly_cof())
        result[i + 3 * n] += R3_c[i]
    #print(result)

    for i in range(P4.poly_num_terms()): # P4 * X^(4n)
        if P4_c[i] == complex(0,0):
            continue
        #assert i+4*n < ris_degree, (i+4*n,P4.poly_cof(),ris_degree)
        result[i + 4 * n] += P4_c[i]

    #print("last",result)
    return F9Poly(result)

def poly_equals(p1,p2):
    if len(p1) != len(p2): return False
    for i in range(0,len(p1)):
        if p1[i] != p2[i]: return False
    return True

def main():

    #c1 = [(0.+2.j), (1.+1.j), (1.+2.j), (1.+2.j), (1.+2.j), (2.+2.j), (1.+1.j), (2.+2.j), (1.+0.j), (1.+0.j), (1.+0.j), (2.+2.j), (2.+0.j), (1.+1.j), (1.+2.j), (2.+1.j), (1.+2.j), (0.+1.j), (1.+2.j), (1.+1.j)]
    #c2 = [(1.+1.j),(1.+2.j),(2.+0.j),(0.+2.j),(1.+2.j),(2.+2.j),(0.+2.j),(0.+0.j),(0.+1.j),(1.+2.j),(1.+2.j),(0.+1.j),(0.+2.j),(0.+0.j),(2.+1.j),(2.+1.j),(2.+0.j),(1.+0.j),(1.+1.j),(1.+1.j)]

    terms = 55
    i = 3
    c1 = np.random.randint(1, 100, terms) + 1j * np.random.randint(1, 100, terms)
    c2 = np.random.randint(1, 100, terms) + 1j * np.random.randint(1, 100, terms)
    c1 = np.array(c1, dtype=complex)
    c2 = np.array(c2, dtype=complex)
    print(c1)
    print(c2)

    param = get_3split_params(terms, i)
    print(param)

    n,k = params(terms,i)
    print(n, k)

    #c1.reverse()
    #c2.reverse()
    p1 = F9Poly(c1)
    p2 = F9Poly(c2)
    print("P1: \n",p1.poly_cof())
    print("P2: \n",p2.poly_cof())

    ris_expected = p1.poly_mul(p2)
    ris_actual = split3_recursive(p1,p2,terms)
    ris_reduxed = ris_actual.redux()

    print("Excpeted:", ris_expected.poly_num_terms())
    print(ris_expected.poly_cof())
    print("Actual:", ris_reduxed.poly_cof())
    print(ris_reduxed.poly_cof())
    print("Equals: ",poly_equals(ris_expected.poly_cof(),ris_reduxed.poly_cof()))

main()
