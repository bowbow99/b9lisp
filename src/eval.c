/// -*- Mode: C -*-
///
/// eval.c

//// Code:
#include "lisp.h"

Lobject *evaluate(Lobject *expr, Lobject *env)
{
  Lobject *ret;

  switch ( Ltype_of(expr) ) {
  case Tsymbol:
    ret = lookup(env, expr);
    if ( ret == NULL )
      die("Undefined variable: %s", symbol_name(expr));
    return ret;
  default:
    return expr;
  }
}



/// eval.c ends here.
