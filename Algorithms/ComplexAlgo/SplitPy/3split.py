import sys
import numpy as np
import math

#sys.setrecursionlimit(10**6)

def poly_cof_print(p):
    st1 = ",".join([str(elem) for elem in p.c])
    print(st1)

def reverse_poly(p, start, end):
    cof = p.c
    cof = cof[start:end][::-1]
    return  np.poly1d(cof)

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
    n = m // 3
    k = m - 2 * n
    if k < 0:
        n -= 1
        k = m - 2 * n
    return n, k

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

def debug_print(p1,p2):
    print("ris intermedio\n")
    print("p1: ",p1)
    print("p2:", p2)
    print("p1*p2",poly_mul(p1,p2))

def split3_recursive(p1,p2, n, k): #TODO fix grado 55 problema nella costruszione dei risultati ricorsivi
    tot_dim = (2 * n + k)
    print("algo: ","n:",n,"k: ",k, "deg tot",tot_dim)

    if tot_dim < 6 or n < 1 or k < 1 : # per grado 55
        #debug_print(p1,p2)
        print("entro nel caso base con:: ","n:",n,"k: ",k, "deg tot",tot_dim)
        return poly_mul(p1,p2)

    ris_degree = 2*tot_dim-1
    result = [0] * ris_degree


    A0 = reverse_poly(p1,0,n)
    A1 = reverse_poly(p1,n,2*n)
    A2 = reverse_poly(p1,2*n,tot_dim)

    B0 = reverse_poly(p2,0,n)
    B1 = reverse_poly(p2,n,2*n)
    B2 = reverse_poly(p2,2*n,tot_dim)
    n_2,k_2 = params(len(A0.c),3)
    P0 = split3_recursive(A0,B0,n_2,k_2)
    n_2,k_2 = params(max(len(A0.c),len(A2.c)),3)
    P1 = split3_recursive(poly_sum(poly_sum(A0,A1),A2), poly_sum(poly_sum(B0,B1),B2),n_2,k_2)
    P2 = split3_recursive(poly_sum(poly_sum(A0, neg_poly(A1)),A2), poly_sum(poly_sum(B0, neg_poly(B1)),B2),n_2,k_2)
    P3 = split3_recursive(poly_sum(poly_sum(A0,mul_img(A1)),neg_poly(A2)), poly_sum(poly_sum(B0,mul_img(B1)), neg_poly(B2)),n_2,k_2)
    n_2,k_2 = params(len(A2.c),3)
    P4 = split3_recursive(A2,B2,n_2,k_2)

    Q1 = poly_sum(P1, neg_poly(P2))
    Q2 = poly_sum(P1, P2)
    Q3 = poly_sum(P0, P4)
    R2 = poly_sum(neg_poly(Q2), neg_poly(Q3))
    Q5 = poly_sum(Q2, neg_poly(Q3))
    Q6 = poly_sum(Q5, neg_poly(P3))
    R1 = poly_sum(Q1, neg_poly(mul_img(Q6)))
    R3 = poly_sum(Q1, mul_img(Q6))


    P0,R1,R2,R3,P4 = P0.c, R1.c, R2.c, R3.c, P4.c
    #print(P0)
    #print(R1)
    #print(R2)
    #print(R3)
    #print(P4)

    for i in range(len(P0)): # P0 * X^0
        result[i] += P0[-i-1]

    #print("P0:",result)

    for i in range(len(R1)): # R1 * X^n
        result[i + n] += R1[-i-1]
    #print("P1:",result)

    for i in range(len(R2)): # R2 * X^(2n)
        result[i + 2 * n] += R2[-i-1]
    #print("P2:",result)

    for i in range(len(R3)): # R3 * X^(3n)
        result[i + 3 * n] += R3[-i-1]
    #print("P3:",result)
    for i in range(len(P4)): # P4 * X^(4n)
        result[i + 4 * n] += P4[-i-1]
    #print("P4:",result)
    return mod3(np.poly1d(result))

