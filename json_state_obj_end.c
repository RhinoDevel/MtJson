
// MT, 2016mar03

#include <assert.h>
#include "Obj.h"
#include "Deb.h"
#include "Stack.h"
#include "json_state_obj_end.h"

enum JsonState json_state_obj_end(struct JsonStateInput * const inObj)
{
    enum JsonState retVal = JsonState_err;
    void const * buf = NULL;

    assert(inObj!=NULL);
    assert(inObj->i<inObj->len);
    assert(inObj->str[inObj->i]=='}');

    ++inObj->i;
    Deb_line("}");

    buf = Stack_top(inObj->stack);
    if(*((char*)buf)=='p')
    {
        Stack_pop(inObj->stack);
    }

    buf = Stack_pop(inObj->stack);
    if((buf!=NULL)&&(*((char*)buf)=='}'))
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
