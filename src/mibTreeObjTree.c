//
// Created by ayden on 2017/4/24.
//

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "mibTreeObjTree.h"
#include "mibTreeGen.h"
#include "type.h"
#include "docGenerate.h"
#include "util.h"

/* Global */
mibObjectTreeNode mibObjectTreeRoot;

/* Local */
static int nodeCmp(void *arg, mibObjectTreeNode *node);
static int Treeprint(void *arg, mibObjectTreeNode *node);
static int descriptionDeal(mibObjectTreeNode *node);

/* Define */
#define OID_LENGTH 256
#define IS_NODE_HAS_CHILD_MT(node) (node->child ? 1 : 0)
#define IS_NODE_HAS_SIBLING_MT(node) (node->sibling ? 1 : 0)
#define LOWER_CASE(C) ({ \
    int ret; \
    if (C < 97) \
        ret = C+32; \
    else \
        ret = C; \
    ret; \
})

/* Declaration */
mibObjectTreeNode * travel_MibTree(mibObjectTreeNode *obj,
                                   int (*func)(void *argu, mibObjectTreeNode *node), void *arg);

int mibObjectTreeInit() {
    mibObjectTreeNode *obj;

    mibTreeHeadInit(&trees);
    return OK;
}

mibObjectTreeNode * mibNodeBuild(char *ident, char *oid, char *parent) {
    mibObjectTreeNode *obj;
    mibNodeInfo *info;

    if (isNullPtr(ident) || isNullPtr(oid))
        return NULL;

    info = (mibNodeInfo *)malloc(sizeof(mibNodeInfo));
    memset(info, 0, sizeof(mibNodeInfo));

    info->ident = ident;
    info->oid = oid;

    obj = (mibObjectTreeNode *)malloc(sizeof(mibObjectTreeNode));
    memset(obj, 0, sizeof(mibObjectTreeNode));

    obj->identifier = ident;
    obj->isNode = 1;
    obj->info = (void *)info;
    obj->mergeInfo.parent = parent;

    return obj;
}

mibObjectTreeNode *mibLeaveBuild(char *ident, char *type, char *rw, char *desc,
                                 char *oid, char *parent, list *additional) {
    mibObjectTreeNode *obj;
    mibLeaveInfo *info;

    if (isNullPtr(ident) || isNullPtr(type)
        ||  isNullPtr(oid) || isNullPtr(rw)
        || isNullPtr(desc) || isNullPtr(parent))
        return NULL;

    info = (mibLeaveInfo *)malloc(sizeof(mibLeaveInfo));
    memset(info, 0, sizeof(mibLeaveInfo));
    info->nodeInfo = (mibNodeInfo *)malloc(sizeof(mibNodeInfo));
    memset(info->nodeInfo, 0, sizeof(mibNodeInfo));

    info->nodeInfo->ident = ident;
    info->nodeInfo->oid = oid;
    info->type = type;
    info->rw = rw;
    info->detail = desc;
    info->additional = additional;

    obj = (mibObjectTreeNode *)malloc(sizeof(mibObjectTreeNode));
    memset(obj, 0, sizeof(mibObjectTreeNode));
    obj->identifier = ident;
    obj->info = (void *)info;
    obj->isNode = 0;
    obj->mergeInfo.parent = parent;

    return obj;
}

/* If parent is root node ,then <parent_ident> can be NULL */
int insert_MibTree(mibObjectTreeNode *root, mibObjectTreeNode *obj, char *parent_ident) {
    mibObjectTreeNode *parentNode, *child, *current;

    if (isNullPtr(root) || isNullPtr(obj) || isNullPtr(parent_ident))
        return -1;

    parentNode = search_MibTree(root, parent_ident);

    if (parentNode == NULL)
        return -1;

    child = parentNode->child;

    if (IS_NODE_HAS_CHILD_MT(parentNode)) {
        for (current = child; current != NULL; current = current->sibling ) {
            if (IS_NODE_HAS_SIBLING_MT(current)) {
                continue;
            }
            current->sibling = obj;
            obj->parent = parentNode;
            obj->head = child;
            goto MISC;
        }
    } else {
        parentNode->child = obj;
        obj->head = obj;
        obj->parent = parentNode;
    }
MISC:
    descriptionDeal(obj);
    return 0;
}

