#include "mystring.h"

	size_t ms_length(const char *pcStr) /* strlen */
 	{	
    	size_t uiLength = 0U;
    	assert(pcStr != NULL);
    
    	while (*(pcStr + uiLength) != '\0')
       		uiLength++;
       
    	return uiLength;
 	}
 	
 	char *ms_copy(char *dest, const char *src) /* strcpy */
 	{
		char *tmp = dest;
		assert(src);
	
		while(*src != '\0')
		{
			*dest++ = *src++;
		}
		
		*dest = '\0';
		return tmp;
 	}
 	
 	char *ms_ncopy(char *dest, const char *src, size_t n) /* strncpy */
 	{
 		char *tmp = dest;
 		int j = 0;
 		assert(src);
 	
 		while(j != n)
 		{
 			if(*src != '\0')
 				*dest++ = *src++;
				
 			else
			{
 				*dest = '\0';	
				break;
			}
			
			j++;
 		}
 	
 		*dest = '\0';
 		return tmp;
 	}
 	
 	char *ms_concat(char *dest, const char *src)
 	{
 		int j = 0; /* l = 0; */
		char *tmp = dest;
		assert(src);
		
		for(j = 0; *dest != '\0'; j++)
			dest++;
		
		for(; *src != '\0'; dest++, src++) /* for(l = 0; *src != '\0'; l++) */
			*dest = *src;
		
		*dest = '\0';
		return tmp;
	 }
	 
 	char *ms_nconcat(char *dest, const char *src, size_t n)
 	{
		char *tmp = dest;
		assert(src);
	
		while(*dest != '\0')
			dest++;
			
		ms_ncopy(dest, src, n);	
	
		return tmp;
 	}
 	
 	int ms_compare(const char *s1, const char *s2)
 	{
		/*size_t j = 0;*/
		assert(s1 != NULL && s2 != NULL);
	
    	while(*s1 == *s2)
    	{
        	if(*s1 == '\0' && *s2 == '\0') 
				return 0;
				
			s1++;
			s2++;		
		}
        
    	return ((*s1 < *s2) ? -1 : +1);
 	}
 	
 	int ms_ncompare(const char *s1, const char *s2, size_t n)
 	{
		size_t j = 0;
		assert(n >= 0); /* n != 0 */
		assert(s1 && s2);
	
		while(*s1 == *s2 && j!=n)
		{
			if(*s1 == '\0' || *s2 == '\0' || j == n-1)
				return 0;
			
			s1++;
			s2++;
			j++;
		}
		
		return ((*s1 < *s2) ? -1 : +1);
 	}
 	
	/* Ekdoxi1
 	char *ms_search(const char *str1, const char *str2) // strstr 
 	{
		size_t j, l;
		const char *pos, *tmp;
		assert(str1 && str2);
	
		for(l = 0; l < ms_length(str1); l++, str1++, str2++)
		{
		 	if(*str1 == *str2)
		 	{
		 		pos = str1;
				tmp = str2;
		 		for(j = 0; j < ms_length(str2); j++, pos++, tmp++)
		 		{
		 			if(*pos != *tmp)
		 				break;
				}
				if(j == ms_length(str2)) 
					return(char *) str1;
		 	}
		}
		return NULL;
 	}*/

	char *ms_search(const char *str1, const char *str2) { // Ekdosxi2: strstr 
		size_t j, str2_length, path_length;

		assert(str1 != NULL && str2 != NULL);

		str2_length = ms_length(str2);
		path_length = ms_length(str1) - str2_length;

		for (j = 0U; j <= path_length; j++, str1++) {
			if (!ms_ncompare(str1, str2, str2_length)) {
				return str1;
			}
		}

		return NULL;
	}

	int main(void)
	{
		//char str1[100] = "Sire command as";
		//char str[100];

		//printf("%d\n", ms_length("Hello World") );
		
		//printf("%s\n", ms_copy(str,"Hello World") );
		//printf("%s\n", ms_ncopy(str,"Hello World", 6) );
		
		//printf("%s\n", ms_concat(str1,",Spears ready") );
		//printf("%s\n", ms_nconcat(str1,",Spears ready", 7) );
		
		//printf("%d\n", ms_compare("hello", "hello"));
		//printf("%d\n", ms_ncompare("hello", "hella", 2) );
		
		//printf("%s\n", ms_search(str1, "re") );

		return 0;
	}
