/// -*- Mode: C -*-
///
/// util.h
#pragma once

#include <stdio.h>
#include <stdlib.h>

#ifdef _MSC_VER
#  define ONCE                           \
  __pragma( warning(push) )              \
  __pragma( warning(disable:4127) )      \
  while ( 0 )                            \
  __pragma( warning(pop) )
#else
#  define ONCE                           \
  while ( 0 )
#endif

#define die(...)                         \
  do {                                   \
    fprintf(stderr, "ERROR: %s:L%d (in function '%s')\n",    \
            __FILE__, __LINE__, __FUNCTION__);               \
    fprintf(stderr, __VA_ARGS__);        \
    abort();                             \
  } ONCE

#define UNUSED(X)                        \
  (void)(X)



/// util.h ends here.
