
// MT, 2016feb26

#ifndef MT_JSONSTATEINPUT
#define MT_JSONSTATEINPUT

#include <stddef.h>
#include "Stack.h"

#ifdef	__cplusplus
extern "C" {
#endif //__cplusplus

struct JsonStateInput
{
    char * const str;
    size_t const len;
    bool const takesOwnership;

    size_t i;
    struct Stack * const stack;
};

struct JsonStateInput * JsonStateInput_create(char * const inStr, bool const inTakesOwnership);
void JsonStateInput_delete(struct JsonStateInput * const inJsonStateInput);

#ifdef	__cplusplus
}
#endif //__cplusplus

#endif //MT_JSONSTATEINPUT
