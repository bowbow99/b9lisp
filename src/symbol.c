/// -*- Mode: C -*-
///
/// symbol.c

//// Code:
#include <string.h>

#include "lisp.h"

typedef struct Lsymbol Lsymbol;
struct Lsymbol {
  Lobject_headers;
  char *name;
};

#define LSYM(X)             ( (Lsymbol *)ptr(X) )
#define symbol_name(X)      ( LSYM(X)->name )

Lobject *make_symbol(char name[])
{
  Lsymbol *sym = Lalloc( sizeof(Lsymbol) / sizeof(void *) );
  check_alloc(sym);

  sym->type = Tsymbol;
  sym->name = strdup(name);

  return (Lobject *)sym;
}

void init_symtab(void)
{
  symtab = Qnil;
}

Lobject *find_symbol(char name[])
{
  for ( Lobject *rest = symtab; rest != Qnil; rest = cdr(rest) ) {
    if ( strcmp(symbol_name(car(rest)), name ) == 0 )
      return car(rest);
  }
  return NULL;
}

Lobject *intern(char name[])
{
  Lobject *sym = find_symbol(name);

  if ( sym == NULL ) {
    sym = make_symbol(name);
    symtab = cons(sym, symtab);
  }
  return sym;
}

void print_symbol(Lobject *sym, FILE *out)
{
  fprintf(out, "%s", symbol_name(sym));
}








/// symbol.c ends here.
