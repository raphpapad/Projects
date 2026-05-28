#include "symtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct symtable /* struct symtable binding */
{
    char *key;
    void *value;
    struct symtable *next;
};

SymTable_T SymTable_new(void) /* ftiaxnei kai epistrefei ena adeio SymTable_T */
{
	int tebugcounter0 = 0; /* gia tebug */
	
    SymTable_T new;
    new=malloc(sizeof(struct symtable));
    if (!new)
    {
    	tebugcounter0++;
        fprintf(stderr,"ERROR: Could not allocate new node\n");
        exit(EXIT_FAILURE);
    }
    new->next=NULL;
    new->key="DUMMY";
    new->value=NULL;
    
    return new;
}

void SymTable_free(SymTable_T oSymTable) /* eleutherwnetai h mnimi (an den einai NULL) */
{
	int tebugcounter1 = 0; /* gia tebug */
	
    SymTable_T p=oSymTable,temp;
    
    if (oSymTable == NULL)
        return;
    p=p->next;
    
    while (p)
    {
    	tebugcounter1++;
        temp=p->next;
        free(p->key);
        free(p);
        p=temp;
    }
    free (oSymTable); /* segmentation if user continue uses sumboltable */
}

unsigned int SymTable_getLength(SymTable_T oSymTable) /* upologizei kai epistrefei twn arithmo twn bindings pou exei o oSymtable */
{
    unsigned int metritis;
    SymTable_T p;
    assert(oSymTable);
    p= oSymTable;
    
    metritis = 0;
    for (; p ; p = p -> next) /* p ; = p!=NULL */
    {
    	metritis++;
	}
    return metritis-1;
}

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue) /* binding(pcKey,pvValue) sto oSymTable an den uparxei */
{
    int tebugcounter5 = 0; /* gia tebug */
    
    SymTable_T prev,new;
    assert(oSymTable);
    assert(pcKey);
    
    if ( SymTable_contains(oSymTable,pcKey) )
        return 0;
    prev = oSymTable;
    tebugcounter5++;
    
    while (prev -> next)
        prev = prev -> next;
    
    new=malloc(sizeof(struct symtable));
    prev -> next = new;
    new -> next = NULL;
    new -> key = malloc( (strlen(pcKey)+1) * sizeof(char) );
    strcpy(new -> key,pcKey);
    new -> value = (void *)pvValue;
    return 1;
}

int SymTable_remove(SymTable_T oSymTable, const char *pcKey) /* diwxnei to binding me id pcKey an uparxei ston oSymtable */
{
	int tebugcounter2 = 0; /* gia tebug */
	
    SymTable_T p,prev;
    assert(oSymTable); /* runtime error gia to oSymatable an einai NULL = assert */
    assert(pcKey);
    p = oSymTable;
    prev = NULL;
    
    while (p && (strcmp(p -> key, pcKey) != 0) )
    {
        prev = p;
        p = p -> next;
    }
    if (p == NULL)
        return 0; 
    else if (prev == NULL) /* 1st node deletion */
    {
        p = oSymTable -> next;
        free(oSymTable -> key);
        free(oSymTable);
        oSymTable = p;
        tebugcounter2++;
        return 1;
    }
    else /* node between 2nd and last */
    	prev->next=p->next;
    free(p->key);
    free(p);
    tebugcounter2--;
    return 1;
}

SymTable_T Symtable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue)
{
    return oSymTable;    
}

int SymTable_contains(SymTable_T oSymTable, const char *pcKey) /* psaxnei an ta bindings me id pcKey uparxoyn */
{
    SymTable_T p;
    assert(oSymTable);
    assert(pcKey);
    p=oSymTable;
    
    while (p && (strcmp(p->key,pcKey)!=0) )
        p=p->next;
    if (!p)
        return 0;
    else
        return 1;
}

void *SymTable_get(SymTable_T oSymTable, const char *pcKey) /* epistrefei tin timi tou binding me to pckey or NULL an to pckey den uparxei */
{
    SymTable_T p;
    assert(oSymTable);
    assert(pcKey);
    p=oSymTable;
    
    while (p && (strcmp(p->key,pcKey)!=0) )
        p=p->next;
    if (!p)
        return NULL;
    else
        return p->value;
}

void SymTable_map(SymTable_T oSymTable,void (*pfApply)(const char *pcKey,void *pvValue,     /*  SymTable_map = efarmozei to pfApply se kathe binding tou oSymtable */
void *pvExtra),const void *pvExtra)
{
	int tebugcounter3 = 0; /* gia tebug */
	
    SymTable_T p;
    assert(oSymTable);
    assert(pfApply);
    p=oSymTable;
    while (p) 
    {
    	tebugcounter3++;
        if (p->value)
            pfApply(p->key, &(p->value), (void *)pvExtra);
        p=p->next;
    }
}

void print(SymTable_T oSymTable) /* print fuction = SymbolTble keys */
{
	int tebugcounter4 = 0; /* gia tebug */
	
    SymTable_T p;
    assert(oSymTable);
    p=oSymTable;
    if (SymTable_getLength(p)==0)
    {
        printf("EMPTY SYMTABLE\n");
        return;
    }
    p=p->next;
    while(p != NULL && p->key!=NULL)
    {
    	tebugcounter4++;
        printf("%s->",p->key);
        p=p->next;
    }
    tebugcounter4--;
    printf("\n");
}
