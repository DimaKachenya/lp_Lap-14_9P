#include "pch.h"
#include "FST.h"
#include "LT.h"
#include "IT.h"
#include "In.h"
#include "CreatingTables.h"
#include "Error.h"
using namespace fst;
using namespace std;
using namespace LT;
int counterLexemInProgram = 0; //отвечает за номер лексемы в исходном коде программы
bool haveMain = false;

char* stringToChar(string str) {
	char* massChar = new char[255];
	for (int i = 0; i < str.length(); i++) {
		massChar[i] = str[i];
	}
	massChar[str.length()] = '\0';
	return massChar;
}
Entry createStructLexem(char type, int number, int numberInTableId) {
	Entry newLexem;
	newLexem.lexema = type;
	newLexem.sn = number;
	newLexem.idxTI = numberInTableId;
	return newLexem;

}
IT::Entry createStructId(char* id, int line, int*typeData, int*typeID, char lexema[TI_STR_MAXSIZE] = NULL) {
	IT::Entry newItEntry;
	int counterSymbol = 0;
	for (int i = 0; (i < strlen(id)) && (i < ID_MAXSIZE - 1); i++)
	{
		newItEntry.id[i] = id[i];
		counterSymbol++;
	}
	newItEntry.id[counterSymbol] = '\0';
	newItEntry.iddatatype = (IT::IDDATATYPE)*typeData;
	newItEntry.idtype = (IT::IDTYPE)*typeID;
	newItEntry.idxfirstLE = line;
	if ((int)newItEntry.idtype != 4) {
		if ((int)newItEntry.iddatatype == 1)
		{
			newItEntry.value.vint = TI_INT_DEFAULT;
		}
		else
		{
			newItEntry.value.vstr->len = 0;
			newItEntry.value.vstr->str[0] = TI_STR_DEFAULT;
			newItEntry.value.vstr->str[1] = '\0';
		}
	}
	else
	{
		if ((int)newItEntry.iddatatype == 1)
		{
			newItEntry.value.vint = atoi(lexema);
		}
		else
		{
			newItEntry.value.vstr->len = strlen(lexema);
			strcpy_s(newItEntry.value.vstr->str, lexema);
		}
	}
	return newItEntry;
}

