#ifndef _TEST_H_
#define _TEST_H_

#include "mat_io.h"

#define BUFSIZE 256
#define TESTS_COUNT 6

typedef struct {
    Matrix* A;
    Matrix* b;
    Matrix* x;
    
    Matrix* expected_x;
    
} test_t ;

void start_tests( char* program_name );                     // rozpoczyna wykonywanie wszystkich testów
test_t init_test( Matrix* A, Matrix* b, Matrix* x_exp );    // inicjalizuje pojedyńczy test
int do_test( test_t* );                                     // wykonuje pojedyńczy testy
void free_test( test_t );                                   // zwalnia pamięć zajmowaną przez testy

#endif
