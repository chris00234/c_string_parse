#include <stdio.h>
#include <stdlib.h>

#include "hw2_helpers.h"
#include "hw2.h"
#include "linkedlist.h"

int main()
{
    // FILE *f = fopen("rsrc/instr_map.txt", "r");
    // createMIPSinstrList(f);
    //  Sample testing main for part 1, one test per function
    //  NOTE: no where near exhaustive
    char *toSubstring2 = "-1a22.3aaaaaaa+";        // pointer to static string!
    char *toSubstring = malloc(16 * sizeof(char)); // dynamic space for 16 chars (15 + null terminator)
    char *toSubstringSeek = toSubstring;           // Don't want to lose reference to start of malloc space!

    // no string.h strcpy (need to copy so toSubstring may be modified)
    while ((*toSubstringSeek++ = *toSubstring2++))
        ;
    // what does toSubstring2 print now?

    int size = 2;
    char **substrings = malloc(2 * sizeof(char *));
    int numSubstrings = getSubstrings(toSubstring, 'a', substrings, 2);
    // Print the resultant substrings
    for (int i = 0; i < numSubstrings; i++)
    {
        printf("Substring %d: \"%s\"\n", i, *(substrings + i));
    }

    free(substrings);
    free(toSubstring);

    // Test for parseMIPSfields
    uint32_t instrValue = 0x24080539;
    MIPSfields *myFields = malloc(sizeof(MIPSfields));
    parseMIPSfields(instrValue, myFields);

    printf("opcode = %u\n", myFields->opcode);
    printf("rs = %u\n", myFields->rs);
    printf("rt = %u\n", myFields->rt);
    printf("rd = %u\n", myFields->rd);
    printf("shamt = %u\n", myFields->shamt);
    printf("func = %u\n", myFields->func);
    printf("immediate16 = %u\n", myFields->immediate16);
    printf("immediate26 = %u\n", myFields->immediate26);
    printf("uid = %u\n", myFields->uid);

    free(myFields);

    // Test for loadInstrFormat
    MIPSinstr *myInstr = loadInstrFormat("j C000000 brandnewmipsinstruction 10\n"); // Can you call getStubstrings on this string directly?

    if (myInstr == NULL)
    {
        printf("loadInstrFormat returned NULL.\n");
    }
    else
    {
        printf("type = %c\n", myInstr->type);
        printf("uid = %u\n", myInstr->uid);
        printf("pretty = %u\n", myInstr->pretty);
        printf("mnemonic = %s\n", myInstr->mnemonic); // should be address on the heap!
        printf("usagecnt = %d\n", myInstr->usagecnt); // should be 0!

        // running valgrind will have memory leak here until you implement MIPSinstr_Deleter in Part 2
        // MIPSinstr_Deleter(myInstr);

        // After deletion where does myInstr point?
        if (myInstr == NULL)
            printf("How did you do that?!?!");
        else
            myInstr = NULL;
    }

    return 0;
}
