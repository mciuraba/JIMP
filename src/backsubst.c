#include "backsubst.h"

#include <stdio.h>
/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
int backsubst(Matrix *x, Matrix *mat, Matrix *b) {
    // sprawdzenie rozmiarów macierzy
	if( mat->r != mat->c || b->r != mat->r || b->c != 1 ) {
		return 2;
	}
	
    // przypisanie odpowiadajacych wartosci z macierzy b do macierzy x
	for( int i = 0; i < x->r; i++){
		x->data[i][0] = b -> data[i][0];
	}	

    // wykoywanie reszty działań
	for (int i = mat->r - 1; i >= 0; --i) {
        if (mat->data[i][i] == 0) { // błąd dzielenia przez 0
            return 1;
        }

        for (int j = i + 1; j < mat->c; ++j) {
            x->data[i][0] -= mat->data[i][j] * x->data[j][0];
        }
        
        x->data[i][0] /= mat->data[i][i];
  	}

	return 0;
}
