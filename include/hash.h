/* hash.h */

#include "list.h"
#include "type.h"

#ifndef _MIB2DOC_HASHMAP_H_
#define _MIB2DOC_HASHMAP_H_

/* Defines */

// hashElem
#define HASH_ELEM_USED (1)
#define HASH_ELEM_NOT_USED (0)
#define HASH_ELEM_IS_USED(ELEM) (ELEM->used == HASH_ELEM_USED)
#define HASH_ELEM_COLLIDE (1)
#define HASH_ELEM_NOT_COLLIDE (0)
#define HASH_ELEM_IS_COLLIDE(ELEM) (ELEM->collide == HASH_ELEM_COLLIDE)
#define HASH_ELEM_CHAIN_REF(ELEM) (&(ELEM->chain))

// hashChain
#define HASH_CHAIN_NODE_R(CHAIN) (&CHAIN->node)
#define HASH_CHAIN_IS_LAST(C) (C->node.next == NULL)
#define HASH_CHAIN_PAIR_R(CHAIN) (&CHAIN->pair)

// Pair
#define PAIR_KEY_R(P) (P->key)
#define PAIR_VAL_R(P) (P->val)

#define PAIR_KEY(P) (P.key)
#define PAIR_VAL(P) (P.val)

#define PAIR_KEY_SET(P, K) (P.key = K)
#define PAIR_VAL_SET(P, V) (P.val = V)

// hashMap
#define HASH_MAP_ELEM_SELECT(MAP, IDX) (MAP->space + IDX)
#define HASH_MAP_HASH_COMPUTING(MAP, KEY) \
    (MAP->hashFunc(KEY) % MAP->size)
#define HASH_MAP_HASH_GET(MAP, KEY) \
    (HASH_MAP_ELEM_SELECT(MAP, HASH_MAP_HASH_COMPUTING(MAP, KEY)))

// Hash method
#define HASH_DEFAULT_METHOD(V) ((V << 5) + V)

typedef int (*hashFunction)(void *);

struct pair_key_base;

typedef int (*pairKeyRelease)(struct pair_key_base *);
typedef void * (*pairKeyValue)(struct pair_key_base *);
typedef int (*pairKeyIsEqual)(struct pair_key_base *, struct pair_key_base *);
typedef struct pair_key_base * (*pairKeyCopy)(struct pair_key_base *);

typedef struct pair_key_base {
    pairKeyRelease release;
    pairKeyValue value;
    pairKeyIsEqual isEqual;
    pairKeyCopy copy;
} pair_key_base;

struct pair_val_base;

typedef int (*pairValRelease)(struct pair_val_base *);
typedef void * (*pairValValue)(struct pair_val_base *);
typedef int (*pairValIsEqual)(struct pair_val_base *, struct pair_val_base *);
typedef struct pair_val_base * (*pairValCopy)(struct pair_val_base *);

typedef struct pair_val_base {
    pairValRelease release;
    pairValValue value;
    pairValIsEqual isEqual;
    pairValCopy copy;
} pair_val_base;

#if 0
typedef struct {
    pair_key_base *key;
    pair_val_base *val;
} pair_kv;
#endif

typedef struct {
    pair_key_base *key;
    pair_val_base *val;
    listNode node;
} hashChain;

typedef struct {
    int used;
    int collide;
    pair_key_base *key;
    pair_val_base *val;
    hashChain chain;
} hashElem;

typedef struct {
    int size;
    hashFunction hashFunc;
    hashElem *space;
} hashMap;

/* Function declarations */
hashMap * hashMapInit(hashMap *map, int size, hashFunction func);
hashMap * hashMapConstruct(int size, hashFunction func);
hashMap * hashMapDup(hashMap *origin);
int hashMapRelease(hashMap *map);
void * hashMapGet(hashMap *map, pair_key_base *key);
int hashMapPut(hashMap *map, pair_key_base *key, pair_val_base *val);
int hashMapDelete(hashMap *map, pair_key_base *key);

#ifdef MIB2DOC_UNIT_TESTING

void hash__HASH_BASIC(void **state);

#endif /* MIB2DOC_UNIT_TESTING */

#endif /* _MIB2DOC_HASHMAP_H_ */
