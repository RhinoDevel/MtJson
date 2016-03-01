
// MT, 2016mar01

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "Deb.h"
#include "Str.h"
#include "Stack.h"
#include "json_state_string.h"

enum JsonState json_state_string(struct JsonStateInput * const inObj)
{
    assert(inObj!=NULL);
    assert(!Stack_isEmpty(inObj->stack));

    enum JsonState retVal = JsonState_err;
    char * const val = Str_string_create(inObj->str, inObj->len, '"', &(inObj->i));

    if(val!=NULL)
    {
        Deb_line("\"%s\"", val);
        free(val);
        retVal = JsonState_val_end;
    }

    return retVal;
}