int setAsChild_MibTree(mibObjectTreeNode *parent, mibObjectTreeNode *child) {
    if (isNullPtr(parent) || isNullPtr(child)) {
        return FALSE;
    }

    if (IS_NODE_HAS_CHILD_MT(parent)) {
        insert_MibTree(parent, child, child->mergeInfo.parent);
        return TRUE;
    }

    parent->child = child;

    return TRUE;
}

int setAsParent_MibTree(mibObjectTreeNode *child, mibObjectTreeNode *parent) {
    if (isNullPtr(parent) || isNullPtr(child))
        return ERROR;

    child->parent = parent;

    return TRUE;
}

static int descriptionDeal(mibObjectTreeNode *node) {

    int i, pos, size, descSize, sumChild, sumParent;
    char *ident = getIdentFromInfo(node);
    char *parentIdent = getIdentFromInfo(node->parent);
    mibLeaveInfo *info;

    if (strlen(ident) > strlen(parentIdent))
        size = strlen(parentIdent);
    else
        size = strlen(ident);

    if (!node->isNode & !tableRecognize(ident, strlen(ident))) {
        info = node->info;

        pos = -1;
        sumChild = 0;
        sumParent = 0;
        for (i=0; i<size; i++) {
            sumChild += LOWER_CASE(ident[i]);
            sumParent += LOWER_CASE(parentIdent[i]);

            if (sumChild == sumParent) {
                pos = i;
                continue;
            }
            break;
        }
        if (pos == -1)
            return 0;

        size = strlen(ident);
        descSize = size-(pos+1);

        info->desc = (char *)malloc(descSize+1);
        memset(info->desc, 0, descSize+1);
        strncpy(info->desc, ident+pos+1, descSize);
    }
    return 0;
}

mibObjectTreeNode *parent_MibTree(mibObjectTreeNode *root, char *ident) {
    mibObjectTreeNode *node;

    node = search_MibTree(root, ident);
    if (node != NULL)
        return node->parent;
    else
        return NULL;
}

mibObjectTreeNode * search_MibTree(mibObjectTreeNode *root, char *const ident) {
    mibObjectTreeNode *target;

    target = travel_MibTree(root, nodeCmp, ident);

    return target;
}

int showTree(mibTreeHead *treeHead) {
    mibTree *currentTree;

    if (isNullPtr(treeHead))
        return ERROR;

    for (currentTree = &treeHead->trees; !isNullPtr(currentTree); currentTree = mibTreeNext(currentTree)) {
        if (isNullPtr(currentTree->root))
            continue;
        printf("Tree:\n");
        travel_MibTree(currentTree->root, Treeprint, NULL);
    }

    return OK;
}

static int Treeprint(void *arg, mibObjectTreeNode *node) {
    mibLeaveInfo *info;
    printf("%s : %s", getIdentFromInfo(node), getOidFromInfo(node));
    if (!node->isNode) {
        info = node->info;
        printf(" -- %s -- %s\n", info->type, info->detail);
    } else
        printf("\n");
    return 0;
}

int nodeCmp(void *arg, mibObjectTreeNode *node) {
    char *ident;
    char *targetIdent;
    int size, size1, size2;
    ident = arg;

    return isStringEqual(ident, getIdentFromInfo(node));
}

char * getIdentFromInfo(mibObjectTreeNode *node) {
    if (node->isNode)
        return ((mibNodeInfo *)node->info)->ident;
    else
        return ((mibLeaveInfo *)node->info)->nodeInfo->ident;

}


char *getOidFromInfo(mibObjectTreeNode *node) {
    if (node->isNode)
        return ((mibNodeInfo *)node->info)->oid;
    else
        return ((mibLeaveInfo *)node->info)->nodeInfo->oid;

}

