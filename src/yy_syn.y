%token IDENTIFIER OBJ_SPECIFIER
%token SYNTAX_SPECIFIER
%token ACCESS_SPECIFIER ACCESS_VALUE
%token STATUS_SPECIFIER STATUS_VALUE
%token DESC_SPECIFIER DESC_VALUE
%token MOUNT_POINT ASSIGNED
%token BEGIN_ END_ DEF SEQ
%token COMMA SEMICOLON INDEX_ TRAP_SPECIFIER
%token OBJ_IDEN_ L_BRACE R_BRACE OBJECTS_
%token TYPE NUM FROM_ IMPORTS_

// Prologue
%code top {
    #include <stdio.h>
    #include "type.h"
    #include "mibTreeGen.h"
    #include "mibTreeObjTree.h"
    #include "dispatcher.h"
    #include "symbolTbl.h"
    #include "string.h"

    #define YYSTYPE char *
    extern symbolTable symTable; 
    extern YYSTYPE yylval;
    void yyerror(char const *s) {
        fprintf(stderr, "%s: %s\n", s, yylval);
    }    
    
    dispatchParam importParam;
    genericStack importInfoStack; 
     
    int syntaxParserInit(void) {
        memset(&importParam, 0, sizeof(dispatchParam));
        genericStackConstruct(&importInfoStack, 20, sizeof(collectInfo *)); 
    }
}

// Grammar rules
%%

MIB :
	MAIN_PART;
    
MAIN_PART :
	  OBJ_DEAL MAIN_PART
	| OBJ MAIN_PART
	| TRAP MAIN_PART
	| SEQUENCE MAIN_PART
    | SMI MAIN_PART
	| END_ MAIN_PART
    | DEFINITION MAIN_PART
    | IMPORT MAIN_PART
    | /* empty */ ;

DEFINITION :
	IDENTIFIER DEF ASSIGNED BEGIN_;

IMPORT :
	IMPORTS_ MODULES SEMICOLON    {
        // Begining to import symbol from another mib files.
        importWorks(&importInfoStack); 
    };

MODULES :
	MODULES_CONTENT MODULES 
    | /* empty */  ;

MODULES_CONTENT :
    ITEMS FROM_ IDENTIFIER {
        dispatchParam *current;    
        current = &importParam;
        
        int ret = TRUE;
        collectInfo *importInfo = collectInfoConst($IDENTIFIER);
         
        // Store symbols that should be included.
        while (current = dispatchParamNext(current)) {
            ret = collectInfo_add(importInfo, current->param);
            if (ret == FALSE) {
                printf("IMPORT: Symbol conflict.\n"); 
                exit(1);
            } 
        }
        disParamRelease_Static(&importParam, NULL); 

        push(&importInfoStack, &importInfo); 
    }

ITEMS :
	IDENTIFIER { 
        if (disParamStore(&importParam, disParamConstruct($IDENTIFIER)) == NULL) {
            exit(1); 
        }
    }
	| IDENTIFIER COMMA ITEMS { 
        if (disParamStore(&importParam, disParamConstruct($IDENTIFIER)) == NULL) {
            exit(1); 
        }
    }
	| /* empty */ ;

SEQUENCE :
	IDENTIFIER ASSIGNED SEQ L_BRACE SEQ_ITEM R_BRACE;

SEQ_ITEM :
	IDENTIFIER TYPE COMMA SEQ_ITEM
	| IDENTIFIER TYPE;

SMI :
    "SMI" IDENTIFIER {
        dispatchParam *param  = disParamConstruct(SLICE_IDENTIFIER);
        disParamStore(param, disParamConstruct($IDENTIFIER));

        dispatch(DISPATCH_PARAM_STAGE, param);
        dispatch(MIBTREE_GENERATION, disParamConstruct(SMI_DEF));
    };


OBJ_DEAL :
	OBJ_IDENTIFIER { 
        dispatchParam *param = disParamConstruct(OBJECT_IDENTIFIER);
        dispatch(MIBTREE_GENERATION, param);
    };

