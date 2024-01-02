#include "backsubst.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
int  backsubst(Matrix *x, Matrix *mat, Matrix *b){
	if(mat->r =! mat->c || b->r != mat->r || b->c != 1){
		printf("Bledny rozmiar macierzy!\n");
		return 2;
	}	

	for (int i =0; i < x->r; i++) {
		x->data[i][0] = b->data[i][0];
	}

	for (int i = mat->r - 1; i >= 0; i--) {
    		if (mat->data[i][i] == 0) {
      			printf("Błąd dzielenia przez 0!\n");
      			return 1;
    		}

    		x->data[i][0] /= mat->data[i][i];

    		for (int j = i + 1; j < mat->r; j++) {
      			x->data[i][0] -= mat->data[i][j] * x->data[j][0];
    		}
  	}

	return 0;
}


