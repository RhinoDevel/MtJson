
// MT, 2016mar01

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Obj.h"
#include "Str.h"

double* Str_double_create(char const * const inStr, size_t const inLen, size_t * const inOutIndex)
{
    double *retVal = NULL,
        buf = 0.0;
    char * endPtr = NULL;

    assert(inStr!=NULL);
    assert(inOutIndex!=NULL);

    if((*inOutIndex)<inLen)
    {
        buf = strtod(inStr+(*inOutIndex), &endPtr);
    }

    size_t const consumeLen = (size_t)(endPtr-(inStr+(*inOutIndex)));

    if(consumeLen>0)
    {
        retVal = Obj_double_create(buf);
        *inOutIndex = (*inOutIndex)+consumeLen;
    }

    return retVal;
}

char* Str_string_create(char const * const inStr, size_t const inLen, char const inTag, size_t * const inOutIndex)
{
    char *retVal = NULL,
        *buf = NULL;

    do
    {
        size_t terminatorPos = 0;

        if(((*inOutIndex)+2)>=inLen)
        {
            break;
        }
        if(inStr[*inOutIndex]!=inTag)
        {
            break;
        }

        ++(*inOutIndex);

        size_t const firstCharPos = *inOutIndex;

        while((*inOutIndex)<inLen)
        {
            if(inStr[*inOutIndex]==inTag)
            {
                // MT_TODO: TEST: Adding '\' to output is wrong,
                //                because '\"' is just standing for one character - fix this!
                //
                if(inStr[(*inOutIndex)-1]!='\\')
                {
                    terminatorPos = *inOutIndex;
                    ++(*inOutIndex); // (consumes closing ")
                    break;
                }
            }
            ++(*inOutIndex);
        }
        if(terminatorPos==0)
        {
            break;
        }

        size_t const len = terminatorPos-firstCharPos; // (without terminator)

        buf = malloc((sizeof *buf)*(len+1));

        assert(buf!=NULL);

        strncpy(buf, inStr+firstCharPos, len);
        buf[len] = '\0';

        retVal = buf;
        buf = NULL;
    }while(false);

    free(buf);
    return retVal;
}
