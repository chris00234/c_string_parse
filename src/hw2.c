#include "linkedlist.h"
#include "hw2_helpers.h"
#include "hw2.h"

#define BOOL int
#define false 0
#define true 1

// Part 1 Functions
int getSubstrings(char *str, char delim, char **array, int maxSize)
{

    if (*str == '\0' || delim == '\0')
    {
        return 0;
    }
    if (str == NULL || array == NULL || maxSize < 1)
    {
        return -1;
    }

    int value = 0;
    char *ptr = str;
    char **tmp = array;

    *array = (str);
    while (*ptr != '\0')
    {
        if (*ptr == delim)
        {
            *ptr = '\0';
            value++;
            if (value == (maxSize))
            {
                return value;
            }
            tmp = tmp + 1;
            *tmp = (ptr + 1);
        }
        ptr++;
    }
    return (value + 1);
}

void parseMIPSfields(const uint32_t instruction, MIPSfields *f)
{
    // 0x24080539 == 001001 00000 01000 00000 10100 111001
    uint32_t tmp = instruction;
    f->opcode = (tmp >> 26);
    tmp = instruction;

    tmp = tmp << 6;
    tmp = tmp >> 27;
    f->rs = tmp;
    tmp = instruction;

    tmp = tmp << 11;
    tmp = tmp >> 27;
    f->rt = tmp;
    tmp = instruction;

    tmp = tmp << 16;
    tmp = tmp >> 27;
    f->rd = tmp;
    tmp = instruction;

    tmp = tmp << 21;
    tmp = tmp >> 27;
    f->shamt = tmp;
    tmp = instruction;

    tmp = tmp << 26;
    tmp = tmp >> 26;
    f->func = tmp;
    tmp = instruction;

    tmp = tmp << 16;
    tmp = tmp >> 16;
    f->immediate16 = tmp;
    tmp = instruction;

    tmp = tmp << 6;
    tmp = tmp >> 6;
    f->immediate26 = tmp;
    tmp = instruction;

    if (f->opcode == 0)
    {
        f->uid = f->func;
    }
    else
    {
        tmp = tmp >> 26;
        tmp = tmp << 26;
        f->uid = tmp;
    }
}

// Work on edge cases
MIPSinstr *loadInstrFormat(char *line)
{
    if (line == NULL)
    {
        return NULL;
    }
    MIPSinstr *ptr = malloc(sizeof(MIPSinstr));
    char *line_ptr = line;
    ptr->usagecnt = 0;
    if (*line_ptr == 'j' || *line_ptr == 'r' || *line_ptr == 'i')
    {
        ptr->type = *line_ptr;
        line_ptr = line_ptr + 2;
    }
    else
    {
        free(ptr);
        return NULL;
    }
    // j 8400000
    u_int32_t num = 0;
    int temp = 0;
    while (*line_ptr != ' ')
    {
        num = num * 16;
        if (*line_ptr != '0')
        {
            if (*line_ptr >= 'A' && *line_ptr <= 'F')
            {
                temp = *line_ptr - 'A' + 10;
            }
            else if (*line_ptr >= 'a' && *line_ptr <= 'f')
            {
                temp = (*line_ptr) - 'a' + 10;
            }
            else if (*line_ptr >= '0' && *line_ptr <= '9')
            {
                temp = (*line_ptr) - '0';
            }
            else
            {
                free(ptr);
                return NULL;
            }
            num = num + temp;
            line_ptr++;
        }
        else if (*line_ptr == '0')
        {
            line_ptr++;
        }
    }
    ptr->uid = num;
    line_ptr++;
    if (*line_ptr == ' ')
    {
        free(ptr);
        return NULL;
    }
    int alloc_size = countChar(line);
    char *ch_ptr = malloc(alloc_size * sizeof(char));
    char *tmp = ch_ptr;
    while (*line_ptr != ' ')
    {
        *tmp = *line_ptr;
        if (*line_ptr < 97 || *line_ptr > 122)
        {
            free(ch_ptr);
            free(ptr);
            return NULL;
        }
        tmp++;
        line_ptr++;
    }
    *tmp = '\0';
    ptr->mnemonic = ch_ptr;
    line_ptr++;
    if (*line_ptr == ' ' || *line_ptr == '\n')
    {
        free(ptr);
        return NULL;
    }
    int pre = 0;
    while (*line_ptr != '\n')
    {
        pre = pre * 10;
        pre = pre + ((*line_ptr) - '0');
        line_ptr++;
    }
    if (pre <= 10 && pre >= 0)
    {
        ptr->pretty = pre;
    }
    else
    {
        free(ptr);
        return NULL;
    }
    return ptr;
}

// Part 2 Functions
int MIPSinstr_uidComparator(const void *s1, const void *s2)
{
    const MIPSinstr *ptr1 = s1;
    const MIPSinstr *ptr2 = s2;
    if (ptr1->uid < ptr2->uid)
    {
        return -1;
    }
    else if (ptr1->uid == ptr2->uid)
    {
        return 0;
    }
    else if (ptr1->uid > ptr2->uid)
    {
        return 1;
    }
}

void MIPSinstr_Printer(void *data, void *fp)
{
    MIPSinstr *ptr = data;
    FILE *file_ptr = fp;

    fprintf(file_ptr, "%c\t%u\t%u\t%d\t%s\n", ptr->type, ptr->uid, ptr->pretty,
            ptr->usagecnt, ptr->mnemonic);
}