def split3(p1,p2, n, k):
    print("Algo1")
    tot_dim = (2 * n + k)

    A0 = reverse_poly(p1,0,n)
    A1 = reverse_poly(p1,n,2*n)
    A2 = reverse_poly(p1,2*n,tot_dim)

    B0 = reverse_poly(p2,0,n)
    B1 = reverse_poly(p2,n,2*n)
    B2 = reverse_poly(p2,2*n,tot_dim)

    P0 = poly_mul(A0,B0)
    debug_print(A0,B0)
    P1 = poly_mul(poly_sum(poly_sum(A0,A1),A2), poly_sum(poly_sum(B0,B1),B2))
    debug_print(poly_sum(poly_sum(A0,A1),A2),poly_sum(poly_sum(B0,B1),B2))
    P2 = poly_mul(poly_sum(poly_sum(A0, neg_poly(A1)),A2), poly_sum(poly_sum(B0, neg_poly(B1)),B2))
    debug_print(poly_sum(poly_sum(A0, neg_poly(A1)),A2),poly_sum(poly_sum(B0, neg_poly(B1)),B2))
    P3 = poly_mul(poly_sum(poly_sum(A0,mul_img(A1)),neg_poly(A2)), poly_sum(poly_sum(B0,mul_img(B1)), neg_poly(B2)))
    debug_print(poly_sum(poly_sum(A0,mul_img(A1)),neg_poly(A2)), poly_sum(poly_sum(B0,mul_img(B1)), neg_poly(B2)))
    P4 = poly_mul(A2,B2)
    debug_print(A2,B2)

    Q1 = poly_sum(P1, neg_poly(P2))
    Q2 = poly_sum(P1, P2)
    Q3 = poly_sum(P0, P4)
    R2 = poly_sum(neg_poly(Q2), neg_poly(Q3))
    Q5 = poly_sum(Q2, neg_poly(Q3))
    Q6 = poly_sum(Q5, neg_poly(P3))
    R1 = poly_sum(Q1, neg_poly(mul_img(Q6)))
    R3 = poly_sum(Q1, mul_img(Q6))


    ris_degree = 2*tot_dim-1
    result = [0] * ris_degree

    P0,R1,R2,R3,P4 = P0.c, R1.c, R2.c, R3.c, P4.c
    print(P0)
    print(R1)
    print(R2)
    print(R3)
    print(P4)

    for i in range(len(P0)): # P0 * X^0
        result[i] += P0[-i-1]

    for i in range(len(R1)): # R1 * X^n
        result[i + n] += R1[-i-1]

    for i in range(len(R2)): # R2 * X^(2n)
        result[i + 2 * n] += R2[-i-1]

    for i in range(len(R3)): # R3 * X^(3n)
        result[i + 3 * n] += R3[-i-1]

    for i in range(len(P4)): # P4 * X^(4n)
        result[i + 4 * n] += P4[-i-1]

    return mod3(np.poly1d(result))

def poly_equals(p1,p2):
    if len(p1) != len(p2): return False
    p1_cof = p1.c
    p2_cof = p2.c
    for i in range(0,len(p1_cof)):
        if p1_cof[i] != p2_cof[i]: return False
    return True


def main():

    #c1 = [2+1j, 1+3j, 0+2j, 3+0j, 2+2j, 1+0j]
    #c2 = [3+2j, 1+1j, 0+3j, 2+0j, 3+1j, 1+2j]

    #c1 = [2+1j, 1+3j, 0+2j, 3+0j, 2+2j, 1+0j, 112+76j, 0+98j]
    #c2 = [3+2j, 1+1j, 0+3j, 2+0j, 3+1j, 1+2j,8+322j, 4+567j]

    #c1 = [1j, (4+4j), (2+1j), (4+2j), (3+1j), (3+1j), 1j, (1+3j), (1+4j), (4+2j), (4+0j), (4+4j), (1+4j), (1+1j), (3+2j), 1j, (3+3j), 0j]
    #c2 = [(1+2j), (4+2j), (3+4j), (4+0j), (2+1j), (3+2j), (4+1j), (1+4j), (4+1j), (2+4j), 2j, 1j, 4j, 1j, (4+3j), (4+2j), (2+2j), (4+0j)]

    #c1 = [(2+4j), (1+3j), (3+1j), (1+2j), (4+4j), (4+3j), (2+1j), (2+1j), (2+4j), (1+2j), (4+1j), (4+2j), (1+4j), (2+1j), (4+2j), (4+1j), (1+3j), (4+3j), (1+4j), (2+3j), (3+3j), (3+3j), (1+2j), (2+3j), (1+2j), (2+1j), (4+2j), (1+2j), (4+3j), (4+1j), (4+4j), (4+1j), (2+2j), (1+2j), (4+2j), (1+3j), (1+2j), (1+3j), (2+2j), (1+1j), (2+2j), (2+1j), (2+4j), (3+3j), (2+1j), (2+4j), (4+4j), (2+3j), (1+3j), (1+1j), (4+1j), (4+3j), (3+2j), (4+2j), (2+1j)]
    #c2 = [(1+3j), (2+4j), (3+1j), (4+3j), (2+4j), (1+4j), (4+3j), (1+1j), (3+3j), (1+3j), (2+3j), (1+1j), (1+3j), (4+2j), (2+3j), (3+4j), (1+3j), (4+1j), (1+4j), (3+3j), (1+1j), (3+2j), (2+1j), (4+4j), (1+2j), (2+3j), (3+4j), (1+4j), (1+2j), (1+2j), (4+2j), (3+3j), (2+1j), (2+1j), (3+4j), (4+3j), (4+3j), (2+2j), (3+1j), (3+4j), (2+4j), (3+2j), (2+3j), (1+2j), (1+3j), (1+1j), (1+3j), (1+2j), (3+1j), (1+4j), (4+1j), (1+3j), (1+2j), (3+1j), (3+4j)]

    terms = 55
    i = 3
    c1 = np.random.randint(2, 5, terms) + 1j * np.random.randint(2, 5, terms)
    c2 = np.random.randint(2, 5, terms) + 1j * np.random.randint(2, 5, terms)
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
    p1 = np.poly1d(c1)
    p2 = np.poly1d(c2)
    print(len(p1))
    print(len(p2))
    print("P1: \n",p1)
    print("P2: \n",p2)
    ris_expected = mod3(np.polymul(p1,p2))

    #ris_actual = split3(p1,p2,n,k)
    ris_actual = split3_recursive(p1,p2,n,k)
    print("Excpeted:", len(ris_expected))
    poly_cof_print(ris_expected)
    print("Actual:", len(ris_actual))
    poly_cof_print(ris_actual)
    print("Equals: ",poly_equals(ris_expected,ris_actual))

main()