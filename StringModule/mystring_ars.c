#include "mystring.h"

	size_t ms_length(const char pcStr[])
 	{	
    	size_t uiLength = 0U; /* 0U = unsigned int */
    	assert(pcStr != NULL);
    
    	while (pcStr[uiLength] != '\0')
       		uiLength++;
       
    	return uiLength;
 	}

 	char *ms_copy(char dest[], const char src[])
 	{
		size_t j = 0;
		assert(dest);
		assert(src);
	
		while(src[j] != '\0')
		{
			dest[j] = src[j];
			j++;
		}
	
		dest[j] = '\0';
		return dest;
 	}

 	char *ms_ncopy(char dest[], const char src[], size_t n)
 	{
 		size_t j = 0;
 		assert(dest && src);
 	
 		while(j != n)
 		{
 			if(src[j] != '\0')
 				dest[j] = src[j];
				
 			else
			{
 				dest[j] = '\0';
				break;
			}
 			
			j++;
 		}
 	
 		return dest;
 	}

 	char *ms_concat(char dest[], const char src[])
 	{
		size_t j = 0, l = ms_length(dest);
		assert(dest && src);
	
		while(j != ms_length(src))
		{
			dest[l] = src[j];
			l++;
			j++;
		}
		
		dest[l] = '\0';
		return dest;
	 }
 
	char *ms_nconcat(char dest[], const char src[], size_t n)
 	{
		size_t j = 0, l = ms_length(dest);
		assert(dest && src);
	
		while(j != ms_length(src) && j != n)
		{
			if(src[j] != '\0')
 				dest[l] = src[j];
				
 			else
 				dest[l] = '\0';
 			
			l++;
			j++;
		}
		
		dest[l] = '\0';
		return dest;
 	}

 	int ms_compare(const char s1[], const char s2[])
 	{
		size_t j = 0;
		assert(s1 != NULL && s2 != NULL);
	
    	while(s1[j] == s2[j])
    	{
        	if(j == ms_length(s1) && j == ms_length(s2)) 
				return 0;
			j++;	
		}
        
    	return ((s1[j] < s2[j]) ? -1 : +1);
 	}

 	int ms_ncompare(const char s1[], const char s2[], size_t n)
 	{
		size_t j = 0;
		assert(n >= 0); /* n != 0*/
		assert(s1 != NULL && s2 != NULL);
			
		if(n ==0) {
			return 0;
		}
		
		while(s1[j] == s2[j] && j!=n)
		{
			if(j == ms_length(s1) || j == ms_length(s2) || j == n-1)
				return 0;
			
			j++;
		}
		
		return ((s1[j] < s2[j]) ? -1 : +1);
 	}
 
 	char *ms_search(const char str1[], const char str2[])
 	{
		size_t j, l, pos;
		assert(str1 && str2);
	
		for(l = 0; l < ms_length(str1); l++)
		{
		 	if(str1[l] == str2[0])
		 	{
		 		pos = l;
		 		for(j = 0; j < ms_length(str2); j++, pos++)
		 		{
		 			if(str1[pos] != str2[j])
		 				break;
				}
				if(j == ms_length(str2)) 
					return(char *) &(str1[l]);
		 	}
		}
		return NULL;
 	}

	int main(void)
	{
		//char str1[100] = "Sire, command as";
		//char str[100];

		//printf("%d\n", ms_length("Hello World") );

		//printf("%s\n", ms_copy(str,"Hello World") );
		//printf("%s\n", ms_ncopy(str1,"Hello World", 5) );

		//printf("%s\n", ms_concat(str1,",Spears ready") );
		//printf("%s\n", ms_nconcat(str1,",Spears ready", 7) );

		//printf("%d\n", ms_compare("hello", "hello"));
		//printf("%d\n", ms_ncompare("hello", "hella", 2) );

		//printf("%s\n", ms_search(str1, "re") );

		return 0;
	}
