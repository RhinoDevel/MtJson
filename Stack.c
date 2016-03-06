
// MT, 2016feb28

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Stack.h"
#include "Deb.h"

#ifndef NDEBUG
void Stack_debug_print_char(struct Stack * const inStack)
{
    assert(inStack!=NULL);

    struct StackEle const * iter = inStack->top;

    do
    {
        assert(iter->val!=NULL);
        Deb_line("%c", *((char*)(iter->val)));

        iter = iter->below;
    }while(iter!=NULL);
}
#endif //NDEBUG

void Stack_push(struct Stack * const inStack, void * const inVal)
{
    assert(inStack!=NULL);

    inStack->top = StackEle_create(inVal, inStack->top);

#ifndef NDEBUG
    //Deb_line("CHAR STACK PUSH:");
    //Stack_debug_print_char(inStack);
#endif //NDEBUG
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

    //Deb_line("STACK POP.");
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
