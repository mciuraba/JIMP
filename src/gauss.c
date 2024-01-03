#include "gauss.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */

int eliminate(Matrix* mat, Matrix* b) {
    double diagonalny = 0;
    double stala_w = 0;
    double stala_k = 0;
    
    for( int k = 0; k < mat -> r-1; ++k ) {
 
        wybor_diagonali(mat, b, k);
        stala_k = b->data[k][0];
        diagonalny = mat -> data[k][k];

        for( int j = k+1; j < b -> r; ++j ) {
            stala_w = mat->data[j][k];
            b->data[j][0] -= stala_w * stala_k / diagonalny;
        }
        for( int i = mat -> c-1; i >= k; --i ) {
            stala_k = mat->data[k][i];

            for( int j=k+1; j < mat->r; ++j ) {
                stala_w = mat->data[j][k];
                mat->data[j][i] -= stala_w * stala_k / diagonalny;
            }
        }
    }
    
    return 0;
}

int wybor_diagonali(Matrix* mat, Matrix* b, int k) {
    int index = k;
    for( int j = k+1; j < mat->r; ++j ){

        if( abs( mat->data[j][k] ) > abs( mat->data[index][k])){
            index = j;
	}

    }

    if( abs( mat->data[index][k] ) == 0 ) {
        return 1;
    }

    if( zamiana_wierszy(mat, k, index) == 1 )
        return 1;
        
    if( zamiana_wierszy(b, k, index) == 1 )
        return 1;
    
    return 0;
}

int zamiana_wierszy(Matrix* mat, int x, int y) {
    if( x == y ){
        return 0;
    }
    if( x >= mat->r || y >= mat->r ){
        return 1;
    }
   
    double* v = mat->data[x];
    mat->data[x] = mat->data[y];
    mat->data[y] = v;
   
    return 0;
}
