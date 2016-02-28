/// -*- Mode: C -*-
///
/// lisp.h
#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>


//// Memory stuff

#define Lalloc(SIZE)                    \
  malloc( sizeof(void *) * (SIZE) )


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
  TAG_000,  // 000:
  TAG_EVEN_FIXNUM,  // 001: Fixnum (even)
  TAG_010,  // 010:
  TAG_011,  // 011:
  TAG_100,  // 100:
  TAG_ODD_FIXNUM,  // 101: Fixnum (odd)
  TAG_110,  // 110:
  TAG_111,  // 111:
} Ltag;

#define TAG_BITS    0x07  // ...111
#define iPTR(X)     ((uintptr_t)(X))
#define Lobj(X)     ( (Lobject *)(iPTR(X) & ~TAG_BITS) )
#define Ltag_of(X)  ( (Ltag)(iPTR(X) & TAG_BITS) )



//// Lobject C APIs

Ltype Ltype_of(Lobject *obj);
void print_object(Lobject *obj, FILE *out);

Lobject *read_object(FILE *in);
void init_b9lisp(void);


//// Fixnum

Lobject *make_fixnum(int64_t n);
void print_fixnum(Lobject *n, FILE *out);


//// Character
Lobject *make_character(char c);
void print_Tcharacter(Lobject *c, FILE *out);


//// Cons/List








/// lisp.h ends here.
