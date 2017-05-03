//
// Created by ayden on 2017/4/24.
//

#include <malloc.h>
#include <string.h>
#include "../include/mibTreeObjTree.h"
#include "../include/type.h"

/* Global */
mibObjectTreeNode mibObjectTreeRoot;

/* Local */
static int nodeCmp(void *arg, mibObjectTreeNode *node);
static int Treeprint(void *arg, mibObjectTreeNode *node);
/* Define */
#define OID_LENGTH 256

#define IS_NODE_HAS_CHILD_MT(node) (node->child ? 1 : 0)
#define IS_NODE_HAS_SIBLING_MT(node) (node->sibling ? 1 : 0)

/* Declaration */
mibObjectTreeNode * mibNodeBuild(char *ident, char *oid);
mibObjectTreeNode *mibLeaveBuild(char *ident, char *type, char *rw, char *desc, char *oid);
mibObjectTreeNode * travel_mot(mibObjectTreeNode *obj, int (*func)(void *argu, mibObjectTreeNode *node), void *arg);

void mibObjectTreeInit(mibObjectTreeNode *root) {
    mibNodeInfo *rootInfo;
    mibObjectTreeNode *obj;

    memset(root, 0, sizeof(mibObjectTreeNode));

    rootInfo = (mibNodeInfo *)malloc(sizeof(mibNodeInfo));
    memset(rootInfo, 0, sizeof(mibNodeInfo));
    rootInfo->ident = "root";
    rootInfo->oid = "root";

    root->isNode = 1;
    root->info = (void *)rootInfo;
    root->head = root;

    insert_mot(root, mibNodeBuild("iso", "1"), "root");
    insert_mot(root, mibNodeBuild("org", "1.3"), "iso");
    insert_mot(root, mibNodeBuild("dod", "1.3.6"), "org");
    insert_mot(root, mibNodeBuild("internet", "1.3.6.1"), "dod");
    insert_mot(root, mibNodeBuild("private", "1.3.6.1.4"), "internet");
    insert_mot(root, mibNodeBuild("enterprises", "1.3.6.1.4.1"), "private");
}

mibObjectTreeNode * mibNodeBuild(char *ident, char *oid) {
    mibObjectTreeNode *obj;
    mibNodeInfo *info;

    if (IS_PTR_NULL(ident) || IS_PTR_NULL(oid))
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
    return obj;
}

mibObjectTreeNode *mibLeaveBuild(char *ident, char *type, char *rw, char *desc, char *oid) {
    mibObjectTreeNode *obj;
    mibLeaveInfo *info;

    if (IS_PTR_NULL(ident) || IS_PTR_NULL(type) ||  IS_PTR_NULL(oid))
        return NULL;

    info = (mibLeaveInfo *)malloc(sizeof(mibLeaveInfo));
    memset(info, 0, sizeof(mibLeaveInfo));
    info->nodeInfo = (mibNodeInfo *)malloc(sizeof(mibNodeInfo));
    memset(info->nodeInfo, 0, sizeof(mibNodeInfo));

    info->nodeInfo->ident = ident;
    info->nodeInfo->oid = oid;
    info->type = type;
    info->rw = rw;
    info->desc = desc;

    obj = (mibObjectTreeNode *)malloc(sizeof(mibObjectTreeNode));
    memset(obj, 0, sizeof(mibObjectTreeNode));
    obj->identifier = ident;
    obj->info = (void *)info;
    obj->isNode = 0;

    return obj;
}

/* If parent is root node ,then <parent_ident> can be NULL */
int insert_mot(mibObjectTreeNode *root, mibObjectTreeNode *obj, char *parent_ident) {
    mibObjectTreeNode *parentNode, *child, *current;

    if (IS_PTR_NULL(root) || IS_PTR_NULL(obj) || IS_PTR_NULL(parent_ident))
        return -1;

    parentNode = search_mot(root, parent_ident);

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
            return 0;
            }
    } else {
        parentNode->child = obj;
        obj->head = obj;
    }
}

mibObjectTreeNode *parent_mot(mibObjectTreeNode *root, char *ident) {
    mibObjectTreeNode *node;

    node = search_mot(root, ident);
    if (node != NULL)
        return node->parent;
    else
        return NULL;
}

mibObjectTreeNode * search_mot(mibObjectTreeNode *root, char *const ident) {
    mibObjectTreeNode *target;

    target = travel_mot(root, nodeCmp, ident);

    return target;
}

void showTree(mibObjectTreeNode *root) {
    travel_mot(root, Treeprint, NULL);
}

static int Treeprint(void *arg, mibObjectTreeNode *node) {
    printf("%s : %s", getIdentFromInfo(node), getOidFromInfo(node));
    if (!node->isNode)
        printf(" -- %s\n", ((mibLeaveInfo *)node->info)->type);
    else
        printf("\n");
    return 0;
}

int nodeCmp(void *arg, mibObjectTreeNode *node) {
    char *ident;
    char *targetIdent;
    int size, size1, size2;
    ident = arg;

    targetIdent = getIdentFromInfo(node);
    size1 = strlen(ident);
    size2 = strlen(targetIdent);

    if (size1 < size2)
        size = size1;
    else
        size = size2;

    if (strncmp(ident, getIdentFromInfo(node), size) == 0)
        return 1;
    else
        return 0;
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


mibObjectTreeNode * travel_mot(mibObjectTreeNode *obj, int (*func)(void *argu, mibObjectTreeNode *node), void *arg) {
    int ret;
    mibObjectTreeNode *targetC, *targetS;

    if (IS_PTR_NULL(obj) || IS_PTR_NULL(func))
        return NULL;


    ret = func(arg, obj);
    if (ret == 1) {
        return obj;
    }

    targetC = travel_mot(obj->child, func, arg);
    targetS = travel_mot(obj->sibling, func, arg);

    if (targetC != NULL)
        return targetC;
    else
        return targetS;
}
