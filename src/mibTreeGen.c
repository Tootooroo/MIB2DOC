//
// Created by ayden on 2017/4/19.
//

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "mibTreeGen.h"
#include "type.h"
#include "list.h"
#include "queue.h"
#include "dispatcher.h"
#include "symbolTbl.h"

/* Declaration */
static int mibTreeLeaveAdd(mibObjectTreeNode *trap, char *parent);
static int mibTreeNodeAdd(mibObjectTreeNode *node, char *parent);
static char * oidComplement(char *parent, char *suffix);

char currentTable[64];
extern mibObjectTreeNode root;
extern slice sliceContainer;
extern mibObjectTreeNode mibObjectTreeRoot;

/* Global */
mibObjectTreeNode root;
mibTreeHead trees;
symbolTable symTable;
slice symCollectSlice;
targetSymbolList tSymListHead;

int mibObjGen(int nodeType) {
    mibObjectTreeNode *newNode;
    char *ident, *type, *rw, *desc, *parent, *suffix, *oid;    
    
    ident = sliceGetVal(&sliceContainer, SLICE_IDENTIFIER);;
    type = sliceGetVal(&sliceContainer, SLICE_TYPE); 
    rw = sliceGetVal(&sliceContainer, SLICE_PERMISSION);
    desc = sliceGetVal(&sliceContainer, SLICE_DESCRIPTION);
    parent = sliceGetVal(&sliceContainer, SLICE_PARENT); 
    suffix = sliceGetVal(&sliceContainer, SLICE_OID_SUFFIX);

    // Node Build
    switch (nodeType) {
        case OBJECT:
            assert(ident != NULL);
            assert(type != NULL);
            assert(rw != NULL);
            assert(desc != NULL);
            assert(parent != NULL);
            assert(suffix != NULL);
            
            oid = oidComplement(parent, suffix);
            newNode = mibLeaveBuild(ident, type, rw, desc, oid);
            break;
        case TRAP:
            type = (char *)malloc(strlen("trap") + 1);
            strncpy(type, "trap", strlen("trap"));

            assert(ident != NULL); 
            assert(parent != NULL); 
            assert(suffix != NULL);
            assert(desc != NULL);
            
            oid = oidComplement(parent, suffix);
            newNode = mibLeaveBuild(ident, type, NULL, NULL, oid); 
            break;
        case OBJECT_IDENTIFIER:
            assert(ident != NULL);
            assert(parent != NULL);
            assert(suffix != NULL);

            oid = oidComplement(parent, suffix);
            newNode = mibNodeBuild(ident, oid);
            break;
        case SEQUENCE:
            /* ignore */
            break;
        default:
            break;
    }

    assert(mibTreeHeadAppend(&trees, newNode, parent) != FALSE);

    return 0;
}

int mibObjGen_Leave() {
    mibObjectTreeNode *obj;
    char *ident, *type, *rw, *desc, *parent, *suffix, *oid;
    
    assert((ident = sliceGetVal(&sliceContainer, SLICE_IDENTIFIER)) != NULL);
    assert((type = sliceGetVal(&sliceContainer, SLICE_TYPE)) != NULL);
    assert((rw = sliceGetVal(&sliceContainer, SLICE_PERMISSION)) != NULL);
    assert((desc = sliceGetVal(&sliceContainer, SLICE_DESCRIPTION)) != NULL);
    assert((parent = sliceGetVal(&sliceContainer, SLICE_PARENT)) != NULL);
    assert((suffix = sliceGetVal(&sliceContainer, SLICE_OID_SUFFIX)) != NULL);

    oid = oidComplement(parent, suffix);
    obj = mibLeaveBuild(ident, type, rw, desc, oid);
    mibTreeLeaveAdd(obj, parent);

    sliceReset(sliceNext(&sliceContainer));
    RELEASE_MEM(suffix);
    RELEASE_MEM(parent);
    return 0;
}

