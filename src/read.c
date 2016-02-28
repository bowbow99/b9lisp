/// -*- Mode: C -*-
///
/// read.c

//// Code
#include "lisp.h"

#include <ctype.h>
#include <stdbool.h>
#include <string.h>

int32_t next_char(FILE *in)
{
  int32_t c = fgetc(in);
  while ( isspace(c) ) {
    c = fgetc(in);
  }
  return c;
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

Lobject *read_list(FILE *in)
{
  Lobject *head, *tail, *tmp;
  int32_t c;

  c = next_char(in);
  if ( c == ')' )
    return Qnil;

  ungetc(c, in);
  tmp = read_object(in);
  head = cons(tmp, Qnil);
  tail = head;

  while ( (c = next_char(in)) != EOF ) {
    switch ( c ) {
    case ')':
      return head;
    case '.':
      tmp = read_object(in);
      if ( tmp == NULL )
        die("list terminated unexpectedly.\n");
      set_cdr(tail, tmp);
      next_char(in);  // get rid of closing paren.
      return head;
    default:
      ungetc(c, in);
      tmp = read_object(in);
      if ( tmp == NULL )
        die("list terminated unexpectedly.\n");
      set_cdr(tail, cons(tmp, Qnil));
      tail = cdr(tail);
    }
  }
  die("list terminated unexpectedly.\n");
}

Lobject *read_object(FILE *in)
{
  int32_t c = next_char(in);

  switch ( c ) {
  case EOF:
    return NULL;
  case '(':
    return read_list(in);
  default:
    return read_atom(in, c);
  }
}

/// read.c ends here.
