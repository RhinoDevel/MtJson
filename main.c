
// MT, 2016feb29

//#define NDEBUG

#include <stdio.h>
#include <stdlib.h>
#include "json.h"

int main()
{
    bool const isValid = json_parse("[1e-3,\"Eat my \\\"shorts!\",2E+5,3E4,null,[0,false,123,[]],[[]],[[false,-8.342,false],77e7]]", false);

    printf(isValid?"VALID":"INVALID");
    printf("\n");

    return EXIT_SUCCESS;
}
