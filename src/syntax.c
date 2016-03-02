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
  case Squote:
    return car(args);
  case Slambda:
  case Sif:
  case Sbegin: {
    Lobject *value = Qnil;
    for ( ; args != Qnil; args = cdr(args) ) {
      value = evaluate(car(args), env);
    }
    return value;
  }
  case Sdefine: {
    Lobject *sym = car(args);
    Lobject *value = evaluate(car(cdr(args)), env);
    bind(global_env, sym, value);
    return value;
  }
  case Slet:
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