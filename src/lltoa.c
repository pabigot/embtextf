#include <embtextf/xtoa.h>
#if (EMBTEXTF_XTOA_ENABLE_LONGLONG - 0)
#define INT_T long long
#define STOA embtextf_lltoa
#define UTOA embtextf_ulltoa
#include "embtextf/xtoa.inc"
#endif /* EMBTEXTF_XTOA_ENABLE_LONGLONG */
