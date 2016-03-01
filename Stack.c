
// MT, 2016feb28

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Stack.h"

void Stack_push(struct Stack * const inStack, void * const inVal)
{
    assert(inStack!=NULL);

    inStack->top = StackEle_create(inVal, inStack->top);
}

void* Stack_pop(struct Stack * const inStack)
{
    void* retVal = Stack_top(inStack);

    if(retVal!=NULL)
    {
        struct StackEle * const below = inStack->top->below;

        StackEle_delete(inStack->top, false);
        inStack->top = below;
    }

    return retVal;
}

void* Stack_top(struct Stack const * const inStack)
{
    void* retVal = NULL;

    assert(inStack!=NULL);

    if(!Stack_isEmpty(inStack))
    {
        retVal = inStack->top->val;
    }

    return retVal;
}

void Stack_clear(struct Stack * const inStack)
{
    assert(inStack!=NULL);

    while(!Stack_isEmpty(inStack))
    {
        void * const val = Stack_pop(inStack);

        if(inStack->takesOwnership)
        {
            free(val);
        }
    }
}

void Stack_delete(struct Stack * const inStack)
{
    Stack_clear(inStack);
    free(inStack);
}

struct Stack * Stack_create(bool const inTakesOwnership)
{
    struct Stack * const retVal = malloc(sizeof *retVal),
        buf = (struct Stack){ .takesOwnership = inTakesOwnership, .top = NULL };

    assert(retVal!=NULL);

    memcpy(retVal, &buf, sizeof *retVal);

    return retVal;
}

bool Stack_isEmpty(struct Stack const * const inStack)
{
    assert(inStack!=NULL);

    return inStack->top==NULL;
}
