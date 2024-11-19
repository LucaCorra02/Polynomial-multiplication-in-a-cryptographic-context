#include <stdio.h>
#include <stdlib.h>

//considero polinomi su 32 bit
//funzione con grado pollinmimio, legge da un file che prodotto utilizzare

int* schoolbook_recursive(int n, int* p1, int* p2, int* ris){
    if(n==0){return ris;} //caso di uscita
    int max_deg = n - 1;
    int mst_p1 = p1[max_deg]; //termine di grado massimo
    int mst_p2 = p2[max_deg];
    ris[max_deg * 2] += mst_p1 * mst_p2;

    for (int i = 0; i < max_deg; i++){
        ris[max_deg + i] += mst_p1 * p2[i];
    }
    for (int i = 0; i < max_deg; i++){
        ris[max_deg + i] += mst_p2 * p1[i];
    }
    return schoolbook_recursive(n - 1, p1, p2, ris);
}

int* schoolbook_r(int n, int* p1, int* p2) { //n = numero di termini.
    int* ris = calloc((2 * n) - 1, sizeof(int)); // Alloca e inizializza.
    if (n==1) {ris[0] = p1[0] * p2[0]; return ris;} // Caso base, evito la chimata ricorsiva.
    return schoolbook_recursive(n, p1, p2, ris);
}

int main() {

}
