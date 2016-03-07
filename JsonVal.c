
// MT, 2016mar07

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "JsonVal.h"
#include "JsonEle.h"
#include "JsonProp.h"

void JsonVal_delete(struct JsonVal * const inJsonVal)
{
    assert(inJsonVal!=NULL);

    switch(inJsonVal->type)
    {
        case JsonType_null:
            assert(inJsonVal->val==NULL);
            break;

        case JsonType_boolean:
        case JsonType_number:
        case JsonType_string:
            assert(inJsonVal->val!=NULL);
            free(inJsonVal->val);
            break;

        case JsonType_arr:
        case JsonType_obj:
            if(inJsonVal->val!=NULL)
            {
                JsonEle_delete((struct JsonEle *)(inJsonVal->val)); // *** RECURSION (see JsonEle). ***
            }
            //
            // Otherwise: Empty array/object.

            break;

        case JsonType_prop:
            assert(inJsonVal->val!=NULL);
            JsonProp_delete((struct JsonProp *)(inJsonVal->val)); // *** RECURSION (see JsonProp). ***
            break;

        default:
            assert(false);
            break;
    }

    free(inJsonVal);
}

struct JsonVal * JsonVal_create(enum JsonType const inType, void * const inVal)
{
    struct JsonVal * const retVal = malloc(sizeof *retVal);
    struct JsonVal const buf = (struct JsonVal)
        {
            .type = inType,
            .val = inVal
        };

    assert(retVal!=NULL);

    memcpy(retVal, &buf, sizeof *retVal);

    return retVal;
}
