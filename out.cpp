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
	fout << "---���������� ������� ������---" << endl;
		fout << tables.LEXTABLE->LexemText;
		fout << endl;
		for (int i = 0; i < (tables.LEXTABLE->size); i++)
			fout << "�������: " << (tables.LEXTABLE->table[i].lexema)
			<< " ����������� ��  " << tables.LEXTABLE->table[i].sn << " ������." <<
			"� ������� ������ : " << tables.LEXTABLE->table[i].idxTI << endl;;

		fout << endl << endl << endl << "--------C��������� ������� ��������������� � ������������ � � �������������� ��������������:" << endl << endl << endl;
		for (int i = 0; i < tables.IDTABLE->size; i++)
		{
			fout << "�������������: " << tables.IDTABLE->table[i].id << " ���(����������, �������, ��������, �������): " << tables.IDTABLE->table[i].idtype
				<< " ��� ������: " << tables.IDTABLE->table[i].iddatatype << " ��������: ";
			if ((int)tables.IDTABLE->table[i].iddatatype == 1) fout << tables.IDTABLE->table[i].value.vint;
			else fout << tables.IDTABLE->table[i].value.vstr->str;
			fout << " ����� ������� ���������: " << tables.IDTABLE->table[i].idxfirstLE << endl << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

		}
}





























																																																													/*fout << "--------C��������� ������� ������ � ������������ � ��������:" << endl << endl << endl
																																																														<< tables.LEXTABLE->LexemText << endl<<endl<<endl
																																																														<< "--------C��������� ������� ������ � ������������ � � �������������� ��������������:" << endl<<endl<<endl;
																																																													for (int i = 0; i < tables.LEXTABLE->size; i++)
																																																													{
																																																														fout << "�������: " << tables.LEXTABLE->table[i].lexema << " ����� ������: "
																																																															<< tables.LEXTABLE->table[i].sn << " ����� � ������� ��������������� : "
																																																															<< tables.LEXTABLE->table[i].idxTI << endl << "-----------------------------------------------------------------------" << endl;
																																																													}
																																																													fout << endl<<endl<<endl<<"--------C��������� ������� ��������������� � ������������ � � �������������� ��������������:" << endl<<endl<<endl;
																																																													for (int i = 0; i < tables.IDTABLE->size; i++)
																																																													{
																																																														fout << "�������������: " << tables.IDTABLE->table[i].id << " ���(����������, �������, ��������, �������): " << tables.IDTABLE->table[i].idtype
																																																															<< " ��� ������: " << tables.IDTABLE->table[i].iddatatype << " ��������: ";
																																																														if ((int)tables.IDTABLE->table[i].iddatatype == 1) fout << tables.IDTABLE->table[i].value.vint;
																																																														else fout << tables.IDTABLE->table[i].value.vstr->str;
																																																														fout << " ����� ������� ���������: " << tables.IDTABLE->table[i].idxfirstLE << endl << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
																																																													}*/



		


