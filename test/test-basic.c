/** This file is in the public domain.
 *
 *
 * @homepage http://github.com/pabigot/psml
 *
 */

#include <embtextf/vuprintf.h>
#include <CUnit/Basic.h>
#include <stdio.h>

int init_suite (void)
{
  return 0;
}
int clean_suite (void)
{
  return 0;
}

char buffer[128];
const char * const bufend = buffer + sizeof(buffer);
const char * errp;
char * bufp;
const char * matchp;

void
resetBuffer (const char * match_str)
{
  errp = NULL;
  bufp = buffer;
  *bufp = 0;
  if (match_str) {
    matchp = match_str;
  }
}

int
storeBuffer (int c)
{
  if (matchp && ! errp) {
    if (*matchp != c) {
      errp = matchp;
    } else {
      ++matchp;
    }
  }
  if ((bufp+1) < bufend) {
    *bufp++ = c;
  }
  *bufp = 0;
  return c;
}

void
test_char (void)
{
  int rc;
  const char * const expected = "'a' '3'";

  resetBuffer(expected);
  rc = uprintf(storeBuffer, "'%c' '%c'", 'a', '3');
  CU_ASSERT_EQUAL(rc, strlen(expected));
  CU_ASSERT_STRING_EQUAL(expected, buffer);
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
    { "char", test_char },
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
    const test_def * td = tests + i;
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
