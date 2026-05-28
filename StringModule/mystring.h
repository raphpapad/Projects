#include <stdio.h>
#include <assert.h>
#include <stddef.h> // defines macros (kai allou tupou parametrwn)

size_t ms_length (const char *s1);							 /* strlen */

char *ms_copy(char *dest, const char *src);                  /* strcpy */

char *ms_ncopy(char *dest, const char *src, size_t n);       /* strncpy */

char *ms_concat(char *dest, const char *src);                /* strcat */

char *ms_nconcat(char *dest, const char *src, size_t n);     /* strncat */

int ms_compare(const char *s1, const char *s2);             /* strcmp */

int ms_ncompare(const char *s1, const char *s2, size_t n);  /* strncmp */

char *ms_search(const char *str1, const char *str2);	    /* strstr */
