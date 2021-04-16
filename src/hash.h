#ifndef HASH_H
#define HASH_H

struct DATAITEM
{
   int data;
   int key;
};

struct DATAITEM *inithash(struct DATAITEM *item);
struct DATAITEM *initdummy(void);
int hashcode(int key);
struct DATAITEM *search(int key);
void insert(int key, int data, struct DATAITEM *item);
struct DATAITEM *delete(struct DATAITEM *item, struct DATAITEM *dummyitem);

#endif
