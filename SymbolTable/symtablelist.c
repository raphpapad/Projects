#include "symtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/* Struct symtable binding */
struct symtable
{
    char *key;
    void *value;
    struct symtable *next;
};

/* Creates and returns an empty SymTable_T */
SymTable_T SymTable_new(void)
{
    SymTable_T new;
    new=malloc(sizeof(struct symtable));
    if (!new)
    {
        fprintf(stderr,"ERROR: Could not allocate new node\n");
        exit(EXIT_FAILURE);
    }
    new->next=NULL;
    new->key="DUMMY";
    new->value=NULL;
    
    return new;
}

/* It mallocs memory (if it's not NULL) */
void SymTable_free(SymTable_T oSymTable)
{
    SymTable_T p=oSymTable,temp;
    
    if (oSymTable == NULL)
        return;
    p=p->next;
    
    while (p)
    {
        temp=p->next;
        free(p->key);
        free(p);
        p=temp;
    }
	/* Segmentation if user continue uses sumboltable */
    free (oSymTable); 
}

/* Calculates and returns the number of bindings that oSymtable has */
unsigned int SymTable_getLength(SymTable_T oSymTable)
{
    unsigned int metritis;
    SymTable_T p;
    assert(oSymTable);
    p= oSymTable;
    
    metritis = 0;
	/* p ; = p!=NULL */
    for (; p ; p = p -> next) 
    {
    	metritis++;
	}
    return metritis-1;
}

/* Binding(pcKey,pvValue) at oSymTable if doesn't exist */
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue)
{    
    SymTable_T prev,new;
    assert(oSymTable);
    assert(pcKey);
    
    if ( SymTable_contains(oSymTable,pcKey) )
        return 0;
    prev = oSymTable;
    
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

/* Removes the binding with id pcKey if exists at oSymtable */
int SymTable_remove(SymTable_T oSymTable, const char *pcKey)
{
    SymTable_T p,prev;
	/* Runtime error for oSymatable if NULL = assert */
    assert(oSymTable); 
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
	/* 1st node deletion */
    else if (prev == NULL)
    {
        p = oSymTable -> next;
        free(oSymTable -> key);
        free(oSymTable);
        oSymTable = p;
        return 1;
    }
	/* Node between 2nd and last */
    else 
    	prev->next=p->next;
    free(p->key);
    free(p);
    return 1;
}

SymTable_T Symtable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue)
{
    return oSymTable;    
}

/* Searches if the bindings with id pcKey exist */
int SymTable_contains(SymTable_T oSymTable, const char *pcKey)
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

/* Returns the value of binding with the pckey or NULL if the pckey doesn't exist */
void *SymTable_get(SymTable_T oSymTable, const char *pcKey)
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

/*  SymTable_map = applies to pfApply at every binding of oSymtable */
void SymTable_map(SymTable_T oSymTable,void (*pfApply)(const char *pcKey,void *pvValue, void *pvExtra),const void *pvExtra)
{
    SymTable_T p;
    assert(oSymTable);
    assert(pfApply);
    p=oSymTable;
    while (p) 
    {
        if (p->value)
            pfApply(p->key, &(p->value), (void *)pvExtra);
        p=p->next;
    }
}

/* print fuction = SymbolTble keys */
void print(SymTable_T oSymTable)
{
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
        printf("%s->",p->key);
        p=p->next;
    }
    printf("\n");
}
