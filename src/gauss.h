#ifndef _GAUSS_H
#define _GAUSS_H

#include "mat_io.h"

#define ABS(a) ( a < 0 ? -a : a )

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix* mat, Matrix* b);              // wykonuje eliminacje Gauss'a
int diag_select(Matrix* mat, Matrix *b, int col);   // wybiera element diagonalny
int switch_rows(Matrix* mat, int a, int b);         // zamienia wiersze miejscami

#endif
