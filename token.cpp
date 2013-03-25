#include "token.h"

Token::Token()
{
	type = TAG_ERROR;
	lexeme = "";
	line_pos = 1;
	char_pos = 1;
}

string Token::getTypeDesc()
{
	switch (type) {
	case OPEN_TAG:
		return "Open Tag";
	case CLOSE_TAG:
		return "Close Tag";
	case EMPTY_TAG:
		return "Empty Tag";
	case WORD_TOKEN:
		return "Word";
	case SPACE_STR:
		return "Space String";
	case NL_TOKEN:
		return "Newline";
	case TAG_ERROR:
		return "Tag Error";
	}
}

void Token::addChar(char c)
{
	lexeme += c;
}
