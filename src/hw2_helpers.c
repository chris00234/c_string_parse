// Define any helper functions here
int countChar(char *str)
{
    int num = 0;
    char *ptr = str;
    while (*ptr != '\0')
    {
        num++;
        ptr++;
    }
    return num;
}

char *toUpper(char *str)
{
    char *ptr = str;
    ptr++;
    ptr++;
    while (*ptr != ' ')
    {
        if (*ptr >= 'a' && *ptr <= 'z')
        {
            *ptr = *ptr - 32;
        }
        ptr++;
    }
    return str;
}