/* DO NOT MODIFY THIS FILE. FILE WILL BE REPLACED DURING GRADING */

#ifndef HW2_H
#define HW2_H

// Needed C stdlib headers
// Do not add to this list
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "linkedlist.h"

// Part 1 structures
typedef struct { 
    uint8_t opcode;
    uint8_t rs;
    uint8_t rt;
    uint8_t rd;
    uint8_t shamt;
    uint8_t func;
    uint16_t immediate16;
    uint32_t immediate26;
    uint32_t uid;
} MIPSfields; 

typedef struct instr {
    char type;
    uint32_t uid;
    uint8_t pretty;
    char* mnemonic;
    int usagecnt;
} MIPSinstr;


// Part 1 Function Declarations
int getSubstrings(char *,  char, char **, int); 
void parseMIPSfields(const uint32_t, MIPSfields*);
MIPSinstr* loadInstrFormat(char*);

// Part 2 Function Declarations
int MIPSinstr_uidComparator(const void*, const void*);
void MIPSinstr_Printer(void*, void*);
void MIPSinstr_Deleter(void*);
node_t* FindInList(list_t*, void*);
void DestroyList(list_t**);

// Part 3 Constant


// Part 3 Function Declarations
list_t* createMIPSinstrList(FILE*);
int printInstr(MIPSfields*, list_t*, char**, FILE*);

// Extra Credit Function Declarations
void MIPSinstr_removeZeros(list_t*);
int MIPSinstr_usagecntComparator(const void*, const void*);
void MIPSinstr_statPrinter(void*, void*);
void sortLinkedList(list_t*);


#endif
