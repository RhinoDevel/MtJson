
// MT, 2016mar01

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "Deb.h"
#include "Str.h"
#include "Stack.h"
#include "json_state_number.h"

enum JsonState json_state_number(struct JsonStateInput * const inObj)
{
    assert(inObj!=NULL);
    assert(!Stack_isEmpty(inObj->stack));

    enum JsonState retVal = JsonState_err;
    double * const val = Str_double_create(inObj->str, inObj->len, &(inObj->i));

    if(val!=NULL)
    {
        //Deb_line("%f", *val);
        *(inObj->pos) = JsonEle_create(JsonType_number, val); // (takes ownership of val)
        assert(*(inObj->pos)!=NULL);
        inObj->pos = &((*(inObj->pos))->next);

        retVal = JsonState_val_end;
    }

    return retVal;
}
