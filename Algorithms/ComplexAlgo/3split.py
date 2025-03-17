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

def params(m,i):
    n = get_3split_params(m,i)[0] #prendo prima sempre minimo
    k = m - (2*n)
    return n,k

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


def split3(p1,p2, n, k):

    p1_reversed = p1[::-1]
    p2_reversed = p2[::-1]

    tot_dim = 2 * n + k

    # Divisione corretta dei coefficienti invertiti
    A0 = np.poly1d(p1_reversed[0:n][::-1])
    A1 = np.poly1d(p1_reversed[n:2*n][::-1])
    A2 = np.poly1d(p1_reversed[2*n:tot_dim][::-1])

    B0 = np.poly1d(p2_reversed[0:n][::-1])
    B1 = np.poly1d(p2_reversed[n:2*n][::-1])
    B2 = np.poly1d(p2_reversed[2*n:tot_dim][::-1])

    print("\n",A0)

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


    ris_degree = 2*tot_dim-1  # Grado massimo corretto
    result = [0] * ris_degree

    P0,R1,R2,R3,P4 = P0.c, R1.c, R2.c, R3.c, P4.c

    for i in range(len(P0)):  # P0 * X^0 (nessuno shift)
        result[i] += P0[-i-1]
    print(P0)
    print("Ris P0",result)

    for i in range(len(R1)):  # R1 * X^n (shift a destra)
        result[i + n] += R1[-i-1]
    print("Ris R1",result)

    for i in range(len(R2)):  # R2 * X^(2n) (shift a destra)
        result[i + 2 * n] += R2[-i-1]
    print("Ris R2",result)

    for i in range(len(R3)):  # R3 * X^(3n) (shift a destra)
        result[i + 3 * n] += R3[-i-1]
    print("Ris R3",result)

    for i in range(len(P4)):  # P4 * X^(4n) (shift a destra)
        result[i + 4 * n] += P4[-i-1]  # Correggi anche qui: 4n, non 3n + k
    print("Ris R4",result)

    #print(result)
    return mod3(np.poly1d(result))


def poly_equals(p1,p2):
    if len(p1) != len(p2): return False
    p1_cof = p1.c
    p2_cof = p2.c
    for i in range(0,len(p1_cof)):
        if p1_cof[i] != p2_cof[i]: return False
    return True


def main():
    #p1 = [2+1j, 1+3j, 0+2j, 3+0j, 2+2j, 1+0j]
    #p2 = [3+2j, 1+1j, 0+3j, 2+0j, 3+1j, 1+2j]

    p1 = [2+1j, 1+3j, 0+2j, 3+0j, 2+2j, 1+0j, 112+76j, 0+98j]
    p2 = [3+2j, 1+1j, 0+3j, 2+0j, 3+1j, 1+2j,8+322j, 4+567j]
    m = 8
    i = 3

    n,k = params(m,i)
    print(n, k)

    ris_expected = mod3(np.polymul(np.poly1d(p1),np.poly1d(p2)))

    print("P1: \n",np.poly1d(p1))
    print("P2: \n",np.poly1d(p2))


    ris_actual = split3(p1,p2,n,k)
    ris_actual = np.poly1d(ris_actual.c[::-1])
    print("Excpeted:")
    poly_cof_print(ris_expected)
    print("Actual:")
    poly_cof_print(ris_actual)
    print("Equals: ",poly_equals(ris_expected,ris_actual))

main()