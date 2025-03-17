import numpy as np

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


def main():
    p1 = [2+1j, 1+3j, 0+2j, 3+0j, 2+2j, 1+0j]
    p2 = [3+2j, 1+1j, 0+3j, 2+0j, 3+1j, 1+2j]

    print(mod3(np.polymul(np.poly1d(p1),np.poly1d(p2))))


    A0 = np.poly1d([2+2j, 1+0j])
    A1 = np.poly1d([0+2j, 3+0j])
    A2 = np.poly1d([2+1j, 1+3j])
    #S1 = poly_sum(A0, A2)
    #S2 = poly_sum(S1, A1)
    #S3 = poly_sum(S1, neg_poly(A1))
    #S4 = poly_sum(A0, neg_poly(A2))
    #S5 = poly_sum(S4, mul_img(A1))

    B0 = np.poly1d([3+1j, 1+2j])
    B1 = np.poly1d([0+3j, 2+0j])
    B2 = np.poly1d([3+2j, 1+1j])
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

    



    print(P0)
    print(R1)
    print(R2)
    print(R3)
    print(P4)



main()