int travel_step(mibObjectTreeNode **node, int *visitState) {
    mibObjectTreeNode *pNode;

    if (isNullPtr(node) || isNullPtr(visitState))
        return -2;

    pNode  = *node;

    switch(*visitState) {
        case VISIT_PRE:
            if (IS_NODE_HAS_CHILD_MT(pNode)) {
                *node = MIB_OBJ_TREE_NODE_CHILD(pNode);
                return 1;
            } else {
                *visitState = VISIT_IN;
                return 0;
            }
            break;

        case VISIT_IN:
            if (IS_NODE_HAS_SIBLING_MT(pNode)) {
                *visitState = VISIT_PRE;
                *node = MIB_OBJ_TREE_NODE_SIBLING(pNode);
                return 1;
            } else {
                *visitState = VISIT_POST;
                return 0;
            }
            break;

        case VISIT_POST:
            if (IS_NODE_HAS_SIBLING_MT(pNode)) {
                *visitState = VISIT_IN;
                return 0;
            } else {
                *node = MIB_OBJ_TREE_NODE_PARENT(pNode);
                return -1;
            }
            break;

        default:
            return -2;
    }

    return -2;
}

mibObjectTreeNode * travel_MibTree(mibObjectTreeNode *obj, travelFunc func, void *arg) {
    int ret = 0;

    if (isNullPtr(obj) || isNullPtr(func))
        return NULL;

    int visit = VISIT_PRE;
    mibObjectTreeNode *root = obj;

    do {
        if (visit == VISIT_PRE) {
            ret = func(arg, obj);
            if (ret == 1) return obj;
        }
        travel_step(&obj, &visit);
    } while (obj != root || visit != VISIT_POST);

    return null;
}

// mibTrees functions
mibTree * mibTreeConstruction() {
    mibTree *tree;

    tree = (mibTree *)malloc(sizeof(mibTree));
    memset(tree, 0, sizeof(mibTree));

    return tree;
}

int mibTreeSetRoot(mibTree *tree, mibObjectTreeNode *rootNode) {
    if (isNullPtr(tree) || isNullPtr(rootNode))
        return ERROR;

    if (isNonNullPtr(tree->root)) {
        setAsParent_MibTree(tree->root, rootNode);
        if (setAsChild_MibTree(rootNode, tree->root) == FALSE) {
            return ERROR;
        }
    }

    tree->root = rootNode;
    tree->rootName = strdup(rootNode->identifier);

    return OK;
}

mibTree * mibTreeNext(mibTree *tree) {
    if (isNullPtr(tree) || MIBTREE_IS_LAST_TREE(tree))
        return NULL;

    return containerOf(listNodeNext(&tree->node), mibTree, node);
}

mibTree * mibTreePrev(mibTree *tree) {
    if (isNullPtr(tree) || MIBTREE_IS_FIRST_TREE(tree))
        return NULL;

    return containerOf(listNodePrev(&tree->node), mibTree, node);
}

mibTree * mibTreeSearch(mibTree *tree, char *name) {
    mibTree *currentTree;

    if (isNullPtr(tree) || MIBTREE_IS_LAST_TREE(tree))
        return NULL;

    int match = FALSE;
    currentTree = tree;

    do {
        match = strncmp(currentTree->rootName, name, strlen(name));
        if (match) {
            break;
        }
    } while (currentTree = mibTreeNext(currentTree));

    return currentTree;
}

int mibTreeAppend(mibTree *head, mibTree *new) {
    if (isNullPtr(head) || isNullPtr(new)) {
        return FALSE;
    }

    if (listNodeAppend(&head->node, &new->node) == NULL) {
        return FALSE;
    }

    return TRUE;
}

mibTree * mibTreeDelete(mibTree *node) {
    if (isNullPtr(node)) {
        return NULL;
    }
    if (listNodeDelete(&node->node) == NULL) {
        return NULL;
    }
    return node;
}

