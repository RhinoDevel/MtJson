
// MT, 2016mar07

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "JsonProp.h"

void JsonProp_delete(struct JsonProp * const inJsonProp)
{
    assert(inJsonProp!=NULL);
    assert(inJsonProp->name!=NULL);

    free(inJsonProp->name);
    if(inJsonProp->ele!=NULL)
    {
        JsonEle_delete(inJsonProp->ele); // *** RECURSION (see JsonEle). ***
    }
    free(inJsonProp);
}

struct JsonProp * JsonProp_create(char * const inName)
{
    struct JsonProp * const retVal = malloc(sizeof *retVal);
    struct JsonProp const buf = (struct JsonProp)
    {
        .name = inName,
        .ele = NULL
    };

    assert(inName!=NULL);
    assert(retVal!=NULL);

    memcpy(retVal, &buf, sizeof *retVal);

    return retVal;
}
