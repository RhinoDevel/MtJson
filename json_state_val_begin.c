
// MT, 2016feb29

#include <assert.h>
#include "json_state_val_begin.h"

enum JsonState json_state_val_begin(struct JsonStateInput * const inObj)
{
    enum JsonState retVal = JsonState_err;

    assert(inObj!=NULL);
    assert(inObj->i<inObj->len);
    assert(!Stack_isEmpty(inObj->stack));

    switch(inObj->str[inObj->i])
    {
        case '[':
            retVal = JsonState_arr_begin;
            break;
        case '{':
            retVal = JsonState_obj_begin;
            break;
        case 't':
        case 'f':
            retVal = JsonState_boolean;
            break;
        case '-':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            retVal = JsonState_number;
            break;
        case '"':
            retVal = JsonState_string;
            break;
        case 'n':
            retVal = JsonState_null;
            break;

        default:
            break;
    }

    return retVal;
}
