
// MT, 2016feb26

#include <assert.h>
#include "Obj.h"
#include "Deb.h"
#include "Stack.h"
#include "json_state_arr_begin.h"

enum JsonState json_state_arr_begin(struct JsonStateInput * const inObj)
{
    enum JsonState retVal = JsonState_err;

    assert(inObj!=NULL);
    assert(inObj->i<inObj->len);
    assert(inObj->str[inObj->i]=='[');

    ++inObj->i;
    Deb_line("[");

    Stack_push(inObj->stack, Obj_char_create(']'));

    if(inObj->i<inObj->len)
    {
        if(inObj->str[inObj->i]==']')
        {
            retVal = JsonState_arr_end;
        }
        else
        {
            retVal = JsonState_val_begin;
        }
    }

    return retVal;
}
