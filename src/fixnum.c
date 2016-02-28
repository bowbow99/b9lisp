/// -*- Mode: C -*-
///
/// fixnum.c

//// Code:
#include "lisp.h"
#include "util.h"

#include <stdbool.h>
#include <inttypes.h>

#define TAG_FIXNUM    0x01

Lobject *make_fixnum(int64_t n)
{
  return (Lobject *)( (n << 2) | TAG_FIXNUM );
}

bool fixnump(Lobject *n)
{
  return ( Ltag_of(n) == TAG_FIXNUM );
}

#define fixnum_value(X)    ( ((int64_t)(X)) >> 2 )

void print_fixnum(Lobject *n, FILE *out)
{
  fprintf(out, "%" PRId64 "", fixnum_value(n));
}

/// fixnum.c ends here.
