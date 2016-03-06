
// MT, 2016feb26

// MT_TODO: TEST: Not 100% like JSON standard:
//
// - No UTF-8 / Unicode support.
// - JSON number format might not be "perfect" (formatting of floating-point numbers, no integer support).

#ifndef MT_JSON
#define MT_JSON

#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif //__cplusplus

bool json_parse(char * const inStr, bool const inTakeOwnership);

#ifdef	__cplusplus
}
#endif //__cplusplus

#endif //MT_JSON
