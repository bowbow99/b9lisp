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
  default:
    return LOBJ(obj)->type;
  }
}

void print_object(Lobject *obj, FILE *out)
{
  switch ( Ltype_of(obj) ) {
  case Tfixnum:    print_fixnum(obj, out); break;
  case Tcons:      print_list(obj, out); break;
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
}

/// object.c ends here.
