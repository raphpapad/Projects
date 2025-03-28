/*

Name and Surname: Raphael Papadakis 
AM: 4325 (csd)
Exercise: assignment 3

*/

#ifndef SYM
#define SYM

typedef struct symtable * SymTable_T;

SymTable_T SymTable_new(void);

void SymTable_free(SymTable_T oSymTable);

unsigned int SymTable_getLength(SymTable_T oSymTable);

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue);

int SymTable_remove(SymTable_T oSymTable, const char *pcKey);

int SymTable_contains(SymTable_T oSymTable, const char *pcKey);
SymTable_T Symtable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue);

void *SymTable_get(SymTable_T oSymTable, const char *pcKey);

void SymTable_map(SymTable_T oSymTable,void (*pfApply)(const char *pcKey,void *pvValue,\
void *pvExtra),const void *pvExtra);

void print(SymTable_T oSymTable);

#endif
