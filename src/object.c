/// -*- Mode: C -*-
///
/// object.c

//// Code
#include "lisp.h"

Ltype Ltype_of(Lobject *obj)
{
  switch ( Ltag_of(obj) ) {
  case TAG_EVEN_FIXNUM:
  case TAG_ODD_FIXNUM:
    return Tfixnum;
  case TAG_CONS:
    return Tcons;
  case TAG_VALUE:
    switch ( iPTR(obj) & 0x0f ) {
    case TAG_CHARACTER: return Tcharacter;
    case TAG_SYNTAX:    return Tsyntax;
    }
  default:
    return LOBJ(obj)->type;
  }
}

void print_object(Lobject *obj, FILE *out)
{
  switch ( Ltype_of(obj) ) {
#define type(NAME,PRINTER)   \
  case NAME: PRINTER(obj, out); break
    type(Tfixnum, print_fixnum);
    type(Tcons, print_list);
    type(Tcharacter, print_character);
    type(Tsymbol, print_symbol);
    type(Tenvironment, print_environment);
    type(Tsyntax, print_syntax);
#undef type
  default:
    die("Printer not implemented: type = %d",
        Ltype_of(obj));
  }
}

void init_b9lisp(void)
{
  Qnil = cons(NULL, NULL);
  set_car(Qnil, Qnil);
  set_cdr(Qnil, Qnil);

  init_symtab();
  init_global_env();
  init_syntax();
}

/// object.c ends here.
