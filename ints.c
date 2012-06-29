#include <stdio.h>
#include <string.h>
#include "arrayslice.h"

void print_slice( struct arr_slice *s )
{
  int i = 0;
  double *p = s->data;
  printf("[ ");
  for ( i = 0; i < s->num; i++ ) {

    printf( "%.1f", p[i] );
    if ( i == s->num - 1) {
      break;
    }
    printf(", ");
  }
  printf(" ]\n");
}

int main( int argc, char **argv )
{

  double arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  struct arr_slice *s = NULL;
  struct arr_slice *a = NULL;
  
  s = Slice.wrap_array( 10, sizeof(double), arr );
  
  /* Prints '5' */
  a = Slice.go( s, "[4]" );
  print_slice( a );
  Slice.clean( a );
  
  /* Prints '1.0, 2.0' */
  a = Slice.go( s, "[0:2]" );
  print_slice( a );
  Slice.clean( a );

  /* Prints '3.0, 4.0' */
  a = Slice.go( s, "[2:4]" );
  print_slice( a );
  Slice.clean( a );

  /* Prints '1.0, 2.0' */
  a = Slice.go( s, "[:2]" );
  print_slice( a );
  Slice.clean( a );

  /* Prints '3.0-10.0' */
  a = Slice.go( s, "[2:]" );
  print_slice( a );
  Slice.clean( a );

  /* Prints '10.0' */
  a = Slice.go( s, "[-1]" );
  print_slice( a );
  Slice.clean( a );

  /* Prints '' */
  a = Slice.go( s, "[1:100]" );
  print_slice( a );
  Slice.clean( a );

  /* Prints '' */
  a = Slice.go( s, "[10:]" );
  print_slice( a );
  Slice.clean( a );

  /* Prints '' */
  a = Slice.go( s, "[2:1]" );
  print_slice( a );
  Slice.clean( a );


  /* Prints 'p' */
  a = Slice.go( s, "[-2]" );
  print_slice( a );
  Slice.clean( a );

  /* Prints 'pA' */
  a = Slice.go( s, "[-2:]" );
  print_slice( a );
  Slice.clean( a );

  /* Prints 'Hel' */
  a = Slice.go( s, "[:-2]" );
  print_slice( a );
  Slice.clean( a );

  /* Prints 'H' */
  a = Slice.go( s, "[-0]" );
  print_slice( a );
  Slice.clean( a );

  return 0;
}
