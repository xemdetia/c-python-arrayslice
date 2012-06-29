
#include "arrayslice.h"

struct start_end {
  int start;
  int end;
};

struct arr_slice* arrslice_wrap_array( int num,
				       size_t size,
				       void *data )
{
  struct arr_slice *result = NULL;
  
  if ( num < 0 || size < 1  || data == NULL ) {

    /* Have to have at least 0 elements, and data must exist and what
       data points to must not be NULL. */
    return NULL;
  }

  result = (struct arr_slice*) malloc( sizeof( struct arr_slice));
  if ( result == NULL ) {
    
    return NULL; /* OOM */
  }

  result->num = num;
  result->size = size;
  result->data = data;
  
  return result;
}

void arrslice_clean_array_slice( struct arr_slice *slice )
{
  if ( slice != NULL ) {

    free( slice );
  }

}

struct arr_slice* get_single_value( struct arr_slice *orig, int targ )
{
  struct arr_slice *result = NULL;

  /* Bad results fall through with result staying NULL */
  if ( targ > 0 ) {
      
    /* Count from end */
    if ( targ - orig->num >= 0 ) {

      result = arrslice_wrap_array( 1, orig->size, orig->data + ( targ - orig->num ));
				    
    } else {

      /* Count from beginning */
      if ( targ < orig->num ) {

	result = arrslice_wrap_array( 1, orig->size, orig->data + targ );
      }
    }
  }

  return result;
}

struct arr_slice* arrslice_get_array_subset( struct arr_slice* orig, int start, int end )
{
  struct arr_slice *result = NULL;

  /* Fail gracefully */
  if ( start < 0 ) {
    start = 0;
  }

  if ( end > orig->num ) {
    end = orig->num;
  }

  if ( start != end ) {
    
    arrslice_wrap_array( end - start, orig->size, orig->data + start );
  }
  return result;
}

/* slice an array using Pythonic notation. Returns NULL on
   failure. Allocates a new arr_slice based on the existing
   data. Caller is responsible for freeing. */
struct arr_slice* arrslice_slice( struct arr_slice *orig, char *slice )
{

  struct arr_slice *result = NULL;
  struct start_end se = { -1, -1 };
  char *p = NULL;
  
  /* Check Parameters */
  if ( orig == NULL || slice == NULL ) {
    
    return NULL;
  }

  p = strstr( slice, ":" );
  if ( p == NULL ) {
    
    /* No ':' in the slice, return one value. */
    if ( sscanf( slice, "[%d]", &se.start ) != 1 ) {

      return NULL; /* Bad Input: String didn't form [333]  */
    }
    
    result = get_single_value( orig, se.start );
  } 

  return result;
}
