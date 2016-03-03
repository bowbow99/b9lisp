/// -*- Mode: C -*-
///
/// eval.c

//// Code:
#include "lisp.h"

Lobject *evaluate_list(Lobject *exprs, Lobject *env)
{
  Lobject *head = cons(evaluate(car(exprs), env), Qnil);
  Lobject *tail = head;
  dolist( expr, cdr(exprs) ) {
    Lobject *x = cons(evaluate(expr, env), Qnil);
    set_cdr(tail, x);
    tail = x;
  }
  return head;
}

Lobject *evaluate(Lobject *expr, Lobject *env)
{
  switch ( Ltype_of(expr) ) {

  case Tsymbol: {
    Lobject *ret = lookup(env, expr);
    if ( ret == NULL )
      die("Undefined variable: %s", symbol_name(expr));
    return ret;
  }

  case Tcons: {
    if ( expr == Qnil ) {
      return Qnil;
    }
    Lobject *op = evaluate(car(expr), env);
    switch ( Ltype_of(op) ) {
    case Tsyntax:
      return apply_syntax(op, cdr(expr), env);
    case Tfunction:
      die("Applying function is not implemented yet. Sorry.\n");
    case Tclosure:
      return apply_closure(op, evaluate_list(cdr(expr), env));
    default:
      die("Invalid operator: type = %d\n", Ltype_of(op));
    }
  }

  default:
    return expr;
  }
}

/// eval.c ends here.
