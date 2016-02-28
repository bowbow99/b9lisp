/// -*- Mode: C -*-
///
/// lisp.h

//// Code
#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "util.h"


//// Memory stuff

#define Lalloc(SIZE)                    \
  malloc( sizeof(void *) * (SIZE) )

#define check_alloc(X)                  \
  if ( (X) == NULL )                    \
    die("Could not allocate memory for %s", #X)


//// Lobject

enum Ltype {
  Tinvalid,
  // simple values
  Tfixnum,
  Tsymbol,
  Tcharacter,
  // complicated objects
  Tenvironment,
  Tstream,
  // containers
  Tcons,
  Tvector,
  Ttable,
  // callables
  Tfunction,
  Tclosure,
  Tsyntax,
};
typedef int Ltype;

#define Lobject_headers                 \
  Ltype type : 4

typedef struct Lobject Lobject;
struct Lobject {
  Lobject_headers;
  Lobject *datum[1];
};


//// Pointer Tagging

typedef enum Ltag {
  TAG_OBJECT,       // 000: Object
  TAG_EVEN_FIXNUM,  // 001: Fixnum (even)
  TAG_CONS,         // 010: Cons cell
  TAG_CHARACTER,    // 011: Character
  TAG_100,  // 100:
  TAG_ODD_FIXNUM,   // 101: Fixnum (odd)
  TAG_110,  // 110:
  TAG_111,  // 111:
} Ltag;

#define TAG_BITS    0x07  // ...111
#define iPTR(X)     ((uintptr_t)(X))
#define ptr(X)      ( iPTR(X) & ~TAG_BITS )
#define Ltag_of(X)  ( (Ltag)(iPTR(X) & TAG_BITS) )

#define LOBJ(X)     ( (Lobject *)(ptr(X)) )

#define check_type(OBJ, TYPE)           \
  if ( Ltype_of(OBJ) != (TYPE) )        \
    die("Object %s is not of type %s.\n", #OBJ, #TYPE)


//// Lobject C APIs

Ltype Ltype_of(Lobject *obj);
void print_object(Lobject *obj, FILE *out);

Lobject *read_object(FILE *in);
void init_b9lisp(void);

Lobject *Qnil;
Lobject *symtab;


//// Fixnum
Lobject *make_fixnum(int64_t n);
void print_fixnum(Lobject *n, FILE *out);


//// Character
Lobject *make_character(char c);
void print_character(Lobject *c, FILE *out);


//// Cons/List
Lobject *cons(Lobject *car, Lobject *cdr);

Lobject *car(Lobject *cons);
Lobject *cdr(Lobject *cons);
Lobject *set_car(Lobject *cons, Lobject *value);
Lobject *set_cdr(Lobject *cons, Lobject *value);

void print_list(Lobject *list, FILE *out);


//// Symbol
Lobject *intern(char name[]);

void init_symtab(void);
void print_symbol(Lobject *sym, FILE *out);


//// Character
Lobject *make_character(char c);
void print_character(Lobject *c, FILE *out);

/// lisp.h ends here.