int mibObjGen_InnerNode() {
    mibObjectTreeNode *node;
    char *ident, *parent, *suffix, *oid;

    assert( (ident = sliceGetVal(&sliceContainer, SLICE_IDENTIFIER)) != NULL);
    assert( (parent = sliceGetVal(&sliceContainer, SLICE_PARENT)) != NULL);
    assert( (suffix = sliceGetVal(&sliceContainer, SLICE_OID_SUFFIX)) != NULL);

    oid = oidComplement(parent, suffix);

    node = mibNodeBuild(ident, oid);
    mibTreeNodeAdd(node, parent);

    sliceReset(sliceNext(&sliceContainer));

    RELEASE_MEM(suffix);
    RELEASE_MEM(parent);

    return 0;
}

int mibObjGen_trap() {
    mibObjectTreeNode *obj; 
    char *ident, *parent, *suffix, *oid, *desc, *type;

    assert( (ident = sliceGetVal(&sliceContainer, SLICE_IDENTIFIER)) != NULL);

    type = (char *)malloc(strlen("trap")+1);
    memset(type, 0, strlen("trap")+1);
    strncpy(type, "trap", strlen("trap"));

    assert( (parent = sliceGetVal(&sliceContainer, SLICE_PARENT)) != NULL);
    assert( (suffix = sliceGetVal(&sliceContainer, SLICE_OID_SUFFIX)) != NULL);
    assert( (desc = sliceGetVal(&sliceContainer, SLICE_DESCRIPTION)) != NULL);

    oid = oidComplement(parent, suffix);
    
    obj = mibLeaveBuild(ident, type, NULL, NULL, oid); 
    mibTreeLeaveAdd(obj, parent);

    sliceReset(sliceNext(&sliceContainer));

    RELEASE_MEM(desc);
    RELEASE_MEM(suffix);
    RELEASE_MEM(parent);

    return 0;
}

void deal_with_sequence() {}

static int tablePrint(char *ident, char *oid, char *rw, char *detail, FILE *output) {
    if (isNullPtr(ident) || isNullPtr(oid) || isNullPtr(rw) || isNullPtr(detail))
        return -1;
}

static int mibTreeLeaveAdd(mibObjectTreeNode *obj, char *parent) {
    if (isNullPtr(obj))
        return -1;
    return insert_MibTree(&mibObjectTreeRoot, obj, parent);
}

static int mibTreeNodeAdd(mibObjectTreeNode *obj, char *parent) {
    if (isNullPtr(obj))
        return -1;
    return insert_MibTree(&mibObjectTreeRoot, obj, parent);
}

static char * oidComplement(char *parent, char *suffix) {
    char *oid, *parentOid;
    int oidLength = SIZE_OF_OID_STRING;
    mibObjectTreeNode *parentNode;

    parentNode = search_MibTree(&mibObjectTreeRoot, parent);

    if (parentNode == NULL)
        return NULL;
    
    parentOid = getOidFromInfo(parentNode);

    // Overflow checking.
    if (strlen(parentOid) >= SIZE_OF_OID_STRING) {
        oidLength += EXTRA_OF_OID_LEN; 
    }

    oid = (char *)malloc(oidLength);
    memset(oid, 0, oidLength);

    strncpy(oid, parentOid, oidLength);
    strncat(oid, ".", 1);
    strncat(oid, suffix, strlen(suffix));

    return oid;
}

extern mibObjectTreeNode mibObjectTreeRoot;
int upperTreeGeneration(symbolTable *symTbl) {
    mibObjectTreeNode *root;
    mibObjectTreeNode *current;
    mibObjectTreeNode *childNode;
    symbolTable *table;
    symbol_t *sym;
    symbol_t *child;
    symbol_t *temp;
    genericStack stack;

    if (isNullPtr(symTbl)) {
        return ERROR_NULL_REF;
    }
    root = &mibObjectTreeRoot;
    insert_MibTree(root, mibNodeBuild("iso", "1"), "root");
    push(&stack, root);

    sym = (symbol_t *)malloc(sizeof(symbol_t));
    memset(sym, 0, sizeof(symbol_t));
    while (stack.top > 0) {
        pop(&stack, current);
        if (symbolSearchingByParent(&symTable, current->identifier, sym)) {
            child = containerOf(sym->symNode.next, symbol_t, symNode);
            while (child != NULL) {
                if (child->symType == SYMBOL_TYPE_NODE) {
                    childNode = mibNodeBuild(strdup(child->symIdent),
                        strdup(child->symInfo.nodeMeta.suffix));
                    insert_MibTree(root, childNode, strdup(current->identifier));
                    push(&stack, childNode);
                } else if (child->symType == SYMBOL_TYPE_LEAVE) {
                    childNode = mibLeaveBuild(strdup(child->symIdent),
                        strdup(child->symInfo.leaveMeta.type),
                        strdup(child->symInfo.leaveMeta.permission),
                        NULL,
                        strdup(child->symInfo.leaveMeta.suffix));
                    insert_MibTree(root, childNode, strdup(current->identifier));
                }
                temp = child;
                child = containerOf(&child->symNode, symbol_t, symNode);

                RELEASE_MEM(temp->symIdent);
                RELEASE_MEM(temp);
            }
        }
    }
}

