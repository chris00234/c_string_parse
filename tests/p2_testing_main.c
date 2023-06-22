#include <stdio.h>
#include <stdlib.h>

#include "hw2_helpers.h"
#include "hw2.h"
#include "linkedlist.h"

int main(void) {

    printf("\n****Compare MIPSinstr by uid*****\n");
    MIPSinstr f1 = {'r',0x9,2,"jalr",10};
    MIPSinstr f2 = {'i',0x84000000,4,"lh",0};
    int success = MIPSinstr_uidComparator(&f1, &f2);

    if(success < 0)
        printf("MIPSinstr f1 (0x%08x) is before MIPSinstr f1 (0x%08x)\n", f1.uid, f2.uid);
    else if (success > 0)
        printf("MIPSinstr f1 (0x%08x) is after MIPSinstr f1 (0x%08x)\n", f1.uid, f2.uid);
    else
        printf("MIPSinstr f1 (0x%08x) equal to MIPSinstr f2 (0x%08x)\n", f1.uid, f2.uid);


    printf("\n****Print MIPSinstr*****\n");
    MIPSinstr_Printer(&f1, stderr);  // print to struct to stderr
    MIPSinstr_Printer(&f2, stdout);  // print to struct to stdout - Why do they both appear on the terminal?

    //Test MIPSinstr_Deleter using p1_testing_main


    // Combine the examples for creation and intialization of a generic linked list 
    // from linkedlisttest_main.c with the function above to test FindInList & DestroyList

    return 0;
}
