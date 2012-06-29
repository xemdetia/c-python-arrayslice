
#ifndef __ARRAYSLICE_H__
#define __ARRAYSLICE_H__

#include <string.h>
#include <stdio.h>
#include <malloc.h>

struct arr_slice
{
  int num;
  size_t size;
  void *data;
};

/*
 * num - number of elements
 * size - sizeof() each element
 * data - pointer that says where the data is
 *
 * returns NULL on failure.
 */
struct arr_slice* arrslice_wrap_array( int num,
				       size_t size,
				       void *data );
/* Frees an allocated array slice */
void arrslice_clean_array_slice( struct arr_slice *slice );
/* slice an array using Pythonic notation. Returns NULL on
   failure. Allocates a new arr_slice based on the existing
   data. Caller is responsible for freeing. Use brackets to
   surround the value.*/
struct arr_slice* arrslice_slice( struct arr_slice *orig, char *slice );
struct arr_slice* arrslice_get_array_subset( struct arr_slice* orig, int start, int end );
struct ArrSlice_namespace
{
  struct arr_slice* (*wrap_array) ( int, size_t, void* );
  void (*clean) ( struct arr_slice* );
  struct arr_slice* (*go) ( struct arr_slice*, char* );
  struct arr_slice* (*subset) (struct arr_slice*, int start, int end );
};

static const struct ArrSlice_namespace 
Slice = { &arrslice_wrap_array,
	  &arrslice_clean_array_slice,
	  &arrslice_slice,
	  &arrslice_get_array_subset };

#endif /* __ARRAYSLICE_H__ */
