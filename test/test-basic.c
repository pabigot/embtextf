/** This file is in the public domain.
 *
 *
 * @homepage http://github.com/pabigot/psml
 *
 */

#include <embtextf/vuprintf.h>
#include <CUnit/Basic.h>
#include <stdio.h>

void
test_one (void)
{
}

int init_suite (void)
{
  return 0;
}
int clean_suite (void)
{
  return 0;
}

int
main (int argc,
      char* argv[])
{
  CU_ErrorCode rc;
  CU_pSuite suite = NULL;
  typedef struct test_def {
    const char* name;
    void (*fn) (void);
  } test_def;
  const test_def tests[] = {
    { "one", test_one },
  };
  const int ntests = sizeof(tests) / sizeof(*tests);
  int i;

  rc = CU_initialize_registry();
  if (CUE_SUCCESS != rc) {
    fprintf(stderr, "CU_initialize_registry %d: %s\n", rc, CU_get_error_msg());
    return CU_get_error();
  }

  suite = CU_add_suite("basic", init_suite, clean_suite);
  if (! suite) {
    fprintf(stderr, "CU_add_suite: %s\n", CU_get_error_msg());
    goto done_registry;
  }

  for (i = 0; i < ntests; ++i) {
    const test_def* td = tests + i;
    if (! (CU_add_test(suite, td->name, td->fn))) {
      fprintf(stderr, "CU_add_test(%s): %s\n", td->name, CU_get_error_msg());
      goto done_registry;
    }
  }
  printf("Running tests\n");
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();

done_registry:
  CU_cleanup_registry();

  return CU_get_error();
}
