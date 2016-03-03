/// -*- Mode: C -*-
///
/// closure.c

//// Code:
#include <inttypes.h>

#include "lisp.h"

typedef struct Lclosure Lclosure;
struct Lclosure {
  Lobject_headers;
  Lobject *arglist;
  Lobject *body;
  Lobject *env;
};

#define L(X)    ( (Lclosure *)ptr(X) )

Lobject *make_closure(Lobject *arglist, Lobject *body, Lobject *env)
{
  Lclosure *f = Lalloc(4);
  check_alloc(f);

  f->type    = Tclosure;
  f->arglist = arglist;
  f->body    = body;
  f->env     = env;

  return (Lobject *)f;
}

Lobject *apply_closure(Lobject *f, Lobject *args)
{
  Lobject *env = make_environment(L(f)->env);

  for ( Lobject *arglist = L(f)->arglist;
        arglist != Qnil;
        arglist = cdr(arglist), args = cdr(args) ) {
    bind(env, car(arglist), car(args));
  }

  Lobject *value = Qnil;
  dolist( expr, L(f)->body ) {
    value = evaluate(expr, env);
  }

  return value;
}


void print_closure(Lobject *f, FILE *out)
{
  fprintf(out, "#<closure: @{%" PRIu64 "}>", iPTR(f));
}

/// closure.c ends here.
