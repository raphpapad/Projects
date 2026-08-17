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

enum hash{epipedo1 = 509, epipedo2 = 1021, epipedo3 = 2053, epipedo4 = 4093, epipedo5 = 8191, epipedo6 = 16381, epipedo7 = 32771, epipedo8 = 65521, HASH_MULTIPLIER = 65599};
static int epipeda[8] = {epipedo1, epipedo2, epipedo3, epipedo4, epipedo5, epipedo6, epipedo7, epipedo8};
static int metritis = 0;
static int bindings = 0;
static int epipedo = epipedo1;


static unsigned int SymTable_hash(const char *pcKey)
{
    size_t ui = 0U;
    unsigned int uiHash = 0U;
    
    while (pcKey[ui] != '\0')
	{
        uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui];
        ui++;
  	}
    return uiHash % epipedo;
}

/* Creates and returns an empty SymTable_T */
SymTable_T SymTable_new(void)
{
    SymTable_T HT;
    int j = 0;
    HT = malloc(sizeof(struct symtable)*epipedo);
    
    while (j < epipedo) 
    {
        HT[j].key="DUMMY";
		HT[j].value=NULL;
		HT[j].next=NULL;
		j++;
    }
    bindings = 0;
    epipedo = epipedo1;
    metritis = 0;
    return HT;
}

/* Mallocs memory (if it's not NULL) */
void SymTable_free(SymTable_T oSymTable) 
{
    int j = 0;
    SymTable_T temp, p;
    
    if (!oSymTable)
        return;
        
    while (j < epipedo)
    {
        p = oSymTable[j].next;
        oSymTable[j].next=NULL;
        oSymTable[j].key=NULL;
        oSymTable[j].value=NULL;
        
        while (p)
        {
            temp=p -> next;
            p -> value = NULL;
            p -> next=NULL;
            free(p -> key);
            free(p);
            p=temp;
        } 
        j++;
    }
    epipedo = epipedo1;
    metritis = 0;
    bindings = 0;
    free(oSymTable);
}

/* Calculates and returns the number of bindings that oSymtable has */
unsigned int SymTable_getLength(SymTable_T oSymTable) 
{
	/* runtime error = assert */
    assert(oSymTable);
    return bindings;
}


static SymTable_T SymTable_Expand(SymTable_T oldsymtable)
{
    SymTable_T newsymtable,p,prev,new;
    int index, temp_epipedo, temp_metritis, temp_bindings, old_buckets;
    int j = 0;
    assert(oldsymtable);
    
    temp_epipedo = epipedo;
    temp_metritis = metritis;
    temp_bindings = bindings;
    old_buckets = epipeda[metritis-1];
    newsymtable = SymTable_new();
    assert(newsymtable);
    epipedo = temp_epipedo;
    metritis = temp_metritis;
    
    printf("===============================\n");
    printf("check old buckets %d \n",old_buckets);
    printf("check new epipedo   %d \n",temp_metritis);
    printf("check new buckets %d \n",temp_epipedo);
    printf("===============================\n");
    
    while (j < old_buckets) 
    {
        p=oldsymtable[j].next;
        
        while (p)
        {
            index = SymTable_hash(p -> key);
            prev = newsymtable[index].next;
            if (!prev)
            {
                prev = malloc(sizeof(struct symtable));
                prev -> next = NULL;
                prev -> key = malloc( (strlen(p -> key)+1) * sizeof(char) );
                strcpy(prev -> key, p -> key);
                prev -> value = (void *)p->value;
                newsymtable[index].next = prev;
                p = p -> next;
                bindings++;
                continue;
            }
            while (prev->next)
                prev=prev->next;
                
            new = malloc(sizeof(struct symtable));
            new -> next = NULL;
            new -> key = malloc( (strlen(p -> key)+1) * sizeof(char) );
            strcpy(new -> key, p -> key);
            new -> value = (void *)p -> value;
            prev -> next = new;
            bindings++;
            p = p -> next;
        }
        j++;
    }
    
    epipedo = old_buckets;
    SymTable_free(oldsymtable);
    epipedo = temp_epipedo;
    metritis = temp_metritis;
    bindings = temp_bindings;
	
    return newsymtable;
}

/* binding(pcKey,pvValue) at oSymTable if doesn't exist*/
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue) 
{
    SymTable_T new,prev;
    int index;
    assert(oSymTable);
    assert(pcKey);
    
    index=SymTable_hash(pcKey);
    prev=oSymTable[index].next;
    
    if ( SymTable_contains(oSymTable,pcKey) )
        return 0;
        
    if (!prev)
    {
        new=malloc(sizeof(struct symtable));
        new->next=NULL;
        new->key=malloc( (strlen(pcKey)+1) * sizeof(char) );
        strcpy(new->key,pcKey);
        new->value=(void *)pvValue;
        prev=new;
        oSymTable[index].next=prev;
        bindings++;
        return 1;
    }
    
    while (prev->next)
        prev=prev->next;
        
    new=malloc(sizeof(struct symtable));
    prev->next=new;
    new->next=NULL;
    new->key=malloc( (strlen(pcKey)+1) * sizeof(char) );
    strcpy(new->key,pcKey);
    new->value=(void *)pvValue;
    bindings++;
	
    return 1;
}