mibTree * mibTreeDeleteByName(mibTree *treeListHead, char *name) {
    mibTree *beDeleted;

    if (isNullPtr(treeListHead) || isNullPtr(name)) {
        return NULL;
    }

    beDeleted = mibTreeSearch(treeListHead, name);
    mibTreeDelete(beDeleted);

    return beDeleted;
}

// Success: return the root of the new tree.
// Failed : return NULL.
mibTree * mibTreeMerge(mibTree *lTree, mibTree *rTree) {
    int ret;
    mibTree *merged;

    // Try to merge left tree into right tree.
    ret = insert_MibTree(lTree->root, rTree->root, MIB_OBJ_TREE_NODE_PARENT_NAME(rTree->root));
    if (ret == 0) {
        return lTree;
    }
    // Try to merge right tree into left tree.
    ret = insert_MibTree(rTree->root, lTree->root, MIB_OBJ_TREE_NODE_PARENT_NAME(lTree->root));
    if (ret == 0) {
        return rTree;
    }
    return NULL;
}

/* mibTreeHead functions */
int mibTreeHeadInit(mibTreeHead *treeHead) {
    if (isNullPtr(treeHead))
        return FALSE;

    memset(treeHead, 0, sizeof(mibTreeHead));
    return TRUE;
}

/* Desc: Try to merge last tree into another tree
 * or merge another tree into last tree.
 *
 * Note: if merge failed you should terminate whole
 * program cause the mibTree list is broken.
 */
int mibTreeHeadMerge_LAST(mibTreeHead *treeHead) {
    mibTree *last, *current, *newTree, *current_tmp;

    if (isNullPtr(treeHead)) {
        return FALSE;
    }

    last = treeHead->last;
    current = &treeHead->trees;

    do {
        if (current == last) {
            continue;
        }

        newTree = mibTreeMerge(current, last);
        // Merge success
        // After that we should remove the two tree
        // and place the new one into the mibTree list.
        if (!isNullPtr(newTree)) {
            current_tmp = mibTreeNext(current);

            current = mibTreeDelete(current);
            last = mibTreeDelete(last);

            if (isNullPtr(current) || isNullPtr(last)) {
                return FALSE;
            }

            mibTreeAppend(&treeHead->trees, newTree);

            last = newTree;
            current = current_tmp;
        }
    } while (current = mibTreeNext(current));

    return TRUE;
}

/* Situations: Assume exist two trees then
 * (1) A is descendent of B, vice versa.
 * (2) A and B has same set of ancestors.
 */
static mibTree * mergeByComplete(mibTree *l, mibTree *r);
// Merge treeSet into theTree
static mibTree * __mergeHelper(mibTree *theTree, mibTree *treeSet, int *numOfTree);
int mibTreeHeadMerge(mibTreeHead *treeHead) {
    int numOfTree, numOfTree_prev;
    mibTree *current, *current_merge, *newTree,
            *deleteMerge, *theTree;

    if (isNullPtr(treeHead))
        return FALSE;

    numOfTree = treeHead->numOfTree;

    theTree = mibTreeNext(&treeHead->trees);
    current = mibTreeNext(theTree);

    mibTreeDelete(theTree);
    --numOfTree;

    // Merge a set of trees with theTree
    theTree = __mergeHelper(theTree, current, &numOfTree);

    mibTreeAppend(&treeHead->trees, theTree);
    treeHead->numOfTree = numOfTree;

    return TRUE;
}

static mibTree * __mergeHelper(mibTree *theTree, mibTree *treeSet, int *numOfTree) {
    int numOfTree_prev, num = *numOfTree;
    mibTree *deletedTree, *currentMerge, *current, *newTree;
    current = treeSet;

    do {
        currentMerge = current;
        numOfTree_prev = num;

        while (currentMerge) {
            newTree = mibTreeMerge(theTree, currentMerge);
            if (!newTree)
                newTree = mergeByComplete(theTree, currentMerge);

            if (newTree) {
                if (isStringEqual(newTree->rootName, theTree->rootName))
                    theTree = newTree;
                else
                    theTree = currentMerge;

                if (current == currentMerge)
                    current = mibTreeNext(current);

                deletedTree = currentMerge;
                currentMerge = mibTreeNext(currentMerge);
                mibTreeDelete(deletedTree);

                --num;
                continue;
            } else {
                currentMerge = mibTreeNext(currentMerge);
            }
        }
    } while (numOfTree_prev > num);

    *numOfTree = num + 1;
    return theTree;
}

