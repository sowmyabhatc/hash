#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "hash.h"



HashTable  hashtable_new(uint32_t size){
HashTable ht;
ht.tableSize=size;
ht.tableAddress=(Node**)malloc(sizeof(Node*)*size); //(Node**)malloc(sizeof(Node*) creates memory to store only one value by multiplying the term with size we can store all the values


for(int i=0;i<ht.tableSize;++i){
   ht.tableAddress[i]=NULL;  //initialize the all slots of array to NULL value.
}
return ht;

}

static int32_t _hash_(char *data){
int32_t hashcode=0;
while(*data!='\0'){
    hashcode=(hashcode<<5)+ *data++;

}
return hashcode;
}

static uint32_t  _compression_(int32_t hashcode,uint32_t tableSize){
return (hashcode % tableSize);
}


static uint32_t _hashing_(char *data,uint32_t tableSize){
int32_t hashcode=_hash_(data);
uint32_t index=_compression_(hashcode,tableSize);

return index;
}


uint32_t  hashtable_lookup(HashTable *ht,char *data){
assert(ht!=NULL);
Node *nodeAdd=ht->tableAddress[_hashing_(data,ht->tableSize)]; //_hashing_(data,ht->tableSize) contains integer index
//ht->tableAddress[_hashing_(data,ht->tableSize)] contains starting address of the linked list.
while(nodeAdd!=NULL){
    if(!strcmp(nodeAdd->name,data)){
        break;
   }else{
       nodeAdd=nodeAdd->next;
   }
}
return (nodeAdd!=NULL);
}

HashTable* hashtable_addElement(HashTable *ht,char *data){
assert(ht!=NULL);
if(!hashtable_lookup(ht,data)){
   uint32_t bucket=_hashing_(data,ht->tableSize); //
   Node *oldAdd=ht->tableAddress[bucket];
   ht->tableAddress[bucket]=(Node*)malloc (sizeof(Node));
   strcpy(ht->tableAddress[bucket]->name,data);
   ht->tableAddress[bucket]->next=oldAdd;
}
return ht;
}


HashTable* hashtable_delElement(HashTable *ht,char *data){
assert(ht!=NULL);
Node *node=ht->tableAddress[_hashing_(data,ht->tableSize)];   //has the address of the node to be deleted
Node *temp, *prev = NULL;
if(node->next==NULL){
temp=node;
ht->tableAddress[_hashing_(data,ht->tableSize)]=NULL;
}
while(node!=NULL){
    if(!strcmp(node->name,data)){
        if(ht->tableAddress[_hashing_(data,ht->tableSize)]==node){
            temp=node;
            ht->tableAddress[_hashing_(data,ht->tableSize)]=node->next;
        }
    else{
        prev->next=node->next;
        temp=node;
    }
    break;
}
else{
  prev=node;
  node=node->next;
}
}
free(temp);
return ht;
}




//prime number generation
//delete ele
//assert if list is NULL
//check if its first Node or middle Node if first update hashbucket value else no
