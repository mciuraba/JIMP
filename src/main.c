#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"

#include <stdlib.h>
#include <stdio.h>


int main(int argc, char ** argv) {
	int res;
	Matrix * A = readFromFile(argv[1]);
	Matrix * b = readFromFile(argv[2]);
	Matrix * x;

	if (A == NULL) return -1;
	if (b == NULL) return -2;
	printToScreen(A);
	printToScreen(b);
    // printf( "--------------------\n" );

	res = eliminate(A,b);
    if( res != 0 ) { // wystąpił jakiś błąd
        fprintf( stderr, "%s: błąd: nie udało się przeprowadzić eliminacji Gauss\'a!\n", argv[0] );
        
        freeMatrix(A);
        freeMatrix(b);
        return 1;
    }
    /* printToScreen(A);
    printToScreen(b);
    printf( "--------------------\n" ); */
    
	x = createMatrix(b->r, 1);
	if (x != NULL) {
		res = backsubst(x,A,b);
        if( res != 0 ) { // wystąpił jakiś błąd
            fprintf( stderr, "%s: błąd: nie udało się przeprowadzić podstawienia wstecznego!\n", argv[0] );
            
            if( res == 1 ) { // błąd dzielenia przez zero
                fprintf( stderr, "%s: opis błędu: napotkano dzielenie przez zero!\n", argv[0] );
            }
            else { // błąd nieprawidłlowych rozmiarów macierzy
                fprintf( stderr, "%s: opis błędu: nieprawidłowy rozmiar macierzy!\n", argv[0] );
            }
            
            freeMatrix(A);
            freeMatrix(b);
            freeMatrix(x);
            return 1;
        }

		printToScreen(x);
        freeMatrix(x);
	}
    else {
        fprintf( stderr, "%s: błąd: nie mogłem utworzyć wektora wynikowego x!\n", argv[0] );
	}

    // Zwalnianie pamięci
	freeMatrix(A);
	freeMatrix(b);

	return 0;
}