/*
 * Symbol Collecting
 */
static int symbolCollect_BUILD_INNER_NODE(dispatchParam *param);
static int symbolCollect_PARAM_DESC(dispatchParam *param);
static int symbolCollect_PARAM_IDENT(dispatchParam *param);
static int symbolCollect_BUILD_LEAVE_NODE(dispatchParam *param);
static int symbolCollect_PARAM_PARENT(dispatchParam *param);
static int symbolCollect_PARAM_PERM(dispatchParam *param);
static int symbolCollect_BUILD_SEQUENCE(dispatchParam *param);
static int symbolCollect_BUILD_SMI_DEF(dispatchParam *param);
static int symbolCollect_PARAM_SUFFIX(dispatchParam *param);
static int symbolCollect_BUILD_TRAP(dispatchParam *param);
static int symbolCollect_PARAM_TYPE(dispatchParam *param);

int (*symbolCollectRoutine[SLICE_TYPE_MAXIMUM])(dispatchParam *);

/* Initialize symbolCollectRoutine array */
int symbolCollectingInit() {
    /* Symbol Table building function */
    symbolCollectRoutine[OBJECT] = symbolCollect_BUILD_INNER_NODE;
    symbolCollectRoutine[TRAP] = symbolCollect_BUILD_TRAP;
    symbolCollectRoutine[OBJECT_IDENTIFIER] = symbolCollect_BUILD_LEAVE_NODE;
    symbolCollectRoutine[SEQUENCE] = symbolCollect_BUILD_SEQUENCE;
    symbolCollectRoutine[SMI_DEF] = symbolCollect_BUILD_SMI_DEF;

    /* Parameter Collecting function */
    symbolCollectRoutine[SLICE_IDENTIFIER] = symbolCollect_PARAM_IDENT;
    symbolCollectRoutine[SLICE_TYPE] = symbolCollect_PARAM_TYPE;
    symbolCollectRoutine[SLICE_PERMISSION] = symbolCollect_PARAM_PERM;
    symbolCollectRoutine[SLICE_DESCRIPTION] = symbolCollect_PARAM_DESC;
    symbolCollectRoutine[SLICE_PARENT] = symbolCollect_PARAM_PARENT;
    symbolCollectRoutine[SLICE_OID_SUFFIX] = symbolCollect_PARAM_SUFFIX;

    return 0;
}

int symbolCollecting(int type, dispatchParam *param) {
    // fixme: before collecting a symbol you should 
    // check to see that whether the symbol you encounter
    // is the one you want to include
    return symbolCollectRoutine[type](param);
}