static char * ancestorCommon(mibObjectTreeNode *l, mibObjectTreeNode *r) {
    if (isNullPtr(l) || isNullPtr(r))
        return NULL;

    symbol_t *sym_l, *sym_r;
    char *parent_l, *parent_r;

    parent_l = l->mergeInfo.parent;
    parent_r = r->mergeInfo.parent;

    while (parent_l != NULL || parent_r != NULL) {
        if (parent_l) {
            sym_l = symbolTableSearch(SYMBOL_TBL_R, parent_l);
            if (sym_l == null)
                parent_l = null;
            else {
                if (sym_l->wall == (unsigned long)r)
                    return sym_l->symIdent;
                sym_l->wall = (unsigned long)l;
                parent_l = sym_l->symInfo.nodeMeta.parentIdent;
            }
        }
        if (parent_r) {
            sym_r = symbolTableSearch(SYMBOL_TBL_R, parent_r);
            if (sym_r == null)
                parent_r = null;
            else {
                if (sym_r->wall == (unsigned long)l)
                    return sym_r->symIdent;
                sym_r->wall = (unsigned long)r;
                parent_r = sym_r->symInfo.nodeMeta.parentIdent;
            }
        }
    }
    return NULL;
}
static mibTree * mergeByComplete(mibTree *l, mibTree *r) {
    if (isNullPtr(l) || isNullPtr(r))
        return NULL;

    symbol_t *symbol;
    char *parent, *current;
    mibObjectTreeNode *node;

    // Find common ancestor
    char *ancestor = ancestorCommon(l->root, r->root);
    if (isNullPtr(ancestor))
       return NULL;

    // Expand tree up to common ancestor
    int idx = 0;
    mibTree *trees[2] = { l, r };

    while (idx < 2) {
        parent = trees[idx]->root->mergeInfo.parent;
        while (parent != NULL) {
            symbol = symbolTableSearch(SYMBOL_TBL_R, parent);

            current = symbol->symIdent;
            if (isStringEqual(current, ancestor))
                break;
            node = mibNodeBuild(current,
                                symbol->symInfo.nodeMeta.suffix,
                                symbol->symInfo.nodeMeta.parentIdent);

            mibTreeSetRoot(trees[idx], node);

            parent = symbol->symInfo.nodeMeta.parentIdent;
        }
        ++idx;
    }

    node = mibNodeBuild(parent,
                        symbol->symInfo.nodeMeta.suffix,
                        symbol->symInfo.nodeMeta.parentIdent);

    mibTreeSetRoot(l, node);
    mibTreeSetRoot(r, node);

    l->root = node;
    return l;
}

int mibTreeHeadAppend(mibTreeHead *treeHead, mibObjectTreeNode *newNode) {
    char *parent;
    mibTree *treeIter, *last;
    mibObjectTreeNode *treeRoot;

    if (isNullPtr(treeHead) || isNullPtr(newNode)) {
        return FALSE;
    }

    parent = newNode->mergeInfo.parent;

    // A new root.
    if (isNullPtr(parent)) {
        goto NEW_TREE;
    }

    // First check last tree.
    treeIter = treeHead->last;
    if (isNullPtr(treeIter))
        goto ITERATE_OVER_ALL;

LAST_TREE:
    treeRoot = treeIter->root;

    if (insert_MibTree(treeRoot, newNode, parent) != -1) {
        return TRUE;
    }

ITERATE_OVER_ALL:
    // Iterate over all another trees.
    last = treeHead->last;
    treeIter = &treeHead->trees;

    if (isNullPtr(treeIter))
        goto NEW_TREE;

    do {
        if (insert_MibTree(treeIter->root, newNode, parent) != -1) {
            treeHead->last = treeIter;
            return TRUE;
        }
    } while (treeIter = mibTreeNext(treeIter));

NEW_TREE:
    // Build a new tree.
    treeIter = mibTreeConstruction();
    mibTreeSetRoot(treeIter, newNode);

    mibTreeAppend(&treeHead->trees, treeIter);
    treeHead->last = treeIter;
    treeHead->numOfTree++;

    return TRUE;
}

