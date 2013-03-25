#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "token_type.h"
#include "token.h"
#include "char_type.h"
#include "state.h"


//#include "gettoken.h"

using namespace std;

void getToken(Token& tok, ifstream& ifp);

int main()
{
    ifstream ifp;
    ofstream ofp;
    string if_name;
    Token currentToken;
    vector<Token> token_list;
    State_Name state = START;

    cout << "Please enter the name of the input file: ";
    cin >> if_name;

    ifp.open(if_name.c_str());

    if (ifp.fail()) {
        cerr << "Unable to open file :" << if_name;
        exit(EXIT_FAILURE);
    }

    ofp.open("log.txt");

    if (ofp.fail()) {
        cerr << "Unable to open log file. Results echoed to standard output only.";
        exit(EXIT_FAILURE);
    }
    while (!ifp.eof()) {
        getToken(currentToken, ifp);
        if (!ifp.fail()) {
            token_list.push_back(currentToken);
            cout << left;
            ofp << left;
            ofp << "token=" << setw(14) << human_readable[currentToken.type] <<
                    " type=" << currentToken.type <<
                    " tag name=" << setw(9) << currentToken.lexeme <<
                    " on line #" << currentToken.line_number <<
                    " at charpos=" << currentToken.char_pos << endl;
        }
    }


    return EXIT_SUCCESS;
}

using namespace std;

void getToken(Token& tok, ifstream& ifp)
{
    tok.lexeme = "";
    tok.char_pos = 0;
    tok.type = ERR_TOKEN;
    tok.line_number = 0;
    cout << "called getToken";
    char c;
    State_Name state = START;
    State_Name prevState = START;
    Char_Type charType;
    static long lineNumber = 1;
    static int charPos = 0;

    while(!ifp.eof()) {
        c = ifp.get();
        if (ifp.fail()) {
            break;
        }

        charPos++;

        if (state == START) {
            tok.char_pos = charPos;
            tok.line_number = lineNumber;
        }

              cout << "**state: "<< state << " + char:  " <<
                c << endl;
        charType = char_classes[c];
        state = state_trans[state][charType];

        switch (state) {
            case OT1:
//                tok.lexeme += c;
                break;
            case OT2:
                tok.lexeme += c;
                tok.type = OPEN_TAG;
                break;
            case OT3:
                tok.lexeme += c;
                break;
            case CT1:
//                tok.lexeme += c;
                tok.type = CLOSE_TAG;
                break;
            case CT2:
                tok.lexeme += c;
                break;
            case CT3:
                tok.lexeme += c;
                return;
            case ET1: break;
            case SP1:
                tok.lexeme += c;
                tok.type = SPACE_STR;
                break;
            case ETF:
                tok.type = EMPTY_TAG;
                return;
            case NLF:
                tok.lexeme = "\\n";
                tok.type = NL_TOKEN;
                lineNumber++;
                charPos = 0;
                return;
            case SPF:
                ifp.unget();
                return;
            case OTF:
//                tok.lexeme += c;
                return;
            case CTF:
//                tok.lexeme += c;
                return;
            case W1:
                tok.lexeme += c;
                break;
            case WF:
                tok.type = WORD_TOKEN;
                ifp.unget();
                return;

        }
    }
}
