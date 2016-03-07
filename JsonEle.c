
// MT, 2016mar07

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "JsonEle.h"

void JsonEle_delete(struct JsonEle * const inJsonEle)
{
    assert(inJsonEle!=NULL);

    struct JsonEle * cur = inJsonEle,
        * next = NULL;

    do
    {
        next = cur->next;
        JsonVal_delete(cur->val); // *** RECURSION (see JsonVal). ***
        free(cur);
    }while(next!=NULL);
}

struct JsonEle * JsonEle_create(enum JsonType const inType, void * const inVal)
{
    struct JsonEle * const retVal = malloc(sizeof *retVal);
    struct JsonEle const buf = (struct JsonEle)
        {
            .val = inVal,
            .next = NULL
        };

    assert(inVal!=NULL);
    assert(retVal!=NULL);

    memcpy(retVal, &buf, sizeof *retVal);

    return retVal;
}
