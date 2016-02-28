/// -*- Mode: C -*-
///
/// cons.c

//// Code:
#include "lisp.h"

typedef struct Lcons Lcons;
struct Lcons {
  Lobject *car;
  Lobject *cdr;
};

#define LCONS(X)    ( (Lcons *)ptr(X) )

Lobject *cons(Lobject *car, Lobject *cdr)
{
  Lcons *cons = Lalloc(2);
  check_alloc(cons);

  cons->car = car;
  cons->cdr = cdr;

  return (Lobject *)( (uintptr_t)cons | TAG_CONS );
}

Lobject *car(Lobject *cons)
{
  return LCONS(cons)->car;
}

Lobject *cdr(Lobject *cons)
{
  return LCONS(cons)->cdr;
}

Lobject *set_car(Lobject *cons, Lobject *value)
{
  check_type(cons, Tcons);
  LCONS(cons)->car = value;
  return value;
}

Lobject *set_cdr(Lobject *cons, Lobject *value)
{
  check_type(cons, Tcons);
  LCONS(cons)->cdr = value;
  return value;
}

void print_list(Lobject *list, FILE *out)
{
  fprintf(out, "(");

  if ( list == Qnil )
    goto CLOSE;

  print_object(car(list), out);

  for ( list = cdr(list);
        list != Qnil && Ltype_of(list) == Tcons;
        list = cdr(list) ) {
    fprintf(out, " ");
    print_object(car(list), out);
  }

  if ( Ltype_of(list) != Tcons ) {
    fprintf(out, " . ");
    print_object(list, out);
  }

CLOSE:
  fprintf(out, ")");
}

/// cons.c ends here.
