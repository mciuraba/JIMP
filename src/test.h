#ifndef _TEST_H_
#define _TEST_H_

#include "mat_io.h"

#define BUFSIZE 256
#define TESTS_COUNT 5

typedef struct {
    Matrix* A;
    Matrix* b;
    Matrix* x;
    
    Matrix* expected_x;
    
} test_t ;

void start_tests( char* );
test_t init_test( Matrix*, Matrix*, Matrix* );
int do_test( test_t* );
void free_test( test_t );

#endif
