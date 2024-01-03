#include "gauss.h"

#include <stdio.h>
#include <stdlib.h> // dla funkcji abs

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix* mat, Matrix* b) {
    double diagonalny = 0;
    double stala_w = 0;    // stała wierszowa służąca do wymnażania elementów macierzy
    double stala_k = 0;    // stała kolumnowa służąca do wymnażania elementów macierzy
    
    for( int k = 0; k < mat -> r-1; ++k ) {
        // elem. diagonalny
        wybor_diagonalnej(mat, b, k);
        diagonalny = mat -> data[k][k];
        
        // przypisanie stalej kolumnowej
        stala_k = b -> data[k][0];
        
	// macierz b -> zmiana elementow
        for( int j = k+1; j < b -> r; ++j ) {
            stala_w = mat -> data[j][k];
            b -> data[j][0] -= stala_w * stala_k / diagonalny;
        }
        
        // macierz A -> zmiana alementow 
        for( int i = mat -> c-1; i >= k; --i ) {
            stala_k = mat->data[k][i];

            for( int j = k+1; j < mat -> r; ++j ) {
                stala_w = mat->data[j][k];
                mat->data[j][i] -= stala_w *stala_k / diagonalny;
            }
        }
    }
    return 0;
}

int wybor_diagonalnej(Matrix* mat, Matrix* b, int k) {
    int index = k;
    for( int j = k+1; j < mat->r; ++j ){
        if( abs( mat -> data[j][k] ) > abs( mat -> data[index][k] )){
            index = j;
        }
    }
    //jesli osobliwa - zwraca 0
    if( abs( mat -> data[index][k] ) == 0 ) {
        return 1;
    }
    
    // zamiana wierszy
    if( zamiana_wierszy( mat, k, index ) == 1 )
        return 1;
        
    if( zamiana_wierszy( b, k, index ) == 1 )
        return 1;
    
    return 0;
}

int zamiana_wierszy(Matrix* mat, int x, int y) {
    if( x == y ) { // x i y sa rowne, a wiec nie ma po co zamieniac
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


