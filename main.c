#include "includes/malloc.h"



int main()
{

    char *ptr  = (char *)malloc(2);
    ptr[0] = 'a';
    ptr[1] = '\0';


        printf ("%s\n", ptr);
    
    return (0);
}
