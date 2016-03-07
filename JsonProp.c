
// MT, 2016mar07

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "JsonProp.h"

void JsonProp_delete(struct JsonProp * const inJsonProp)
{
    assert(inJsonProp!=NULL);
    assert(inJsonProp->name!=NULL);
    assert(inJsonProp->val!=NULL);

    free(inJsonProp->name);
    JsonVal_delete(inJsonProp->val); // *** RECURSION (see JsonVal). ***
    free(inJsonProp);
}

struct JsonProp * JsonProp_create(char * const inName, struct JsonVal * const inVal)
{
    struct JsonProp * const retVal = malloc(sizeof *retVal);
    struct JsonProp const buf = (struct JsonProp)
    {
        .name = inName,
        .val = inVal
    };

    assert(inName!=NULL);
    assert(inVal!=NULL);
    assert(retVal!=NULL);

    memcpy(retVal, &buf, sizeof *retVal);

    return retVal;
}
