#include "symtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


struct symtable  /* struct symtable binding */
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
	int tebugcounter0 = 0;  /* gia tebug */
    size_t ui = 0U;
    unsigned int uiHash = 0U;
    
    while (pcKey[ui] != '\0')
	{
		tebugcounter0++;
        uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui];
        ui++;
  	}
    return uiHash % epipedo;
}

SymTable_T SymTable_new(void) /* ftiaxnei kai epistrefei ena adeio SymTable_T */
{
	int tebugcounter1 = 0;  /* gia tebug */
    SymTable_T HT;
    int j = 0;
    HT = malloc(sizeof(struct symtable)*epipedo);
    
    while (j < epipedo) 
    {
    	tebugcounter1++;
        HT[j].key="DUMMY";
		HT[j].value=NULL;
		HT[j].next=NULL;
		j++;
    }
    tebugcounter1--;
    bindings = 0;
    epipedo = epipedo1;
    metritis = 0;
    return HT;
}

void SymTable_free(SymTable_T oSymTable) /* eleutherwnetai h mnimi (an den einai NULL) */
{
	int tebugcounter2 = 0;  /* gia tebug */
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
        	tebugcounter2++;
            temp=p -> next;
            p -> value = NULL;
            p -> next=NULL;
            free(p -> key);
            free(p);
            p=temp;
        } 
        j++;
    }
    tebugcounter2--;
    epipedo = epipedo1;
    metritis = 0;
    bindings = 0;
    free(oSymTable);
}

unsigned int SymTable_getLength(SymTable_T oSymTable) /* upologizei kai epistrefei ton arithmo twn bindings pou exei o oSymtable */
{
    assert(oSymTable); /* runtime error = assert */
    return bindings;
}


static SymTable_T SymTable_Expand(SymTable_T oldsymtable)
{
	int tebugcounter3 = 0;
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
    	tebugcounter3++;
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
    tebugcounter3--;
    
    epipedo = old_buckets;
    SymTable_free(oldsymtable);
    epipedo = temp_epipedo;
    metritis = temp_metritis;
    bindings = temp_bindings;
    return newsymtable;
}
 
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue) /* binding(pcKey,pvValue) sto oSymTable an den uparxei */
{
	int tebugcounter4 = 0; /* gia debug */
	
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
    tebugcounter4++;
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

int SymTable_remove(SymTable_T oSymTable, const char *pcKey) /* diwxnei to binding me id pcKey an uparxei ston oSymtable */
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
    else if (prev==NULL) /* 1st node deletion */
        oSymTable[index].next=p->next;
    else /* node between 2nd and last */
        prev->next=p->next;
        
    free(p->key);
    free(p);
    bindings--;
    return 1;   
}

int SymTable_contains(SymTable_T oSymTable, const char *pcKey) /* psaxnei an ta bindings me id pcKey uparxoyn */
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

void *SymTable_get(SymTable_T oSymTable, const char *pcKey)  /* epistrefei tin timi tou binding me to pckey or NULL an to pckey den uparxei */
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

void SymTable_map(SymTable_T oSymTable,void (*pfApply)(const char *pcKey,void *pvValue, void *pvExtra),const void *pvExtra)  /*  SymTable_map = efarmozei to pfApply se kathe binding tou oSymtable */
{
	int tebugcounter5 = 0; /* gia debug */
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
        tebugcounter5++;
        j++;
    }
    tebugcounter5--;
}

void print(SymTable_T oSymTable) /* print fuction = SymbolTble keys */
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
