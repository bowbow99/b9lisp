/// -*- Mode: C -*-
///
/// syntax.c

//// Code:
#include "inttypes.h"

#include "lisp.h"

Lobject *make_syntax(int32_t id)
{
  return (Lobject *)( (id << 8) | TAG_SYNTAX );
  
}

int32_t syntax_id(Lobject *syn)
{
  return (int32_t)( iPTR(syn) >> 8 );
}


static char *syntax_name_list[] = {
#define DEFSYNTAX(NAME)   #NAME,
#  include "syntax.def"
#undef DEFSYNTAX
};

void define_syntax(int32_t id, char *name)
{
  Lobject *s = make_syntax(id);
  bind(global_env, intern(name), s);
}


Lobject *apply_syntax(Lobject *op, Lobject *args, Lobject *env)
{
  check_type(op, Tsyntax);
  check_type(args, Tcons);
  check_type(env, Tenvironment);

  switch ( syntax_id(op) ) {
  case Squote: {
    return xfirst(args);
  }
  case Slambda: {
    check_type(car(args), Tcons);
    check_type(cdr(args), Tcons);
    return make_closure(car(args), cdr(args), env);
  }
  case Sif: {
    Lobject *cond = evaluate(xfirst(args), env);
    if ( cond == Qnil )
      return evaluate(xthird(args), env);
    else
      return evaluate(xsecond(args), env);
  }
  case Sbegin: {
    Lobject *value = Qnil;
    for ( ; args != Qnil; args = cdr(args) ) {
      value = evaluate(car(args), env);
    }
    return value;
  }
  case Sdefine: {
    Lobject *sym = xfirst(args);
    Lobject *value = evaluate(xsecond(args), env);
    bind(global_env, sym, value);
    return value;
  }
  case Slet: {
    Lobject *nenv = make_environment(env);
    check_type(car(args), Tcons);
    dolist(bin, car(args)) {
      check_type(bin, Tcons);
      check_type(xfirst(bin), Tsymbol);
      bind(nenv, xfirst(bin), evaluate(xsecond(bin), env));
    }
    Lobject *ret = Qnil;
    dolist(expr, cdr(args)) {
      ret = evaluate(expr, nenv);
    }
    return ret;
  }
  default:
    die("Unknown syntax: %p\n", op);
  }
}

void print_syntax(Lobject *syn, FILE *out)
{
  fprintf(out, "#<syntax: %s>", syntax_name_list[syntax_id(syn)]);
}


void init_syntax(void)
{
#define DEFSYNTAX(NAME)   define_syntax(S##NAME, #NAME);
#  include "syntax.def"
#undef DEFSYNTAX  
}

/// syntax.c ends here.
