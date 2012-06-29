
#include <stdio.h>
#include <string.h>
#include "arrayslice.h"

void print_slice( struct arr_slice *s )
{
  char buff[256] = "";
  
  strncat( buff, s->data, s->num );
  printf( "'%s'\n", &buff );
}

int main( int argc, char **argv )
{
  /* From http://docs.python.org/tutorial/introduction.html */
  char *word = "HelpA";
  struct arr_slice *s = NULL;
  struct arr_slice *a = NULL;
  
  s = Slice.wrap_array( strlen( word ), sizeof(char), word );
  
  /* Prints 'A' */
  a = Slice.go( s, "[4]" );
  print_slice( a );
  Slice.clean( a );
  
  /* Prints 'He' */
  a = Slice.go( s, "[0:2]" );
  print_slice( a );
  Slice.clean( a );

  /* Prints 'lp' */
  a = Slice.go( s, "[2:4]" );
  print_slice( a );
  Slice.clean( a );

  /* Prints 'He' */
  a = Slice.go( s, "[:2]" );
  print_slice( a );
  Slice.clean( a );

  /* Prints 'lpA' */
  a = Slice.go( s, "[2:]" );
  print_slice( a );
  Slice.clean( a );

  /* Prints 'A' */
  a = Slice.go( s, "[-1]" );
  print_slice( a );
  Slice.clean( a );

  /* Prints 'elpA' */
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