void initTypeLexem(const char* text, string tmp, LexTable* tableOfLexem, int numberOfstring, int poz, IT::IdTable* newIdTable, int*typeData, int*typeID)
{
	FST fstInteger(text, 8,
		NODE(1, RELATION('i', 1)),
		NODE(1, RELATION('n', 2)),
		NODE(1, RELATION('t', 3)),
		NODE(1, RELATION('e', 4)),
		NODE(1, RELATION('g', 5)),
		NODE(1, RELATION('e', 6)),
		NODE(1, RELATION('r', 7)),
		NODE());
	FST fstString(text, 7,
		NODE(1, RELATION('s', 1)),
		NODE(1, RELATION('t', 2)),
		NODE(1, RELATION('r', 3)),
		NODE(1, RELATION('i', 4)),
		NODE(1, RELATION('n', 5)),
		NODE(1, RELATION('g', 6)),
		NODE());
	FST fstFunction(text, 9,
		NODE(1, RELATION('f', 1)),
		NODE(1, RELATION('u', 2)),
		NODE(1, RELATION('n', 3)),
		NODE(1, RELATION('c', 4)),
		NODE(1, RELATION('t', 5)),
		NODE(1, RELATION('i', 6)),
		NODE(1, RELATION('o', 7)),
		NODE(1, RELATION('n', 8)),
		NODE()
	);
	FST fstDeclare(text, 8,
		NODE(1, RELATION('d', 1)),
		NODE(1, RELATION('e', 2)),
		NODE(1, RELATION('c', 3)),
		NODE(1, RELATION('l', 4)),
		NODE(1, RELATION('a', 5)),
		NODE(1, RELATION('r', 6)),
		NODE(1, RELATION('e', 7)),
		NODE()
	);
	FST fstReturn(text, 7,
		NODE(1, RELATION('r', 1)),
		NODE(1, RELATION('e', 2)),
		NODE(1, RELATION('t', 3)),
		NODE(1, RELATION('u', 4)),
		NODE(1, RELATION('r', 5)),
		NODE(1, RELATION('n', 6)),
		NODE()
	);
	FST fstPrint(text, 6,
		NODE(1, RELATION('p', 1)),
		NODE(1, RELATION('r', 2)),
		NODE(1, RELATION('i', 3)),
		NODE(1, RELATION('n', 4)),
		NODE(1, RELATION('t', 5)),
		NODE()
	);
	FST fstMain(text, 5,
		NODE(1, RELATION('m', 1)),
		NODE(1, RELATION('a', 2)),
		NODE(1, RELATION('i', 3)),
		NODE(1, RELATION('n', 4)),
		NODE()
	);
	FST fstSemicolon(text, 2,
		NODE(1, RELATION(';', 1)),
		NODE()
	);
	FST fstComma(text, 2,
		NODE(1, RELATION(',', 1)),
		NODE()
	);
	FST fstLeftbrace(text, 2,
		NODE(1, RELATION('{', 1)),
		NODE()
	);
	FST fstBracelet(text, 2,
		NODE(1, RELATION('}', 1)),
		NODE()
	);
	FST fstLefthesis(text, 2,
		NODE(1, RELATION('(', 1)),
		NODE()
	);
	FST fstRighthesis(text, 2,
		NODE(1, RELATION(')', 1)),
		NODE()
	);
	FST fstPlus(text, 2,
		NODE(1, RELATION('+', 1)),
		NODE()
	);
	FST fstMinus(text, 2,
		NODE(1, RELATION('-', 1)),
		NODE()
	);
	FST fstStar(text, 2,
		NODE(1, RELATION('*', 1)),
		NODE()
	);
	FST fstDirslash(text, 2,
		NODE(1, RELATION('/', 1)),
		NODE()
	);
	FST fstLiteralOfInteger(text, 2,
		NODE(20, RELATION('0', 0), RELATION('1', 0), RELATION('2', 0), RELATION('3', 0), RELATION('4', 0), RELATION('5', 0), RELATION('6', 0),
			RELATION('7', 0), RELATION('8', 0), RELATION('9', 0),
			RELATION('0', 1), RELATION('1', 1), RELATION('2', 1), RELATION('3', 1), RELATION('4', 1), RELATION('5', 1), RELATION('6', 1),
			RELATION('7', 1), RELATION('8', 1), RELATION('9', 1)),
		NODE()
	);
	FST fstId(text, 2,
		NODE(52, RELATION('a', 0), RELATION('b', 0), RELATION('c', 0), RELATION('d', 0), RELATION('e', 0),
			RELATION('f', 0), RELATION('g', 0), RELATION('h', 0), RELATION('i', 0), RELATION('j', 0), RELATION('k', 0),
			RELATION('l', 0), RELATION('m', 0), RELATION('n', 0), RELATION('o', 0), RELATION('p', 0), RELATION('q', 0),
			RELATION('r', 0), RELATION('s', 0), RELATION('t', 0), RELATION('u', 0), RELATION('v', 0), RELATION('w', 0),
			RELATION('x', 0), RELATION('y', 0), RELATION('z', 0),
			RELATION('a', 1), RELATION('b', 1), RELATION('c', 1), RELATION('d', 1), RELATION('e', 1),
			RELATION('f', 1), RELATION('g', 1), RELATION('h', 1), RELATION('i', 1), RELATION('j', 1), RELATION('k', 1),
			RELATION('l', 1), RELATION('m', 1), RELATION('n', 1), RELATION('o', 1), RELATION('p', 1), RELATION('q', 1),
			RELATION('r', 1), RELATION('s', 1), RELATION('t', 1), RELATION('u', 1), RELATION('v', 1), RELATION('w', 1),
			RELATION('x', 1), RELATION('y', 1), RELATION('z', 1)),
		NODE()
	);
	FST fstEqual(text, 2,
		NODE(1, RELATION('=', 1)),
		NODE());
	
	FST fstLiteralOfString(text, 3,
		NODE(1, RELATION('\'', 1)),
		NODE(71, 
			RELATION('\'', 2), RELATION('a', 1),RELATION('b',1), RELATION('c', 1), RELATION('d', 1), 
			RELATION('e', 1), RELATION('f', 1), RELATION('g', 1), RELATION('h', 1), RELATION('i', 1), RELATION('j', 1),
			RELATION('k', 1), RELATION('l', 1), RELATION('m', 1), RELATION('n', 1), RELATION('o', 1), RELATION('p', 1), 
			RELATION('q', 1), RELATION('r', 1), RELATION('s', 1), RELATION('t', 1), RELATION('u', 1), RELATION('v', 1), 
			RELATION('w', 1), RELATION('x', 1), RELATION('y', 1), RELATION('z', 1), RELATION('0', 1), RELATION('1', 1),
			RELATION('2', 1), RELATION('3', 1), RELATION('4', 1), RELATION('5', 1), RELATION('6', 1), RELATION('7', 1),
			RELATION('8', 1), RELATION('9', 1), RELATION('а', 1), RELATION('б', 1), RELATION('в', 1), RELATION('г', 1),
			RELATION('д', 1), RELATION('е', 1), RELATION('ё', 1), RELATION('ж', 1), RELATION('з', 1), RELATION('и', 1),
			RELATION('й', 1), RELATION('к', 1), RELATION('л', 1), RELATION('м', 1), RELATION('н', 1), RELATION('о', 1),
			RELATION('п', 1), RELATION('р', 1), RELATION('с', 1), RELATION('т', 1), RELATION('у', 1), RELATION('ф', 1),
			RELATION('х', 1), RELATION('ц', 1), RELATION('ч', 1), RELATION('ш', 1), RELATION('щ', 1), RELATION('ъ', 1),
			RELATION('ы', 1), RELATION('ь', 1), RELATION('э', 1), RELATION('ю', 1), RELATION('я', 1), RELATION(' ', 1)
			),
		NODE()
	);
	if (execute(fstInteger)) {
		Add(tableOfLexem, createStructLexem(LEX_INTEGER, numberOfstring, LT_TI_NULLIDX));
		*typeData = 1;
		return;
	}
	if (execute(fstString)) {
		Add(tableOfLexem, createStructLexem(LEX_STRING, numberOfstring, LT_TI_NULLIDX));
		*typeData = 2;
		return;
	}
	if (execute(fstFunction)) {
		Add(tableOfLexem, createStructLexem(LEX_FUNCTION, numberOfstring, LT_TI_NULLIDX));
		*typeID = 2;
		return;
	}
	if (execute(fstDeclare)) {
		Add(tableOfLexem, createStructLexem(LEX_DECLARE, numberOfstring, LT_TI_NULLIDX));
		*typeID = 1;
		return;
	}
	if (execute(fstReturn)) {
		Add(tableOfLexem, createStructLexem(LEX_RETURN, numberOfstring, LT_TI_NULLIDX));
		return;
	}
	if (execute(fstPrint)) {
		Add(tableOfLexem, createStructLexem(LEX_PRINT, numberOfstring, LT_TI_NULLIDX));
		return;
	}
	if (execute(fstMain)) {
		Add(tableOfLexem, createStructLexem(LEX_MAIN, numberOfstring, LT_TI_NULLIDX));
		haveMain = true;
		return;
	}
	if (execute(fstSemicolon)) {
		Add(tableOfLexem, createStructLexem(LEX_SEMICOLON, numberOfstring, LT_TI_NULLIDX));
		return;
	}
	if (execute(fstComma)) {
		Add(tableOfLexem, createStructLexem(LEX_COMMA, numberOfstring, LT_TI_NULLIDX));
		return;
	}
	if (execute(fstLeftbrace)) {
		Add(tableOfLexem, createStructLexem(LEX_LEFTBRACE, numberOfstring, LT_TI_NULLIDX));
		return;
	}
	if (execute(fstBracelet)) {
		Add(tableOfLexem, createStructLexem(LEX_BRACELET, numberOfstring, LT_TI_NULLIDX));
		return;
	}
	if (execute(fstLefthesis)) {
		Add(tableOfLexem, createStructLexem(LEX_LEFTHESIS, numberOfstring, LT_TI_NULLIDX));
		if (*(typeID) == 2) *typeID = 3;
		return;
	}
	if (execute(fstRighthesis)) {
		Add(tableOfLexem, createStructLexem(LEX_RIGHTHESIS, numberOfstring, LT_TI_NULLIDX));
		if (*typeID == 3) *typeID = -1;
		return;
	}
	if (execute(fstPlus)) {
		Add(tableOfLexem, createStructLexem(LEX_PLUS, numberOfstring, LT_TI_NULLIDX));
		return;
	}
	if (execute(fstMinus)) {
		Add(tableOfLexem, createStructLexem(LEX_MINUS, numberOfstring, LT_TI_NULLIDX));
		return;
	}
	if (execute(fstStar)) {
		Add(tableOfLexem, createStructLexem(LEX_STAR, numberOfstring, LT_TI_NULLIDX));
		return;
	}
	if (execute(fstEqual)) {
		Add(tableOfLexem, createStructLexem(LEX_EQUAL, numberOfstring, LT_TI_NULLIDX));
		return;
	}
	if (execute(fstDirslash)) {
		Add(tableOfLexem, createStructLexem(LEX_DIRSLASH, numberOfstring, LT_TI_NULLIDX));
		return;
	}
	if (execute(fstLiteralOfInteger)) {
		int*t = new int;//всегда хранит единицу необходим для корректной передачи данных в функцию
		int*t2 = new int;//всегда хранит 4 необходим для корректной передачи данных в функцию
		*t = 1;
		*t2 = 4;
		char numberLi[20];
		_itoa_s(counterLexemInProgram, numberLi, 10);
		IT::Entry newEntry = createStructId(numberLi, numberOfstring, t, t2, (char*)text);
		IT::Add(newIdTable, newEntry);
		for (int i = 0; i < newIdTable->size; i++)//Добавляем в таблицу лексем, сопоставляя таблицу идентификаторов
		{
			if (!strcmp(newEntry.id, newIdTable->table[i].id)) 	Add(tableOfLexem, createStructLexem(LEX_LITERAL, numberOfstring, i));
		}
		counterLexemInProgram++;
		delete t;
		delete t2;
		return;
	}
	if (execute(fstLiteralOfString)) {
		int*t = new int;//всегда хранит двойку необходим для корректной передачи данных в функцию
		int*t2 = new int;//всегда хранит 4 необходим для корректной передачи данных в функцию
		*t = 2;
		*t2 = 4;
		char numberLi[20];
		_itoa_s(counterLexemInProgram, numberLi, 10);
		IT::Entry newEntry = createStructId(numberLi, numberOfstring, t, t2, (char*)text);
		IT::Add(newIdTable, newEntry);
		for (int i = 0; i < newIdTable->size; i++)//Добавляем в таблицу лексем, сопоставляя таблицу идентификаторов
		{
			if (!strcmp(newEntry.id, newIdTable->table[i].id)) 	Add(tableOfLexem, createStructLexem(LEX_LITERAL, numberOfstring, i));
		}
		counterLexemInProgram++;
		delete t;
		delete t2;
		return;
	}
	if (execute(fstId)) {
		IT::Entry newEntry = createStructId((char*)text, numberOfstring, typeData, typeID);
		bool idInTable = false; //отвечает за то, есть ли такой идентификатор в таблице идентификаторов
		int numberInTableID = 0;
		for (int i = 0; i < newIdTable->size; i++)
		{
			if (!strcmp(newEntry.id, newIdTable->table[i].id)) idInTable = true;
		}
		if (!idInTable) {
			IT::Add(newIdTable, newEntry);
		}//если такого идентификатора в таблице не было, то добавляем
		for (int i = 0; i < newIdTable->size; i++)//Добавляем в таблицу лексем, сопоставляя таблицу идентификаторов
		{
			if (!strcmp(newEntry.id, newIdTable->table[i].id)) 	Add(tableOfLexem, createStructLexem(LEX_ID, numberOfstring, i));
		}
		return;
	}
 throw ERROR_THROW_IN(9, numberOfstring, poz);

}

