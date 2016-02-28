/// -*- Mode: C -*-
///
/// read.c
#include "lisp.h"

#include "util.h"
#include <ctype.h>
#include <stdbool.h>
#include <string.h>


void skip_whitespaces(FILE *in)
{
  int32_t c = fgetc(in);
  while ( isspace(c) ) {
    c = fgetc(in);
  }
  ungetc(c, in);
}



static const char extra_symbol_chars[] = "!@$%^&*/?-_=+~<>";

bool is_symbol_char(int32_t c)
{
  return ( isalnum(c) || strchr(extra_symbol_chars, c) );
}

#define READ_BUF_SIZE  1024

Lobject *read_atom(FILE *in, int32_t c)
{
# define push(C)    buf[i++] = (char)(C);

  char buf[READ_BUF_SIZE];
  size_t i = 0;
  bool is_number = isdigit(c) || strchr("+-", c);

  push(c);

  while ( c = fgetc(in), is_symbol_char(c) ) {
    push(c);
    if ( is_number && !isdigit(c) ) {
      is_number = false;
    }
  }
  buf[i] = '\0';
  ungetc(c, in);

  if ( is_number ) {
    return make_fixnum(atol(buf));
  }
  else {
    die("Symbol not implemented.\n;; buf = \"%s\"\n", buf);
  }
}





Lobject *read_object(FILE *in)
{
  skip_whitespaces(in);

  int32_t c = fgetc(in);

  switch ( c ) {
  case EOF:
    return NULL;
  default:
    return read_atom(in, c);
  }
}



/// read.c ends here.