void MIPSinstr_Deleter(void *data)
{
    if (data != NULL)
    {
        MIPSinstr *ptr = data;
        if (ptr->mnemonic != NULL)
            free(ptr->mnemonic);
        free(ptr);
    }
}

node_t *FindInList(list_t *list, void *token)
{
    if (list == NULL || token == NULL || list->length == 0)
    {
        return NULL;
    }
    node_t *t = list->head;

    while (t != NULL)
    {
        if (list->comparator((t->data), token) == 0)
        {
            return t;
        }
        t = t->next;
    }
    return NULL;
}
void DestroyList(list_t **list)
{

    node_t *t = (*list)->head;
    node_t *holder;

    while (t != NULL)
    {

        holder = t->next;

        MIPSinstr_Deleter(t->data);
        free(t);
        t = holder;
    }
    free(*list);
}

// Part 3 Functions
list_t *createMIPSinstrList(FILE *IMAPFILE)
{
    if (IMAPFILE == NULL)
    {
        return NULL;
    }
    char *buffer;
    int buffsize = 50;
    MIPSinstr *MIPSptr;
    buffer = malloc(buffsize * sizeof(char));
    list_t *list = CreateList(MIPSinstr_uidComparator, MIPSinstr_Printer, MIPSinstr_Deleter);

    while (fgets(buffer, buffsize, IMAPFILE) != NULL)
    {
        // buffer = toUpper(buffer);
        MIPSptr = loadInstrFormat(buffer);
        if (FindInList(list, MIPSptr) != NULL)
        {
            DestroyList(&list);
            free(buffer);
            return NULL;
        }
        if (MIPSptr == NULL)
        {
            DestroyList(&list);
            free(buffer);
            return NULL;
        }
        InsertAtHead(list, MIPSptr);
    }

    free(buffer);
    return list;
}

int printInstr(MIPSfields *instr, list_t *MIPSinstrList, char **regNames, FILE *OUTFILE)
{
    MIPSinstr *instr_ptr;
    instr_ptr = malloc(sizeof(MIPSinstr));
    instr_ptr->uid = instr->uid;
    node_t *t = FindInList(MIPSinstrList, instr_ptr);

    if (t == NULL)
    {
        free(instr_ptr);
        return 0;
    }

    switch (((MIPSinstr *)(t->data))->pretty)
    {
    case 0:
        fprintf(OUTFILE, "%s %s\n", ((MIPSinstr *)(t->data))->mnemonic, *(regNames + instr->rd));
        ((MIPSinstr* )(t->data))->usagecnt++;
        break;
    case 1:
        fprintf(OUTFILE, "%s %s, %s\n", ((MIPSinstr *)(t->data))->mnemonic, *(regNames + instr->rs), *(regNames + instr->rt));
        ((MIPSinstr* )(t->data))->usagecnt++;
        break;
    case 2:
        fprintf(OUTFILE, "%s %s, %s, 0x%x\n", ((MIPSinstr *)(t->data))->mnemonic, *(regNames + instr->rt), *(regNames + instr->rs), instr->immediate16);
        ((MIPSinstr* )(t->data))->usagecnt++;
        break;
    case 3:
        fprintf(OUTFILE, "%s %s, %s, %s\n", ((MIPSinstr *)(t->data))->mnemonic, *(regNames + instr->rd), *(regNames + instr->rs), *(regNames + instr->rt));
        ((MIPSinstr* )(t->data))->usagecnt++;
        break;
    case 4:
        fprintf(OUTFILE, "%s %s, 0x%x\n", ((MIPSinstr *)(t->data))->mnemonic, *(regNames + instr->rt), instr->immediate16);
        ((MIPSinstr* )(t->data))->usagecnt++;
        break;
    case 5:
        fprintf(OUTFILE, "%s\n", ((MIPSinstr *)(t->data))->mnemonic);
        ((MIPSinstr* )(t->data))->usagecnt++;
        break;
    case 6:
        fprintf(OUTFILE, "%s 0x%x\n", ((MIPSinstr *)(t->data))->mnemonic, instr->immediate26);
        ((MIPSinstr* )(t->data))->usagecnt++;
        break;
    case 7:
        fprintf(OUTFILE, "%s %s, 0x%x\n", ((MIPSinstr *)(t->data))->mnemonic, *(regNames + instr->rs), instr->immediate16);
        ((MIPSinstr* )(t->data))->usagecnt++;
        break;
    case 8:
        fprintf(OUTFILE, "%s %s, %s, 0x%x\n", ((MIPSinstr *)(t->data))->mnemonic, *(regNames + instr->rd), *(regNames + instr->rs), instr->shamt);
        ((MIPSinstr* )(t->data))->usagecnt++;
        break;
    case 9:
        fprintf(OUTFILE, "%s %s, %s, 0x%x\n", ((MIPSinstr *)(t->data))->mnemonic, *(regNames + instr->rs), *(regNames + instr->rt), instr->immediate16);
        ((MIPSinstr* )(t->data))->usagecnt++;
        break;
    case 10:
        fprintf(OUTFILE, "%s %s, 0x%x\n", ((MIPSinstr *)(t->data))->mnemonic, *(regNames + instr->rt), instr->immediate16);
        ((MIPSinstr* )(t->data))->usagecnt++;
        break;
    }
    free(instr_ptr);
    return 1;
}

// Extra Credit Functions
void MIPSinstr_removeZeros(list_t *list)
{
}

int MIPSinstr_usagecntComparator(const void *s1, const void *s2)
{

    return 0xDEADBEEF;
}

void MIPSinstr_statPrinter(void *data, void *fp)
{
}

void sortLinkedList(list_t *list)
{
}
