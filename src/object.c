/// -*- Mode: C -*-
///
/// object.c

#include "lisp.h"
#include "util.h"

Ltype Ltype_of(Lobject *obj)
{
  switch ( Ltag_of(obj) ) {
  case TAG_EVEN_FIXNUM:
  case TAG_ODD_FIXNUM:
    return Tfixnum;
  default:
    return Lobj(obj)->type;
  }
}


void print_object(Lobject *obj, FILE *out)
{
  switch ( Ltype_of(obj) ) {
  case Tfixnum:    print_fixnum(obj, out); break;
  default:
    die("Printer not implemented: type = %d",
        Ltype_of(obj));
  }
}







/// object.c ends here.
