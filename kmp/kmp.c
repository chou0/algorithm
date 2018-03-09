#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int* get_next(char *patter);

int kmp(char *string, char *patter)
{
    unsigned int *next = get_next(patter);   
    int i, len = strlen(patter);
    
    for (i = 0; i < len; i++)
    {
        printf("%d ", next[i]);
    }
    printf("\n");
    
    int slen = strlen(string);
    int j = 0;
    
    for (i = 0; i < slen; )
    {
        while (string[i] == patter[j])
        {
            i++;
            j++;
            if (j == len)
            {
                free(next);
                return (i - j);
            }
        }
        
        if (j)
        {
            j = next[j - 1];
        }
        else
        {
            i++;    
        }
    }
    
    free(next);
    return -1;
}

unsigned int* get_next(char *patter)
{
    int len = strlen(patter);
    int i,j,k;
    unsigned int *next = NULL;
    
    if (NULL == (next = calloc(sizeof(int), len)))
    {
        printf("get memory failed\n");
        return NULL;
    }
    
    for (i = 1; i < len; )
    {
        j = 0;
        k = i;
        while (patter[k] == patter[j])
        {
            next[k] = (k - i + 1);
            j++;
            k++;        
        }
	
	    if (i != k)
	    {
		    i = k;
	    }
	    else
	    {
		    i++;
	    }
    }
    
    return next;
}

int main(int argc, char **args)
{
    if (argc != 3)
    {
        printf("usage: %s string patter\n", args[0]);
        return -1;
    }
    
    int ret = kmp(args[1], args[2]);
    
    printf("index: %d\n", ret);
    return 0;
}
