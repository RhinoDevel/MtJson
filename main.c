
// MT, 2016feb29

//NDEBUG

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "JsonEle.h"
#include "json.h"

int main()
{
    char /*const*/ * const testStr[] = {
       "{}",
       "[]",
       "[{}]",
       "[false,true,false,true]",
       "{\"a\":null}",
       "{\"a\":null,\"b\":null}",
       "{\"a\":1234,\"b\":1234.5678}",
       "{\"a\":{\"b\":null}}",
       "{\"a\":{\"b\":null,\"c\":true}}",
       "{\"a\":{\"a-b\":null,\"a-c\":true}}",
       "{\"a\":[],\"b\":null}",
       "{\"a\":{},\"b\":false}",
       "{\"a\":{\"a1\":[[{}]],\"a2\":null},\"myArr\":[1e-3,\"Eat my \\\"shorts!\",2E+5,3E4,null,[0,false,123,[]],[[]],[[false,-8.342,false],77e7]]}",
       "{\"myArr\":[],\"myObj\":{}}",
       "[{\"myArr\":[],\"myObj\":{\"subArr\":[null,false,true,0.0,-42,\"beerbarreltree\"],\"subObj\":{}}}]"
    };
    int const testStrCnt = (int)(sizeof testStr/sizeof *testStr),
        startIndex = 0,
        endIndex = testStrCnt-1;
    int i = 0;

    assert(endIndex>=startIndex);
    assert(endIndex<=testStrCnt);

    for(i = startIndex;i<=endIndex;++i)
    {
        struct JsonEle * const root = json_parse(testStr[i], false);
        char * str = NULL;

        if(root==NULL)
        {
            printf("Parse test at index %d failed: \"%s\"!\n", i, testStr[i]);
            break;
        }
        printf("Parse test at index %d succeeded.", i);

        str = json_stringify(root, true);

        printf(" Stringify result: \"%s\".\n", str);

        free(str);
    }
    if(i==testStrCnt)
    {
        printf("All %d test(-s) ran succeeded.\n", testStrCnt-startIndex);
    }

    return EXIT_SUCCESS;
}
