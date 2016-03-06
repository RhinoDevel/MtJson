
// MT, 2016feb29

#include <assert.h>
#include "Obj.h"
#include "Deb.h"
#include "Stack.h"
#include "json_state_arr_end.h"

enum JsonState json_state_arr_end(struct JsonStateInput * const inObj)
{
    enum JsonState retVal = JsonState_err;

    assert(inObj!=NULL);
    assert(inObj->i<inObj->len);
    assert(inObj->str[inObj->i]==']');

    ++inObj->i;
    Deb_line("]");

    void const * const pop = Stack_pop(inObj->stack);

    if((pop!=NULL)&&(*((char*)pop)==']'))
    {
        if(inObj->i<inObj->len)
        {
            retVal = JsonState_val_end;
        }
        else
        {
            if(Stack_isEmpty(inObj->stack))
            {
                retVal = JsonState_done;
            }
        }
    }

    return retVal;
}
