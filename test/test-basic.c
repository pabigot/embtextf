/** This file is in the public domain.
 *
 * Note: Expected results are for a 64-bit host where sizeof(int)=4
 * and sizeof(long int)=8.
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

void
test_int_127 (void)
{
  int rc;
  const char * const expected = "127 7f 127 127";

  resetBuffer(expected);
  rc = uprintf(storeBuffer, "%d %x %u %i", 127, 127, 127, 127);
  CU_ASSERT_EQUAL(rc, strlen(expected));
  CU_ASSERT_STRING_EQUAL(expected, buffer);
}

void
test_int_m127 (void)
{
  int rc;
  const char * const expected = "-127 ffffff81 4294967169 -127";

  resetBuffer(expected);
  rc = uprintf(storeBuffer, "%d %x %u %i", -127, -127, -127, -127);
  CU_ASSERT_EQUAL(rc, strlen(expected));
  CU_ASSERT_STRING_EQUAL(expected, buffer);
}

void
test_long (void)
{
#if EMBTEXTF_VUPRINTF_ENABLE_LONG - 0
  long int v = 0;
  int rc;
  const char * const expected = "1 2 3 4";

  resetBuffer(expected);
  rc = uprintf(storeBuffer, "%ld %lx %lu %li", v+1,v+2,v+3,v+4);
  CU_ASSERT_EQUAL(rc, strlen(expected));
  CU_ASSERT_STRING_EQUAL(expected, buffer);
#else /* EMBTEXTF_VUPRINTF_ENABLE_LONG */
  CU_FAIL("LONG not supported");
#endif /* EMBTEXTF_VUPRINTF_ENABLE_LONG */
}

void
test_longlong (void)
{
#if EMBTEXTF_VUPRINTF_ENABLE_LONGLONG - 0
  long long int v = 0;
  int rc;
  const char * const expected = "1 2 3 4";

  resetBuffer(expected);
  rc = uprintf(storeBuffer, "%lld %llx %llu %lli", v+1, v+2, v+3, v+4);
  CU_ASSERT_EQUAL(rc, strlen(expected));
  CU_ASSERT_STRING_EQUAL(expected, buffer);
#else /* EMBTEXTF_VUPRINTF_ENABLE_LONGLONG */
  CU_FAIL("LONG_LONG not supported");
#endif /* EMBTEXTF_VUPRINTF_ENABLE_LONGLONG */
}

#define TEST0(EXPECTED,FMT)                     \
  do {                                          \
    int rc;                                     \
    const char * const expected = EXPECTED;     \
    resetBuffer(expected);                      \
    rc = uprintf(storeBuffer, FMT);             \
    CU_ASSERT_EQUAL(rc, strlen(expected));      \
    CU_ASSERT_STRING_EQUAL(buffer, EXPECTED);   \
  } while(0)

#define TEST(EXPECTED,FMT,...)                                  \
  do {                                                          \
    int rc;                                                     \
    const char * const expected = EXPECTED;                     \
    resetBuffer(expected);                                      \
    rc = uprintf(storeBuffer, FMT, ## __VA_ARGS__);             \
    CU_ASSERT_EQUAL(rc, strlen(expected));                      \
    if (strcmp(buffer, expected)) {                             \
      printf("\nGot '%s'\nExp '%s'\n", buffer, expected);       \
    }                                                           \
    CU_ASSERT_STRING_EQUAL(buffer, expected);                   \
  } while(0)

void
test_basic (void)
{
  /* Basics */
  TEST0("Hello World", "Hello World");
  TEST("1 and 2 and 3", "%d and %d and %d", 1, 2, 3);
  TEST("-123", "%d", -123);
  TEST("4294967173", "%u", -123);
  TEST("ffffff85", "%x", -123);
  TEST("FFFFFF85", "%X", -123);
  TEST("173", "%o", 123);
  TEST("a string", "%s", "a string");
  TEST("(null)", "%s", NULL);
  TEST("mno", "%c%c%c", 'm', 'n', 'o');
  /* Alternative representation */
  TEST("0173", "%#o", 123);
  TEST("0", "%#o", 0);
  TEST("0xffffff85", "%#x", -123);
  /* Sign modifiers */
  TEST(" 12", "% d", 12);
  TEST("-12", "% d", -12);
  TEST("+12", "%+d", 12);
  TEST("-12", "%+d", -12);
  /* Width */
  TEST("-000000123", "%010d",-123);
  TEST("-000000123", "%0*d", 10, -123);
  TEST("      -123", "%10d", -123);
  TEST("      -123", "%*d", 10, -123);
  TEST("-123      ", "%-10d", -123);
  TEST("ab    ", "%-6x", 0xab);
  TEST("    ab", "%6x", 0xab);
  TEST("    ab", "%*x", 6, 0xab);
  TEST("ab    ", "%*x", -6, 0xab);
  TEST("  a string", "%10s", "a string");
  TEST("0", "%p", NULL);
  TEST("   r", "%4c", 'r');
  TEST("l   ", "%-4c", 'l');
  /* Precision */
  TEST("0012", "%.4d", 12);
  TEST("  0012", "%6.4d", 12);
  TEST("12345", "%4.2d", 12345);
  TEST("12345", "%3.4d", 12345);
  TEST("0ab   ", "%-6.3x", 0xab);
  TEST("   0ab", "%6.3x", 0xab);
  TEST("   0ab", "%*.3x", 6, 0xab);
  TEST("0ab   ", "%*.3x", -6, 0xab);
  TEST("0ab   ", "%0*.3x", -6, 0xab);
  TEST("   0ab", "%6.*x", 3, 0xab);
  TEST("   0ab", "%*.*x", 6, 3, 0xab);
  TEST(" 0x0ab", "%#6.3x", 0xab);
  TEST(" 0x0ab", "%#*.3x", 6, 0xab);
  TEST(" 0x0ab", "%#6.*x", 3, 0xab);
  TEST(" 0x0ab", "%#*.*x", 6, 3, 0xab);
  TEST("mno", "%.3s", "mnopq");
  //TEST("%.0-3s", "%.-3s", "mnopq");
  TEST("mno", "%.*s", 3, "mnopq");
  TEST0("%?", "%?");
  TEST("%*.4? 2", "%*.4? %d", 1, 2);
  TEST0("%", "%%");
  TEST0("", "%");
  TEST("    mno", "%7.3s", "mnopq");
  TEST("    mno", "%*.3s", 7, "mnopq");
  TEST("    mno", "%7.*s", 3, "mnopq");
  TEST("    mno", "%*.*s", 7, 3, "mnopq");
  TEST("(nu", "%.3s", NULL);
  TEST("", "%.s", "mno");
  TEST("123", "%.d", 123);
  TEST("1", "%.d", 1);
  TEST("0", "%.d", 0);

  TEST("'    mno' 'mnopq'", "'%7.3s' '%s'", "mnopq", "mnopq");
}

void
test_strprec (void)
{
  /* Basics */
  TEST("    a", "%5.3s", "a");
  TEST("   ab", "%5.3s", "ab");
  TEST("  abc", "%5.3s", "abc");
  TEST("  abc", "%5.3s", "abcd");
  TEST("  abc", "%5.3s", "abcde");
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
    { "int 127", test_int_127 },
    { "int -127", test_int_m127 },
    { "long", test_long },
    { "long long", test_longlong },
    { "basic", test_basic },
    { "strprec", test_strprec },
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
