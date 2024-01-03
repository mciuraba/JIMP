#include "gauss.h"

#include <stdio.h>

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix* mat, Matrix* b) {
    double diag = 0.;
    double r_const = 0.;    // stała wierszowa służąca do wymnażania elementów macierzy
    double c_const = 0.;    // stała kolumnowa służąca do wymnażania elementów macierzy
    
    for( int k=0; k < mat->r - 1; ++k ) {
        // selekcja elementu diagonalnego
        diag_select(mat, b, k);
        diag = mat->data[k][k];
        
        // zmiana wartości elementów w macierzy b
        c_const = b->data[k][0];
        
        for( int j=k+1; j < b->r; ++j ) {
            r_const = mat->data[j][k];
            b->data[j][0] -= r_const * c_const / diag;
        }
        
        // zmiana wartości elementów w macierzy A
        for( int i = mat->c - 1; i >= k; --i ) {
            c_const = mat->data[k][i];

            for( int j=k+1; j < mat->r; ++j ) {
                r_const = mat->data[j][k];
                mat->data[j][i] -= r_const * c_const / diag;
            }
        }
    }
    
    return 0;
}

int diag_select(Matrix* mat, Matrix* b, int col) {
    int max_idx = col; // ustawienie indeksu z maksymalną wartością na element diagonali
    
    for( int j = col+1; j < mat->r; ++j ) { // iterowanie po pozostałych elementach i-tej kolumny
        if( ABS( mat->data[j][col] ) > ABS( mat->data[ max_idx ][col] ) ) {
            max_idx = j;
        }
    }
    
    // sprawdzanie, czy sprawdzana macierz jest macierzą osobliwą (występuje dzielenie przez 0)
    if( ABS( mat->data[ max_idx ][col] ) == 0 ) {
        return 1;
    }
    
    // zamiana miejscami wierszy (dodatkowo obsluga błędów)
    if( switch_rows( mat, col, max_idx ) == 1 )
        return 1;
        
    if( switch_rows( b, col, max_idx ) == 1 )
        return 1;
    
    return 0;
}

int switch_rows(Matrix* mat, int a, int b) {
    if( a == b ) { // nie potrzeba zmiany
        return 0;
    }
    if( a >= mat->r || b >= mat->r ) { // sprawdzenie, czy nie wyjdzie poza zakres macierzy
        return 1;
    }
    
    // zamiana wskaźników miejscami
    double* v = mat->data[a];
    mat->data[a] = mat->data[b];
    mat->data[b] = v;
    
    return 0;
}
