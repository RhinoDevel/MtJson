
// MT, 2016feb26

#include <string.h>
#include <assert.h>
#include "JsonState.h"
#include "JsonStateInput.h"
#include "json_state_begin.h"
#include "json_state_arr_begin.h"
#include "json_state_arr_end.h"
#include "json_state_val_next.h"
#include "json_state_val_begin.h"
#include "json_state_val_end.h"
#include "json_state_boolean.h"
#include "json_state_null.h"
#include "json_state_number.h"
#include "json_state_string.h"
#include "json.h"

bool json_parse(char * const inStr, bool const inTakeOwnership)
{
    bool retVal = false,
        loop = true;
    struct JsonStateInput * const obj = JsonStateInput_create(inStr, inTakeOwnership);
    enum JsonState state = JsonState_begin;

    do
    {
        switch(state)
        {
            case JsonState_begin:
                state = json_state_begin(obj);
                break;

            case JsonState_arr_begin:
                state = json_state_arr_begin(obj);
                break;

            case JsonState_arr_end:
                state = json_state_arr_end(obj);
                break;

            case JsonState_val_next:
                state = json_state_val_next(obj);
                break;

            case JsonState_val_begin:
                state = json_state_val_begin(obj);
                break;

            case JsonState_val_end:
                state = json_state_val_end(obj);
                break;

            case JsonState_boolean:
                state = json_state_boolean(obj);
                break;

            case JsonState_null:
                state = json_state_null(obj);
                break;

            case JsonState_number:
                state = json_state_number(obj);
                break;

            case JsonState_string:
                state = json_state_string(obj);
                break;

            case JsonState_obj_begin:
            case JsonState_obj_end:

            case JsonState_err:
            default:
                loop = false;
                break;

            case JsonState_done:
                loop = false;
                retVal = true;
                break;
        }
    }while(loop);

    JsonStateInput_delete(obj);
    return retVal;
}

