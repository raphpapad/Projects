#include <stdio.h>
#include <assert.h>
#include <stddef.h> 
/* defines macros (kai allou tupou parametrwn) */

/* strlen */
size_t ms_length (const char *s1);							

/* strcpy */
char *ms_copy(char *dest, const char *src);                  

/* strncpy */
char *ms_ncopy(char *dest, const char *src, size_t n);       

/* strcat */
char *ms_concat(char *dest, const char *src);                

/* strncat */
char *ms_nconcat(char *dest, const char *src, size_t n);     

/* strcmp */
int ms_compare(const char *s1, const char *s2);             

/* strncmp */
int ms_ncompare(const char *s1, const char *s2, size_t n); 

/* strstr */
char *ms_search(const char *str1, const char *str2);	    
