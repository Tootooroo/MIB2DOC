//
// Created by ayden on 2017/4/19.
//

#ifndef GL5610_MIB_DOC_GEN_TOKENOP_H
#define GL5610_MIB_DOC_GEN_TOKENOP_H

#include "type.h"
#include "list.h"

int deal_with(int type);
int deal_with_object();
int deal_with_objIdent();
int deal_with_trap();

/* Note: this macro is only use for symbolCollect_XXXX series function */
#define PARAM_STORE_TO_SYM_LIST(type, param) ({ \
    char *string; \
    string = paramListGet(&param); \
    appendElement_el(&symCollectList, buildElement(type, string)); \
})

#endif //GL5610_MIB_DOC_GEN_TOKENOP_H