static char * oidComplement(char *parentOid, char *suffix) {
    char *oid;
    int oidLength = SIZE_OF_OID_STRING;

    if (isNullPtr(parentOid) || isNullPtr(suffix))
        return NULL;

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

static int oidComplete(void *arg, mibObjectTreeNode *node) {
    char *newOid, *parentOid;
    mibObjectTreeNode *parent;
    mibNodeInfo *nInfo_P, *nInfo_C;
    mibLeaveInfo *lInfo_P, *lInfo_C;

    if (isNullPtr(node))
        return ERROR;

    if (isNullPtr(node->parent))
        return OK;

    parent = node->parent;
    nInfo_P = parent->info;

    if (parent->isNode) {
        nInfo_P = parent->info;
        parentOid = nInfo_P->oid;
    } else {
        lInfo_P = parent->info;
        parentOid = lInfo_P->nodeInfo->oid;
    }

    if (node->isNode) {
        nInfo_C = node->info;
        newOid = oidComplement(parentOid, nInfo_C->oid);
        RELEASE_MEM(nInfo_C->oid);
        nInfo_C->oid = newOid;
    } else {
        lInfo_C = node->info;
        newOid = oidComplement(parentOid, lInfo_C->nodeInfo->oid);
        RELEASE_MEM(lInfo_C->nodeInfo->oid);
        lInfo_C->nodeInfo->oid = newOid;
    }

    return OK;
}

int mibTreeHeadComplete(mibTreeHead *treeHead, symbolTable *symTbl) {
    if (isNullPtr(treeHead)) return ERROR;

    assert(treeHead->numOfTree == 1);

    // Import nothing from another mib files.
    if (symTbl->numOfSymbols == 0)
        return OK;

    mibTree *tree = mibTreeHeadFirstTree(treeHead);

    char *ident, *oid, *parent;

    parent = tree->root->mergeInfo.parent;
    symbol_t *symbol = symbolTableSearch(symTbl, parent);

    mibObjectTreeNode *node;

    while (isNonNullPtr(symbol)) {
        ident = symbol->symIdent;
        oid = symbol->symInfo.nodeMeta.suffix;
        parent = symbol->symInfo.nodeMeta.parentIdent;

        node = mibNodeBuild(strdup(ident), strdup(oid), strdup(parent));
        if (mibTreeSetRoot(tree, node) == ERROR)
            abort();

        symbol = symbolTableSearch(symTbl, parent);
    }

    return OK;
}

int mibTreeHeadOidComplete(mibTreeHead *treeHead) {
    mibTree *tree;

    if (isNullPtr(treeHead))
        return ERROR;

    assert(treeHead->numOfTree == 1);

    tree = mibTreeHeadFirstTree(treeHead);

    travel_MibTree(tree->root, oidComplete, NULL);

    return OK;
}

mibTree * mibTreeHeadFirstTree(mibTreeHead *treeHead) {
    if (isNullPtr(treeHead))
        return NULL;

    return mibTreeNext(&treeHead->trees);
}

// mibTree Type functions
static char * mibLeaveGetType(mibObjectTreeNode *node) {
    if (isNullPtr(node)) return NULL;
    if (node->isNode) return NULL;

    mibLeaveInfo *lInfo = node->info;

    return lInfo->type;
}

// Todo: Need to check the sequence type.
_Bool isMibNodeType_TABLE(mibObjectTreeNode *node) {
    if (node->isNode == TRUE)
        return FALSE;

    char *type = mibLeaveGetType(node);
    assert(isNonNullPtr(type));

    char *seqPrefix = "SEQUENCE OF";

    if (strncmp(type, seqPrefix, strlen(seqPrefix)))
        return FALSE;

    return TRUE;
}

_Bool isMibNodeType_ENTRY(mibObjectTreeNode *node) {
    if (node->isNode == TRUE)
        return FALSE;

    char *type = mibLeaveGetType(node);
    assert(isNonNullPtr(type));

    typeCate cate = typeTableTypeCate(&mibTypeTbl, type);
    if (cate == ERROR) return ERROR;

    if (cate == CATE_SEQUENCE) return TRUE;

    return FALSE;
}

#ifdef MIB2DOC_UNIT_TESTING

#include "test.h"

typedef struct {
    int idx;
    char *order;
    char *oid[];
} order;

static int mibTreeMergeAssert(void *arg, mibObjectTreeNode *node) {
    int idx;
    order *pOrder = arg;
    mibNodeInfo *info;

    info = node->info;

    idx = pOrder->idx;
    if (pOrder->order[idx] != node->identifier[0])
        fail();
    if (strncmp(pOrder->oid[idx], info->oid, strlen(info->oid)) != 0)
        fail();

    ++idx;
    pOrder->idx = idx;
}

void mibTreeObjTree__MIBTREE_MERGE(void **state) {
    // Merge testing
    mibObjectTreeNode *node;
    mibTreeHead treeHead;
    mibTree *currentTree;

    memset(&treeHead, 0, sizeof(mibTreeHead));

    node = mibNodeBuild("A", strdup("1"), NULL);
    mibTreeHeadAppend(&treeHead, node);

    node = mibNodeBuild("B", strdup("2"), "A");
    mibTreeHeadAppend(&treeHead, node);

    node = mibNodeBuild("F", strdup("1"), "C");
    mibTreeHeadAppend(&treeHead, node);

    node = mibNodeBuild("E", strdup("2"), "C");
    mibTreeHeadAppend(&treeHead, node);

    node = mibNodeBuild("C", strdup("3"), "A");
    mibTreeHeadAppend(&treeHead, node);

    node = mibNodeBuild("G", strdup("2"), "B");
    mibTreeHeadAppend(&treeHead, node);

    node = mibNodeBuild("D", strdup("1"), "B");
    mibTreeHeadAppend(&treeHead, node);

    assert_int_equal(treeHead.numOfTree, 3);

    mibTreeHeadMerge(&treeHead);
    mibTreeHeadOidComplete(&treeHead);

    assert_int_equal(treeHead.numOfTree, 1);

    char nodeOrder[7] = {'A', 'B', 'G', 'D', 'C', 'F', 'E'};
    char *oid[7] = {"1", "1.2", "1.2.2", "1.2.1", "1.3", "1.3.1", "1.3.2"};
    order orderDeck;

    orderDeck.idx = 0;
    orderDeck.order = nodeOrder;

    currentTree = mibTreeNext(&treeHead.trees);
    travel_MibTree(currentTree->root, mibTreeMergeAssert, &orderDeck);

    // Merge by complete testing
    symTableInit();

    memset(&treeHead, 0, sizeof(mibTreeHead));

    symbol_t *symbol = symbolNodeConst("A", "N/A", "1");
    symbolTableAdd(SYMBOL_TBL_R, symbol);

    node = mibNodeBuild("B", strdup("1"), "A");
    mibTreeHeadAppend(&treeHead, node);

    node = mibNodeBuild("C", strdup("1"), "B");
    mibTreeHeadAppend(&treeHead, node);

    node = mibNodeBuild("D", strdup("2"), "A");
    mibTreeHeadAppend(&treeHead, node);

    node = mibNodeBuild("E", strdup("2"), "D");
    mibTreeHeadAppend(&treeHead, node);

    mibTreeHeadMerge(&treeHead);
    assert_int_equal(treeHead.numOfTree, 1);
}

#endif /* MIB2DOC_UNIT_TESTING */

/* mibTreeObjTree.c */