SymTable_T Symtable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue)
{
    SymTable_T new,prev;
    int index;
    assert (oSymTable);
    assert(pcKey);
    
    index=SymTable_hash(pcKey);
    prev=oSymTable[index].next;
    
    if ( SymTable_contains(oSymTable,pcKey) )
        return oSymTable; 
        
    if (bindings == epipedo && metritis < 7)
    {
        printf("\nReady   to Expand from level %d to level %d \n",metritis,metritis+1);
        printf("level   before expand %d \n",metritis);
        printf("Buckets before expand %d \n",epipedo);
        metritis++;
        epipedo=epipeda[metritis];
        oSymTable=SymTable_Expand(oSymTable);
        index=SymTable_hash(pcKey);
        prev=oSymTable[index].next;
    }
    
    if (!prev)
    {
        new=malloc(sizeof(struct symtable));
        new->next=NULL;
        new->key=malloc( (strlen(pcKey)+1) * sizeof(char) );
        strcpy(new->key,pcKey);
        new->value=(void *)pvValue;
        prev=new;
        oSymTable[index].next=new;
        bindings++;
        return oSymTable;
    }
    while (prev->next)
        prev=prev->next;
        
    new=malloc(sizeof(struct symtable));
    new->next=NULL;
    new->key=malloc( (strlen(pcKey)+1) );
    strcpy(new->key,pcKey);
    new->value=(void *)pvValue;
    prev->next=new;
    bindings++;
	
    return oSymTable;
}

/* Removes the binding with id pcKey if exists on oSymtable */
int SymTable_remove(SymTable_T oSymTable, const char *pcKey) 
{
    SymTable_T p,prev;
    int index;
    assert(oSymTable);
    assert(pcKey);
    
    index=SymTable_hash(pcKey);
    p=oSymTable[index].next;
    prev=NULL;
    
    while (p && (strcmp(p->key,pcKey)!=0) )
    {
        prev=p;
        p=p->next;
    }
    
    if (p==NULL)
        return 0; 
	/* 1st node deletion */
    else if (prev==NULL) 
        oSymTable[index].next=p->next;
	/* node between 2nd and last */
    else
        prev->next=p->next;
        
    free(p->key);
    free(p);
    bindings--;
    return 1;   
}

/* Searches if the bindings with id pcKey exist */
int SymTable_contains(SymTable_T oSymTable, const char *pcKey)
{
    SymTable_T p;
    int index;
    assert(oSymTable);
    assert(pcKey);
    
    index=SymTable_hash(pcKey);
    p=oSymTable[index].next;
    
    while ( p && (strcmp(p->key,pcKey)!=0) )
        p=p->next;
        
    if (!p)
        return 0;
    else
        return 1;
}

/* Returns the value of binding with pckey or NULL if pckey doesn't exist */
void *SymTable_get(SymTable_T oSymTable, const char *pcKey)  
{
    SymTable_T p;
    int index;
    assert(oSymTable);
    assert(pcKey);
    
    index=SymTable_hash(pcKey);
    p=oSymTable[index].next;
    
    while (p && (strcmp(p->key,pcKey)!=0) )
        p=p->next;
        
    if (!p)
        return NULL;
    else
        return p->value;
}

/* SymTable_map = applies on pfApply at every binding of oSymtable */
void SymTable_map(SymTable_T oSymTable,void (*pfApply)(const char *pcKey,void *pvValue, void *pvExtra),const void *pvExtra)  
{
    SymTable_T p;
    int j = 0;
    assert(oSymTable);
    assert(pfApply);
    
    while (j < epipedo)
    {
        p=oSymTable[j].next;
        
        while (p) 
        {
            if (p->value)
                pfApply(p->key, p->value, (void *)pvExtra); 
            p=p->next;
        }
        j++;
    }
}

/* Print fuction = SymbolTble keys */
void print(SymTable_T oSymTable)
{
	int tebugcounter6 = 0;
    SymTable_T p;
    int j = 0;
    assert(oSymTable);
    
    while (j < epipedo)
    {
        p=oSymTable[j].next;
        if (p)
        {
            while(p && p->key)
            {
                printf("%s->",p->key);
                p=p->next;
            }
            printf("\n");
        }
        tebugcounter6++;
        j++;
    }
}    
