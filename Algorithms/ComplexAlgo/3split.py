import numpy as np
import math

def poly_cof_print(p):
    st1 = ",".join([str(elem) for elem in p])
    print(st1)

"""
    m = termini polinomio
    i = grado split
    restiuisce le varie possibili taglie di n per i termini di grado minore.
"""
def get_3split_params(m, i):
    n_min = math.ceil(m / i)
    n_max = math.floor((2*m) / ((2*i)-1))
    return [n_min, n_max]

def mod3(poly):
    ris_mod3 = []
    for coff in poly.coef:
        ris_mod3.append(complex(coff.real%3,coff.imag%3))
    return np.poly1d(ris_mod3)

def mul_img(poly):
    return mod3(np.poly1d(np.polymul(mod3(poly), 1j)))

def poly_sum(p1, p2):
    return  mod3(np.polyadd(mod3(p1),mod3(p2)))

def neg_poly(p1):
    return mod3(np.polymul(mod3(p1),-1))

def poly_mul(p1,p2):
    return mod3(np.polymul(mod3(p1),mod3(p2)))


def split3(a0,a1,a2,b0,b1,b2, n, k):
    A0 = np.poly1d(a0)
    A1 = np.poly1d(a1)
    A2 = np.poly1d(a2)
    #S1 = poly_sum(A0, A2)
    #S2 = poly_sum(S1, A1)
    #S3 = poly_sum(S1, neg_poly(A1))
    #S4 = poly_sum(A0, neg_poly(A2))
    #S5 = poly_sum(S4, mul_img(A1))

    B0 = np.poly1d(b0)
    B1 = np.poly1d(b1)
    B2 = np.poly1d(b2)
    #S1_B = poly_sum(B0, B2)
    #S2_B = poly_sum(S1_B, B1)
    #S3_B = poly_sum(S1_B, neg_poly(B1))
    #S4_B = poly_sum(B0, neg_poly(B2))
    #S5_B = poly_sum(S4_B, mul_img(B1))

    P0 = poly_mul(A0,B0)
    P1 = poly_mul(poly_sum(poly_sum(A0,A1),A2), poly_sum(poly_sum(B0,B1),B2))
    P2 = poly_mul(poly_sum(poly_sum(A0, neg_poly(A1)),A2), poly_sum(poly_sum(B0, neg_poly(B1)),B2))
    P3 = poly_mul(poly_sum(poly_sum(A0,mul_img(A1)),neg_poly(A2)), poly_sum(poly_sum(B0,mul_img(B1)), neg_poly(B2)))
    P4 = poly_mul(A2,B2)

    Q1 = poly_sum(P1, neg_poly(P2))
    Q2 = poly_sum(P1, P2)
    Q3 = poly_sum(P0, P4)
    R2 = poly_sum(neg_poly(Q2), neg_poly(Q3))
    Q5 = poly_sum(Q2, neg_poly(Q3))
    Q6 = poly_sum(Q5, neg_poly(P3))
    R1 = poly_sum(Q1, neg_poly(mul_img(Q6)))
    R3 = poly_sum(Q1, mul_img(Q6))


    ris_degree = 2*((2*n)+k) -1  # Grado massimo del polinomio finale
    result = [0] * ris_degree

    P0,R1,R2,R3,P4 = P0.c, R1.c, R2.c, R3.c, P4.c

    for i in range(len(P0)): #P0 * X^0
        result[i] += P0[i]

    for i in range(len(R1)): #R1 * X^n
        result[i + n] += R1[i]

    for i in range(len(R2)): #R2 * X^(2n)
        result[i + 2 * n] += R2[i]

    for i in range(len(R3)): #R3 * X^(3n)
        result[i + 3 * n] += R3[i]

    for i in range(len(P4)): #P4 * X^(4n)
        result[i + (3*n)+k] += P4[i]

    #print(result)
    return mod3(np.poly1d(result))


def main():
    p1 = [2+1j, 1+3j, 0+2j, 3+0j, 2+2j, 1+0j]
    p2 = [3+2j, 1+1j, 0+3j, 2+0j, 3+1j, 1+2j]
    m = 6
    i = 3

    n = get_3split_params(m,i)[0] #prendo prima sempre minimo
    k = m - (2*n)
    print(n, k)

    ris_expected = mod3(np.polymul(np.poly1d(p1),np.poly1d(p2)))
    print("Excpeted:")
    poly_cof_print(ris_expected)
    ris_actual = split3(p1[0:n],p1[n:2*n],p1[2*n:m], p2[0:n], p2[n:2*n], p2[2*n:m], n,k)
    print("Actual:")
    poly_cof_print(ris_actual)

main()