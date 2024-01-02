#include "gauss.h"

#include <stdio.h>

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix* mat, Matrix* b) {
// selekcja elementu diagonalnego
    // szukanie indeksu
    int max_idx = 0;
    
    for( int i=0; i < mat->c - 1; ++i ) { // iterowanie po kolumnach
        max_idx = i; // ustawienie indeks z maksymalną wartością na element diagonali
        
        for( int j = i+1; j < mat->r; ++j ) { // iterowanie po pozostałych elementach i-tej kolumny
            if( ABS( mat->data[j][i] ) > ABS( mat->data[ max_idx ][i] ) ) {
                max_idx = j;
            }
        }
        
        // sprawdzanie, czy sprawdzana macierz jest macierzą osobliwą (występuje dzielenie przez 0)
        if( ABS( mat->data[ max_idx ][i] ) == 0 ) {
            return 1;
        }
        
        // zamiana miejscami wierszy
        if( switch_rows( mat, i, max_idx ) == 1 )
            return 1;
            
        if( switch_rows( b, i, max_idx ) == 1 )
            return 1;
    }
    
    
// eliminacja gaussa
    double diag = 0.;
    double r_const = 0.;
    
    for( int k=0; k < mat->r - 1; ++ k ) {
        diag = mat->data[k][k];
        
        // zmiana wartości w macierzy A
        for( int i=k; i < mat->c - 1; ++i ) {
            r_const = mat->data[k][i];
            
            for( int j = i+1; j < mat->r; ++j ) {
                mat->data[j][i] -= mat->data[j][i] * r_const / diag;
            }
        }
        
        // zmiana wartości w macierzy b
        for( int i=k; i < b->c - 1; ++i ) {
            r_const = b->data[k][i];
            
            for( int j = i+1; j < b->r; ++j ) {
                b->data[j][i] -= b->data[j][i] * r_const / diag;
            }
        }
    }
    
    return 0;
}

int switch_rows(Matrix* mat, int a, int b) {
    if( a == b ) { // nie potrzeba zmiany
        return 0;
    }
    if( a >= mat->r || b >= mat->r ) { // sprawdzenie, czy nie wyjdzie poza zakres macierzy
        return 1;
    }
    
    double* v = mat->data[a];
    mat->data[a] = mat->data[b];
    mat->data[b] = v;
    
    return 0;
}