Tables createTables(In::IN newIN) //создаем таблицу лексем
{
	int* typeData = new int; //1-integer 2-string; -1--не определена
	int* typeID = new int; //1-переменная 2-функция 3- параметр 4-литерал -1 не определена	
	*typeData = -1;
	*typeID = -1;
	unsigned char* input = newIN.textFormated;
	string currentString;
	int indOfFirstSpace = 0;
	bool isFirstSpaceDetected = false;
	int numberSymbol = -1; //отвечает за номер символа в текущей строке
	bool scope = false;
	LexTable* newTable = Create(newIN.counterLexem);
	IT::IdTable* newIdTable = IT::Create(newIN.counterLexem);
	ListId* newListId = new ListId;
	ListId* pHeadListId = NULL;
	int numberOfString = 0;
	int counterLexem = 0;
	for (int i = 0; i < strlen((char*)input); i++) {
		if (input[i] != '\n')
		{
			numberSymbol++;
			currentString = currentString + (char)input[i];
			if (!isFirstSpaceDetected) if (input[i] == ' ') {
				indOfFirstSpace = numberSymbol;
				isFirstSpaceDetected = true;
			}
		}
		else
		{
			numberOfString++;
			string currentLexem;
			for (int j = indOfFirstSpace + 1; j < currentString.length(); j++)
			{
				if (currentString[j] == '\'') {
					if (!scope)	scope = true;
					else scope = false;
				}
				if ((currentString[j] != ' ')) currentLexem = currentLexem + currentString[j];
				else {
					if (scope) currentLexem = currentLexem + currentString[j];
					else {
						initTypeLexem(stringToChar(currentLexem), currentString, newTable, numberOfString, (j-indOfFirstSpace-currentLexem.length()), newIdTable, typeData, typeID);
						counterLexem++;
						currentLexem.clear();
					}

				}


			}

			currentString.clear();
			indOfFirstSpace = 0;
			isFirstSpaceDetected = false;
			numberSymbol = -1;

		}
	}
	newTable->LexemText = new unsigned char[counterLexem * 3 + 10];
	unsigned char* LexemText = newTable->LexemText;
	numberOfString = newTable->table->sn;
	int currentNumberString = 1;
	*LexemText = '0';
	LexemText++;
	*LexemText = '1';
	LexemText++;
	*LexemText = ' ';
	LexemText++;
	for (int i = 0; i < newTable->size; i++)
	{
		if (currentNumberString == newTable->table[i].sn)
		{
			*LexemText = newTable->table[i].lexema;
			LexemText++;

		}
		else
		{
			currentNumberString = newTable->table[i].sn;
			*LexemText = '\n';
			LexemText++;
			if (currentNumberString < 10)
			{
				*LexemText = '0';
				LexemText++;
				char str[2];
				_itoa_s(currentNumberString, str, 10);
				*LexemText = str[0];
				LexemText++;
				*LexemText = ' ';
				LexemText++;

			}
			else {
				char str[100];
				_itoa_s(currentNumberString, str, 10);
				for (int j = 0; j < strlen(str); j++)
				{
					*LexemText = str[j];
					LexemText++;

				}
				*LexemText = ' ';
				LexemText++;
			}
			*LexemText = newTable->table[i].lexema;
			LexemText++;

		}
	}
	*LexemText = '\0';
	Tables newTables;
	newTables.IDTABLE = newIdTable;
	newTables.LEXTABLE = newTable;
	LexemText = newTables.LEXTABLE->LexemText;
	int l = 1, c = 1;
	int counterScope=0;
	int counterFigureScope = 0;
	for (int i = 0; i < strlen((char*)newTables.LEXTABLE->LexemText); i++)
	{
		if (LexemText[i] == '\n')
		{
			l++;
			c = 1;
		}
		if (LexemText[i] == '{') counterFigureScope++;
		if (LexemText[i] == '}')
		{
			if (counterFigureScope<= 0) throw ERROR_THROW_IN(5, l, c);
			counterFigureScope--;
		}
		if (LexemText[i] == '(') counterScope++;
		if (LexemText[i] == ')')
		{
			if (counterScope <= 0) throw ERROR_THROW_IN(5, l, c);
			counterScope--;
		}
		c++;
		LexemText++;
	}
	if ((counterScope != 0)||(counterFigureScope!=0)) ERROR_THROW(5);
		if (!haveMain) throw ERROR_THROW(8);
			return newTables;
}