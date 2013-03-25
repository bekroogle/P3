#ifndef __token_h__
#define __token_h__
#include <string>

class Token
{
public:
	Token();
	Token(Token_Type, long line_pos = 1,
          int char_pos = 1, std::string lexeme = "");
	~Token();
	Token_Type getType() { return type; }
	std::string getTypeDesc();
	void setLinePos(long l) {line_pos = l;}
	void setCharPos(int i) {char_pos = i;}
	void addChar(char);

private:
	Token_Type type;
	std::string lexeme;
	long line_pos;
	int char_pos;
};
#endif

