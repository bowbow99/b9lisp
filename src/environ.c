/// -*- Mode: C -*-
///
/// environ.c

//// Code:
#include "lisp.h"

typedef struct binding binding;
struct binding {
  Lobject *sym;
  Lobject *value;
  binding *next;
};

typedef struct Lenviron Lenviron;
struct Lenviron {
  Lobject_headers;
  binding *bindings;
  Lobject *next;
};

#define LENV(X)    ( (Lenviron *)ptr(X) )

Lobject *make_environment(Lobject *next)
{
  Lenviron *env = Lalloc(3);
  check_alloc(env);

  env->type = Tenvironment;
  env->bindings = NULL;
  env->next = next;

  return (Lobject *)( iPTR(env) | TAG_OBJECT );
}

binding *find_binding(Lobject *env, Lobject *sym)
{
  check_type(env, Tenvironment);

  for ( binding *bin = LENV(env)->bindings; bin != NULL; bin = bin->next ) {
    if ( bin->sym == sym )
      return bin;
  }

  if ( LENV(env)->next )
    return find_binding(LENV(env)->next, sym);
  else
    return NULL;
}

Lobject *lookup(Lobject *env, Lobject *sym)
{
  check_type(env, Tenvironment);
  check_type(sym, Tsymbol);

  binding *bin = find_binding(env, sym);
  if ( bin )
    return bin->value;
  else
    return NULL;
}

Lobject *bind(Lobject *env, Lobject *sym, Lobject *value)
{
  check_type(env, Tenvironment);
  check_type(sym, Tsymbol);

  binding *bin = find_binding(env, sym);
  if ( bin ) {
    bin->value = value;
  }
  else {
    bin = Lalloc( sizeof(binding) / sizeof(void *) );
    check_alloc(bin);
    bin->sym = sym;
    bin->value = value;
    bin->next = LENV(env)->bindings;
    LENV(env)->bindings = bin;
  }
  return bin->value;
}

void init_global_env(void)
{
  global_env = make_environment(NULL);
}

void print_environment(Lobject *env, FILE *out)
{
  fprintf(out, "#<environment: @0x%" PRIu64 ">", iPTR(env));
}

/// environ.c
