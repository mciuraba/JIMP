#ifndef _GAUSS_H
#define _GAUSS_H

#include "mat_io.h"

#define ABS(a) ( a < 0 ? -a : a ) // makro, które wyrzuca wartość bezwzględną danej liczby

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b);
int zamiana_wierszy(Matrix *mat, int x, int y);
int wybor_diagonali(Matrix *mat, Matrix *b, int k);

#endif
