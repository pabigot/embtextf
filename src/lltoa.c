#include <embtextf/xtoa.h>
#include <embtextf/buildconf.h>
#if (ENABLE_XTOA_LONGLONG - 0)
#define INT_T long long
#define STOA embtextf_lltoa
#define UTOA embtextf_ulltoa
#include "embtextf/xtoa.inc"
#endif /* ENABLE_XTOA_LONGLONG */