static int symbolCollect_BUILD_INNER_NODE(dispatchParam *param) {
    int retVal;
    symbolTable *newMod;
    collectInfo *pCollect;
    symbol_t *newSymbol;
    identList *listHead, *listProcessing;
    char *modIdent;
    char *symbolIdent;
    char *parentIdent ;
    
    parentIdent = sliceGetVal(&symCollectSlice, SLICE_PARENT);
    symbolIdent = sliceGetVal(&symCollectSlice, SLICE_IDENTIFIER);

    /* Is the symbol exists in symbol table ? */
    if (symbolSearching(&symTable, symbolIdent)) {
        /* Already exist only need to remove it from modStack */
        goto MOD_STACK_OP_REMOVE;
    }

    modIdent = (char *)malloc(MAX_CHAR_OF_MOD_IDENT);
    modIdent = switch_CurrentMod();
    parentIdent = sliceGetVal(&symCollectSlice, SLICE_PARENT);

    /* Is the module specify by modIdent is exists ? */
    if (!symbolTableSearch(&symTable, modIdent)) {
        newMod = (symbolTable *)malloc(sizeof(symbolTable));
        newMod->modName = modIdent;
        symbolModuleAdd(&symTable, newMod);
    }

    newSymbol = (symbol_t *)malloc(sizeof(symbol_t));
    newSymbol->symIdent = symbolIdent;
    newSymbol->symType = SYMBOL_TYPE_NODE;
    newSymbol->symInfo.nodeMeta.parentIdent = parentIdent;
    symbolAdd(&symTable, newSymbol, newMod->modName);

MOD_STACK_OP_REMOVE:
    /* Need to remove the symbol found from list in the modStack */
    retVal = collectInfo_del(SW_CUR_IMPORT_REF(swState), symbolIdent);
    sliceRelease(&symCollectSlice);
    return retVal;
}

static int symbolCollect_BUILD_TRAP(dispatchParam *param) {
    int retVal;
    char *symbolIdent = sliceGetVal(&symCollectSlice, SLICE_IDENTIFIER);

    retVal = collectInfo_del(SW_CUR_IMPORT_REF(swState), symbolIdent);
    sliceRelease(&symCollectSlice);

    return retVal;
}

static int symbolCollect_BUILD_LEAVE_NODE(dispatchParam *param) {
    int retVal;
    char *symbolIdent = sliceGetVal(&symCollectSlice, SLICE_IDENTIFIER);

    retVal = collectInfo_del(SW_CUR_IMPORT_REF(swState), symbolIdent);
    sliceRelease(&symCollectSlice);

    return retVal;
}

static int symbolCollect_BUILD_SEQUENCE(dispatchParam *param) {
    int retVal;
    char *symbolIdent = sliceGetVal(&symCollectSlice, SLICE_IDENTIFIER);

    retVal = collectInfo_del(SW_CUR_IMPORT_REF(swState), symbolIdent);
    sliceRelease(&symCollectSlice);

    return retVal;
}

static int symbolCollect_BUILD_SMI_DEF(dispatchParam *param) {
    int retVal;
    char *symbolIdent = sliceGetVal(&symCollectSlice, SLICE_IDENTIFIER);

    retVal = collectInfo_del(SW_CUR_IMPORT_REF(swState), symbolIdent);
    sliceRelease(&symCollectSlice);

    return retVal;
}

static int symbolCollect_PARAM_IDENT(dispatchParam *param) {
    if (isNullPtr(param)) {
        return -1;
    }

    PARAM_STORE_TO_SYM_LIST(SLICE_IDENTIFIER, param);
    return 0;
}

static int symbolCollect_PARAM_TYPE(dispatchParam *param) {
    if (isNullPtr(param)) {
        return -1;
    }

    PARAM_STORE_TO_SYM_LIST(SLICE_TYPE, param);
    return 0;
}

static int symbolCollect_PARAM_PERM(dispatchParam *param) {
    if (isNullPtr(param)) {
        return -1;
    }

    PARAM_STORE_TO_SYM_LIST(SLICE_PERMISSION, param);
    return 0;
}

static int symbolCollect_PARAM_DESC(dispatchParam *param) {
    if (isNullPtr(param)) {
        return -1;
    }

    PARAM_STORE_TO_SYM_LIST(SLICE_DESCRIPTION, param);
    return 0;
}

static int symbolCollect_PARAM_PARENT(dispatchParam *param) {
    if (isNullPtr(param)) {
        return -1;
    }

    PARAM_STORE_TO_SYM_LIST(SLICE_PARENT, param);
    return 0;
}

static int symbolCollect_PARAM_SUFFIX(dispatchParam *param) {
    if (isNullPtr(param)) {
        return -1;
    }

    PARAM_STORE_TO_SYM_LIST(SLICE_OID_SUFFIX, param);
    return 0;
}

#ifdef MIB2DOC_UNIT_TESTING

void mibTreeGenTesting(void **state) {
               
}

#endif /* MIB2DOC_UNIT_TESTING */

