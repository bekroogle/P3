#ifndef __token_type_h__
#define __token_type_h__

typedef enum Token_Type {
	/* 01 */	OPEN_TAG, 
	/* 02 */	CLOSE_TAG, 
	/* 03 */	EMPTY_TAG,
	/* 04 */ 	WORD_TOKEN, 
	/* 05 */	SPACE_STR, 
	/* 06 */	NL_TOKEN, 
	/* 07 */	TAG_ERROR
};

#endif
