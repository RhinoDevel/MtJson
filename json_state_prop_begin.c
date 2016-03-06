
// MT, 2016feb29

#include <assert.h>
#include <stdlib.h>
#include "Obj.h"
#include "Deb.h"
#include "Str.h"
#include "json_state_prop_begin.h"

enum JsonState json_state_prop_begin(struct JsonStateInput * const inObj)
{
    enum JsonState retVal = JsonState_err;

    assert(inObj!=NULL);
    assert(inObj->i<inObj->len);
    assert(!Stack_isEmpty(inObj->stack));
    assert(*((char*)Stack_top(inObj->stack))=='}');
    assert(inObj->str[inObj->i]=='"');

    char * const prop = Str_string_create(inObj->str, inObj->len, '"', &(inObj->i));

    if(prop!=NULL)
    {
        Deb_line("\"%s\"", prop);
        free(prop);

        if(inObj->str[inObj->i]==':')
        {
            ++inObj->i;
            Deb_line(":");

            Stack_push(inObj->stack, Obj_char_create('p'));

            retVal = JsonState_val_begin;
        }
    }

    return retVal;
}
