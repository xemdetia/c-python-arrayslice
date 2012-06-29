
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
  if ( targ < 0 ) {
      
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
  int read = 0;
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
  } else {

    /* There is probably a better way to do this but this is the easiest way */
    if ( sscanf( slice, "[:%d]", &se.end ) == 1 ) {
      se.start = 0;
      
      if ( se.end > orig->num - 1 ) {

	se.end = orig->num - 1; /* Did we go out of bounds? */
	if ( se.end < 0 && (se.end - orig->num > 0 ) ) {
	  se.end = se.end - orig->num; /* Normalize */
	} else {
	  se.end = se.end;
	}
      }

      /* else if( sscanf( slice, "[%d:]", &se.start ) == 1) { */
      /*   se.end = orig->num - 1; */

      /*   if ( se.start < 0 && (se.start - orig->num -1) >) { */
      /* 	se.start =  */
      /*   } else { */
      /* 	se.start = 0; */
      /*   } */
      /* } else if( sscanf( slice, "[%d:%d]", &se.start, &se.end ) == 2) { */
      
      /*   /\* Don't need to touch anything *\/ */
      /* } else { */
      
      /*   return NULL; /\* Didn't match either [:x], [x:], or [x:x] *\/ */
      /* } */
   
      result = arrslice_get_array_subset( orig, se.start, se.end );
    }

    return result;
  }
}
