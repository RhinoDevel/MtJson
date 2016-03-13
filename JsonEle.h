
// MT, 2016mar06

#ifndef MT_JSONELE
#define MT_JSONELE

#include <stdbool.h>
#include "JsonType.h"
#include "JsonVal.h"

#ifdef	__cplusplus
extern "C" {
#endif //__cplusplus

struct JsonEle
{
    struct JsonVal * val;
    struct JsonEle * next;
};

/** Deletes JSON element.
 *
 *  - Also deletes its JSON value object.
 */
void JsonEle_delete(struct JsonEle * const inJsonEle);

/** Creates new JSON element.
 *
 *  - Takes ownership of given value object.
 */
struct JsonEle * JsonEle_create(enum JsonType const inType, void * const inVal);

#ifdef	__cplusplus
}
#endif //__cplusplus

#endif //MT_JSONELE
