#include "pch.h"
#include "out.h"
#include "In.h"
#include "Parm.h"
#include "LT.h"
#include "IT.h"
#include "CreatingTables.h"
using namespace std;
void printOut(In::IN input, Parm::PARM parm, Tables 
	tables)
{
	ofstream fout;
	fout.open("input.out");
	fout << "---содержимое таблицы лексем---" << endl;
		fout << tables.LEXTABLE->LexemText;
		fout << endl;
		for (int i = 0; i < (tables.LEXTABLE->size); i++)
			fout << "Лексема: " << (tables.LEXTABLE->table[i].lexema)
			<< " расположена на  " << tables.LEXTABLE->table[i].sn << " строке." <<
			"В таблице лексем : " << tables.LEXTABLE->table[i].idxTI << endl;;

		fout << endl << endl << endl << "--------Cодержимое таблицы идентификаторов в соответствии с её первоначальным представлением:" << endl << endl << endl;
		for (int i = 0; i < tables.IDTABLE->size; i++)
		{
			fout << "Идентификатор: " << tables.IDTABLE->table[i].id << " Тип(переменная, функция, параметр, лексема): " << tables.IDTABLE->table[i].idtype
				<< " Тип данных: " << tables.IDTABLE->table[i].iddatatype << " Значение: ";
			if ((int)tables.IDTABLE->table[i].iddatatype == 1) fout << tables.IDTABLE->table[i].value.vint;
			else fout << tables.IDTABLE->table[i].value.vstr->str;
			fout << " Номер первого вхождения: " << tables.IDTABLE->table[i].idxfirstLE << endl << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

		}
}





























																																																													/*fout << "--------Cодержимое таблицы лексем в соответствии с образцом:" << endl << endl << endl
																																																														<< tables.LEXTABLE->LexemText << endl<<endl<<endl
																																																														<< "--------Cодержимое таблицы лексем в соответствии с её первоначальным представлением:" << endl<<endl<<endl;
																																																													for (int i = 0; i < tables.LEXTABLE->size; i++)
																																																													{
																																																														fout << "Лексема: " << tables.LEXTABLE->table[i].lexema << " Номер строки: "
																																																															<< tables.LEXTABLE->table[i].sn << " Номер в таблице идентификаторов : "
																																																															<< tables.LEXTABLE->table[i].idxTI << endl << "-----------------------------------------------------------------------" << endl;
																																																													}
																																																													fout << endl<<endl<<endl<<"--------Cодержимое таблицы идентификаторов в соответствии с её первоначальным представлением:" << endl<<endl<<endl;
																																																													for (int i = 0; i < tables.IDTABLE->size; i++)
																																																													{
																																																														fout << "Идентификатор: " << tables.IDTABLE->table[i].id << " Тип(переменная, функция, параметр, лексема): " << tables.IDTABLE->table[i].idtype
																																																															<< " Тип данных: " << tables.IDTABLE->table[i].iddatatype << " Значение: ";
																																																														if ((int)tables.IDTABLE->table[i].iddatatype == 1) fout << tables.IDTABLE->table[i].value.vint;
																																																														else fout << tables.IDTABLE->table[i].value.vstr->str;
																																																														fout << " Номер первого вхождения: " << tables.IDTABLE->table[i].idxfirstLE << endl << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
																																																													}*/



		


