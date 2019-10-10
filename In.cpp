#include "pch.h"
#include "Error.h"
#include "In.h"
using namespace std;
namespace In
{
	IN getin(wchar_t infile[])
	{
		ifstream fin(infile);
		IN newIn;
		if (!fin.is_open())
			throw ERROR_THROW(110);
		string STR;
		string text;
		int counterSeparate = 0;
		while (!fin.eof())
		{
			getline(fin, STR);
			text += STR;
			text += '\n';
			newIn.lines++;
		}
		int TMP = newIn.lines;
		while (TMP > 0) {
			TMP = TMP / 10;
			counterSeparate++;//таким образом мы узнаем количество разрядов числа, в котором записано количество линий
		}
		newIn.text = new unsigned char[text.size() + 1 + newIn.lines*(counterSeparate+2)];
		int line = 1, column = 0; unsigned char* ptrText = newIn.text;
		*ptrText = '0';
		ptrText++;
		*ptrText = '1';
		ptrText++;
		*ptrText = ' ';
		ptrText++;
		for (int i = 0; i < text.size(); i++)
		{
			
			if (newIn.code[*((unsigned char*)&text[i])] == IN::F)
			{
				cout << (int)*((unsigned char*)&text[i])<<endl;
				cout << text[i];
				throw ERROR_THROW_IN(111, line, column)
			}
			else if (newIn.code[*((unsigned char*)&text[i])] == IN::I) newIn.ignor++;
			else if (newIn.code[*((unsigned char*)&text[i])] != IN::T)
			{
				*ptrText = newIn.code[*((unsigned char*)&text[i])];
				ptrText++;
			}
			else
			{
				*ptrText = text[i];
				ptrText++;
			}
			if (text[i] == '\n')
			{
				line++;
				column = 0;
				char numberLine[20];
				_itoa_s(line, numberLine, 10);
				
				for (int i = 0; i < strlen(numberLine); i++) {
					*ptrText = numberLine[i];
					ptrText++;
				}
				if (line < 10) {
					*ptrText = '0';
					swap(*ptrText, *(ptrText - 1));
					ptrText++;
				}
				*ptrText = ' ';
				ptrText++;
			}
			else column++;
		}
		*ptrText = '\0';
		newIn.size = strlen((char*)newIn.text);
		//удалим лишние пробелы, и разделим все лексемы пробелами
		unsigned char* textFormated = new unsigned char[(newIn.size * 2)+1];
		ptrText = textFormated;
		bool spaceAdded=true;
		bool scope = false;
		for (int i = 0; i < newIn.size; i++)
		{
			if (*(newIn.text + i) != ' ')
			{
				if (*(newIn.text + i) == '\'')
				{
					if (!scope) scope = true;
					else scope = false;
				}

				if(((*(newIn.text + i) ==';'|| *(newIn.text + i) == ',')|| (*(newIn.text + i) == '+')||
					(*(newIn.text + i) == '-') ||( *(newIn.text + i) == '*')||(*(newIn.text + i) == '=' )||
					(*(newIn.text + i) == '(' )||(*(newIn.text + i) == ')')|| (*(newIn.text + i) == '{') ||
					(*(newIn.text + i) == '}' )||( *(newIn.text + i) == '\n' ))&&(!scope))
				{
					if (*(newIn.text + i) == '\n')
					{
						*ptrText = ' ';
						ptrText++;
						*ptrText = *(newIn.text + i);
						ptrText++;
						continue;
					}
					*ptrText = ' ';
					ptrText++;
					*ptrText = *(newIn.text + i);
					ptrText++;
					*ptrText = ' ';
					ptrText++;
					if (!scope) spaceAdded = true;
				}
				else {
					*ptrText = *(newIn.text + i);
					ptrText++;
					 spaceAdded = false;
				}
			}
			else {
				if (scope) {
					*ptrText = ' ';
					ptrText++;
					continue;
				}
				if (!spaceAdded) {
					*ptrText = ' ';
					ptrText++;
					spaceAdded = true;
				}
			}
		}
		*ptrText = '\0';
		spaceAdded = false;
		newIn.textFormated = new unsigned char[strlen((char*)textFormated) + 1];
		ptrText = newIn.textFormated;
		for (int i = 0; i < strlen((char*)textFormated); i++)
		{
			if (textFormated[i] != ' ') {
				*ptrText = textFormated[i];
				ptrText++;
				spaceAdded = false;
			}
			else
			{
				if (!spaceAdded)
				{
					*ptrText = ' ';
					ptrText++;
					spaceAdded = true;
				}
			}
		}
		*ptrText = '\0';
		ptrText = newIn.textFormated;
		long long int counterLexem = 0;
		for (int i = 0; i < strlen((char*)newIn.textFormated); i++)
		{
			if (*ptrText == ' ') counterLexem++;
			ptrText++;
		}
		newIn.counterLexem=counterLexem;
		return newIn;
	}
}		