OBJ_IDENTIFIER :
	IDENTIFIER[chil] OBJ_IDEN_ ASSIGNED L_BRACE IDENTIFIER[parent] NUM R_BRACE {
		dispatchParam *param = disParamConstruct(SLICE_IDENTIFIER);
		disParamStore(param, disParamConstruct($chil));
		dispatch(DISPATCH_PARAM_STAGE, param);

		param = disParamConstruct(SLICE_PARENT);
		disParamStore(param, disParamConstruct($parent));
		dispatch(DISPATCH_PARAM_STAGE, param);

		param = disParamConstruct(SLICE_OID_SUFFIX);
		disParamStore(param, disParamConstruct($NUM));
		dispatch(DISPATCH_PARAM_STAGE, param);
};

OBJ :
	HEAD BODY { dispatch(MIBTREE_GENERATION, disParamConstruct(OBJECT)); };

TRAP :
	TRAP_HEAD PROPERTY    { dispatch(MIBTREE_GENERATION, disParamConstruct(TRAP)); };

TRAP_HEAD :
	IDENTIFIER TRAP_SPECIFIER {
		dispatchParam *param = disParamConstruct(SLICE_IDENTIFIER);
		disParamStore(param, disParamConstruct($IDENTIFIER));

		dispatch(DISPATCH_PARAM_STAGE, param);
	};

HEAD :
	IDENTIFIER OBJ_SPECIFIER {
		dispatchParam *param = disParamConstruct(SLICE_IDENTIFIER);
		disParamStore(param, disParamConstruct($IDENTIFIER));
		dispatch(DISPATCH_PARAM_STAGE, param);
	};

BODY :
	PROPERTY;

PROPERTY :
	SYNTAX PROPERTY
	| ACCESS PROPERTY
	| STATUS PROPERTY
	| DESCRIPTION PROPERTY
	| INDEX PROPERTY
 	| MOUNT PROPERTY
 	| OBJECT PROPERTY
 	| /* empty */;

OBJECT :
	OBJECTS_ L_BRACE OBJECT_ITEM R_BRACE;

OBJECT_ITEM :
	IDENTIFIER COMMA OBJECT_ITEM
	| IDENTIFIER ;

SYNTAX :
	SYNTAX_SPECIFIER SYNTAX_VALUE ;

SYNTAX_VALUE :
	TYPE {
		dispatchParam *param = disParamConstruct(SLICE_TYPE);
	    disParamStore(param, disParamConstruct($TYPE));
		dispatch(DISPATCH_PARAM_STAGE, param);
    }
    | IDENTIFIER {
 		dispatchParam *param = disParamConstruct(SLICE_TYPE);
	    disParamStore(param, disParamConstruct($IDENTIFIER));
		dispatch(DISPATCH_PARAM_STAGE, param);
 	};

ACCESS :
	ACCESS_SPECIFIER ACCESS_VALUE {
		dispatchParam *param = disParamConstruct(SLICE_PERMISSION);
		disParamStore(param, disParamConstruct($ACCESS_VALUE));
		dispatch(DISPATCH_PARAM_STAGE, param);
	};

STATUS :
	STATUS_SPECIFIER STATUS_VALUE;

DESCRIPTION :
	DESC_SPECIFIER DESC_VALUE {
		dispatchParam *param = disParamConstruct(SLICE_DESCRIPTION);
		disParamStore(param, disParamConstruct($DESC_VALUE));
		dispatch(DISPATCH_PARAM_STAGE, param);
	};

INDEX : INDEX_ L_BRACE INDEX_ITEM R_BRACE;

INDEX_ITEM :
	IDENTIFIER COMMA INDEX_ITEM
	| IDENTIFIER;

MOUNT :
	ASSIGNED L_BRACE IDENTIFIER NUM R_BRACE {
		dispatchParam *param = disParamConstruct(SLICE_PARENT);
		disParamStore(param, disParamConstruct($IDENTIFIER));
		dispatch(DISPATCH_PARAM_STAGE, param);

		param = disParamConstruct(SLICE_OID_SUFFIX);
	    disParamStore(param, disParamConstruct($NUM));
		dispatch(DISPATCH_PARAM_STAGE, param);
	};

%%

// Epilogue

