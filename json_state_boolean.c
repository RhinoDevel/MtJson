
// MT, 2016feb29

#include <assert.h>
#include <string.h>
#include "Deb.h"
#include "Stack.h"
#include "Obj.h"
#include "json_state_boolean.h"

enum JsonState json_state_boolean(struct JsonStateInput * const inObj)
{
    enum JsonState retVal = JsonState_err;

    assert(inObj!=NULL);
    assert(inObj->i<inObj->len);
    assert((inObj->str[inObj->i]=='t')||(inObj->str[inObj->i]=='f'));
    assert(!Stack_isEmpty(inObj->stack));

    switch(inObj->str[inObj->i])
    {
        case 't':
            if((inObj->i+3)<inObj->len)
            {
                if(strncmp(inObj->str+inObj->i, "true", 4)==0)
                {
                    inObj->i += 4;
                    //Deb_line("true");
                    *(inObj->pos) = JsonEle_create(JsonType_boolean, Obj_bool_create(true));
                    assert(*(inObj->pos)!=NULL);
                    inObj->pos = &((*(inObj->pos))->next);

                    retVal = JsonState_val_end;
                }
            }
            break;
        case 'f':
            if((inObj->i+4)<inObj->len)
            {
                if(strncmp(inObj->str+inObj->i, "false", 5)==0)
                {
                    inObj->i += 5;
                    //Deb_line("false");
                    *(inObj->pos) = JsonEle_create(JsonType_boolean, Obj_bool_create(false));
                    assert(*(inObj->pos)!=NULL);
                    inObj->pos = &((*(inObj->pos))->next);

                    retVal = JsonState_val_end;
                }
            }
            break;

        default:
            break;
    }

    return retVal;
}
