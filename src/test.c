#include "test.h"
#include "gauss.h"
#include "backsubst.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void start_tests( char* program_name ) {
// ALOKACJA PAMIĘCI
    test_t* tests_arr = (test_t*) malloc( TESTS_COUNT * sizeof *tests_arr );
    if( tests_arr == NULL ) { // zabezpieczenie
        return;
    }
    
// INICJALIZACJA TESTÓW
    char str_A[BUFSIZE], str_b[BUFSIZE], str_x[BUFSIZE];
    
    for( int i=0; i < TESTS_COUNT; ++i ) {
        sprintf( str_A, "dane/A%d", i+1 );
        sprintf( str_b, "dane/b%d", i+1 );
        sprintf( str_x, "dane/x%d_exp", i+1 );
        tests_arr[i] = init_test( readFromFile( str_A ), readFromFile( str_b ), readFromFile( str_x ) );
    }
    
// WYKONYWANIE TESTÓW
    int res = 0;
    
    for( int i=0; i < TESTS_COUNT; ++i ) {
        printf( "========== TEST %d: ==========\n", i+1 );
        
        printf( "  -> Macierz A:\n" );
        printToScreen( tests_arr[i].A );
        printf( "\n" );
        
        printf( "  -> Macierz b:\n" );
        printToScreen( tests_arr[i].b );
        printf( "-----------------------------\n" );
        
        printf( " Spodziewany wynik:\n" );
        printToScreen( tests_arr[i].expected_x );
        printf( "-----------------------------\n" );
        
        printf( " Rzeczywisty wynik:\n" );
        res = do_test( &(tests_arr[i]) ); // wykonanie i-tego testu
        if( res == 0 ) {
            printToScreen( tests_arr[i].x );
        }
        else if( res == 1 ) { // błąd wczytywania macierzy
            fprintf( stderr, "%s: błąd: nie udało się wczytać macierzy w teście numer %d!\n", program_name , i+1 );
        }
        else if( res == 2 ) { //jakiś błąd
            fprintf( stderr, "%s: błąd: nie udało się przeprowadzić eliminacji Gauss\'a dla testu numer %d!\n", program_name , i+1 );
        }
        else if( res > 2 ) { // błąd podczas przeprowadzania podstawienia wstecznego
            fprintf( stderr, "%s: błąd: nie udało się przeprowadzić podstawienia wstecznego dla testu numer %d!\n", program_name, i+1 );
            
            // Opisy błędów dla podstawienia wstecznego
            if( res == 3 ) {
                fprintf( stderr, "%s: opis błędu: napotkano dzielenie przez zero!\n", program_name );
            }
            else if( res == 4 ) {
                fprintf( stderr, "%s: opis błędu: nieprawidłowy rozmiar macierzy!\n", program_name );
            }
        }
        printf( "-----------------------------\n" );
        
        printf( "=============================\n\n\n\n\n" );
    }
    




    
// ZWALNIANIE PAMIĘCI
    for( int i=0; i < TESTS_COUNT; ++i ) {
        free_test( tests_arr[i] );
    }
    free( tests_arr );
}

test_t init_test( Matrix* A, Matrix* b, Matrix* x_exp ) {
    test_t test;
    test.A = A;
    test.b = b;
    test.expected_x = x_exp;

    test.x = createMatrix( x_exp->r, x_exp->c );
    
    return test;
}

int do_test( test_t* test_ptr ) {
    // sprawdza poprawność wczytania i wygenerowania macierzy; zwróci błąd wczytania macierzy, jeżeli taki występuje
    if( test_ptr->A == NULL || test_ptr->b == NULL || test_ptr->x == NULL || test_ptr->expected_x == NULL ) {
        return 1;
    }
    
    
    int res = 0;
    
    // wykonanie eliminacji Gauss'a
    res = eliminate( test_ptr->A, test_ptr->b );
    if( res != 0 ) { // wystąpił jakiś błąd (bliżej nieokreślony)
        return 2;
    }

    // wykonanie podstawiania wstecznego
    res = backsubst( test_ptr->x, test_ptr->A, test_ptr->b );
    if( res != 0 ) { // wystąpił jakiś błąd
        if( res == 1 ) { // błąd dzielenia przez zero
            return 3;
        }
        else { // błąd nieprawidłlowych rozmiarów macierzy
            return 4;
        }
    }
    
    return 0; // sukces
}

void free_test( test_t test ) {
    freeMatrix( test.A );
    freeMatrix( test.b );
    freeMatrix( test.x );
    freeMatrix( test.expected_x );
}
