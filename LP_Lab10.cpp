#include "pch.h"
#include "Log.h"
#include "Error.h"
#include "CreatingTables.h"
#include "FST.h"
#include "In.h"
#include "IT.h"
#include "LT.h"
#include "Parm.h"
#include "out.h"
int _tmain(int argc, _TCHAR **argv)
{
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		In::IN in = In::getin(parm.in);
		log = Log::getlog(parm.log);
		//Log::WriteLine(log, L"Тест", L" Без ошибок", L"");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		Log::WriteIn(log, in);
		Tables tables = createTables(in);
		printOut(in, parm, tables);
		Log::Close(log);
		
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
	system("pause");
	return 0;
}