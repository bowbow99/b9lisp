/// -*- Mode: C -*-
///
/// character.c

//// Code:
#include "lisp.h"

Lobject *make_character(char c)
{
  return (Lobject *)( (iPTR(c) << 8) | TAG_CHARACTER );
}

void print_character(Lobject *c, FILE *out)
{
  fprintf(out, "#\\%c", iPTR(c) >> 8);
}

/// character.c ends here.
