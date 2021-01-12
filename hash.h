#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED
#include "appconst.h"
#include <stdint.h>


typedef struct _node_ Node;
struct _node_{
char name[DATA_LEN];
Node *next;
};


typedef struct _hash_table_ HashTable;
struct _hash_table_{
uint32_t tableSize;
Node **tableAddress; //index of the data stored is a ouble pointer
};


HashTable  hashtable_new(uint32_t size);
uint32_t   hashtable_lookup(HashTable *ht,char *data);
HashTable* hashtable_addElement(HashTable *ht,char *data);
HashTable* hashtable_delElement(HashTable *ht,char *data);
//int32_t    prime(int32_t n);


#endif // HASH_H_INCLUDED
