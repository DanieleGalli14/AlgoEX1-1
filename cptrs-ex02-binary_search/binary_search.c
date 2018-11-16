/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static void *binary_search(const void *key, const void *base, size_t num_elem, size_t elem_size, int (*compar)(const void *, const void *));

static int int_cmp(const void* key, const void* elem);

static int str_cmp(const void* key, const void* elem);


void *binary_search(const void *key, const void *base, size_t num_elem, size_t elem_size, int (*compar)(const void *, const void *))
{
    assert( key != NULL );
    assert( base != NULL );
    assert( compar != NULL );

    size_t lo = 0;
    size_t hi = num_elem - 1;
    size_t mid;
    const unsigned char * pc1 = key;
    const unsigned char * pc2 = base;
    
    while(lo <= hi)
    {
        mid = (lo + hi)/2;
        
        if(compar(pc1, &pc2[mid*elem_size]) < 0)
        {
            hi = mid - elem_size;
        }
        else 
            if (compar(pc1, &pc2[mid*elem_size]) > 0)
            {
                lo = mid + elem_size;
            }
            else
                {
                    return &pc2[mid*elem_size];
                }
    }
    return NULL;
}

int int_cmp(const void *pkey, const void *pelem)
{
    const int *pk = pkey;
    const int *pe = pelem;

    assert( pk != NULL );
    assert( pe != NULL );

    return (*pk > *pe) ? 1 : ((*pk < *pe) ? -1 : 0);
}

int str_cmp(const void *pkey, const void *pelem)
{
    const char **pk = (const char**) pkey;
    const char **pe = (const char**) pelem;

    assert( pk != NULL );
    assert( pe != NULL );

    //fprintf(stderr, "key: '%s', candidate: '%s' -> cmp: %d\n", *pk, *pe, strcmp(*pk, *pe));

    return strcmp(*pk, *pe);
}

int main()
{
    int iary[] = {1, 20, 25, 32, 76, 123};
    int ikey = 76;
    int *ires = NULL;
    int *ires_check = NULL;
    const char *sary[] = {"e01","e02","e03","e04","e05","e06"};
    const char *skey = "e01";
    char **sres = NULL;
    char **sres_check = NULL;

    ires = binary_search(&ikey, iary, sizeof iary/sizeof iary[0], sizeof iary[0], int_cmp);
    ires_check = bsearch(&ikey, iary, sizeof iary/sizeof iary[0], sizeof iary[0], int_cmp);
    assert( ires == ires_check );
    printf("Key %d -> %s (element: %d)\n", ikey, (ires != NULL) ? "found" : "not found", *ires); 

    sres = binary_search(&skey, sary, sizeof sary/sizeof sary[0], sizeof sary[0], str_cmp);
    sres_check = bsearch(&skey, sary, sizeof sary/sizeof sary[0], sizeof sary[0], str_cmp);
    assert( sres == sres_check );
    printf("Key '%s' -> %s (element: '%s')\n", skey, (sres != NULL) ? "found" : "not found", *sres); 

    return 0;
}
