
// MT, 2016mar07

#ifndef MT_JSONPROP
#define MT_JSONPROP

#include "JsonVal.h"

#ifdef	__cplusplus
extern "C" {
#endif //__cplusplus

struct JsonProp
{
    char * const name;
    struct JsonVal * const val;
};

/** Delete property.
 *
 *  - Also deletes name and JSON value objects from heap.
 */
void JsonProp_delete(struct JsonProp * const inJsonProp);

/** Create property.
 *
 *  - Takes ownership of given name and JSON value.
 */
struct JsonProp * JsonProp_create(char * const inName, struct JsonVal * const inVal);

#ifdef	__cplusplus
}
#endif //__cplusplus

#endif //MT_JSONELE
