/// -*- Mode: C -*-
///
/// repl.c

//// Code
#include "lisp.h"

void run_repl(void)
{
  Lobject *x;
  for (;;) {
    // read
    printf("b9lisp> ");
    x = read_object(stdin);
    if ( !x ) break;
    // eval
    x = evaluate(x, global_env);
    // print
    print_object(x, stdout);
    printf("\n");
  }
}

void test_fixnum(void)
{
#define test(EXPR)    \
  if ( !(EXPR) )      \
    die("Test failed: %s", #EXPR)

  Lobject *a = make_fixnum(3);
  Lobject *b = make_fixnum(8);
  Lobject *c = make_fixnum(11);

  test((uint64_t)a == 13);
  test((uint64_t)b == 33);
  test((uint64_t)c == 45);

#define dump(EXPR)                      \
  do {                                  \
    printf("b9lisp> %s\n", #EXPR);      \
    print_object((EXPR), stdout);       \
    printf("\n");                       \
  } ONCE

  dump(a);
  dump(b);
  dump(c);
}

int main(int argc, char *argv[])
{
  UNUSED(argc);
  UNUSED(argv);

  init_b9lisp();

  run_repl();

  return 0;
}

/// repl.c ends here.
