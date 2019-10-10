#include "pch.h"
#include "Error.h"
namespace Error
{
	// 0-99 системные ошибки
	// 100-109 ошибки параметров
	// 110-119 ошибки открытия файлов
	ERROR errors[ERROR_MAX_ENTRY]
	{
		ERROR_ENTRY(0,"Недопустимый код ошибки"),
		ERROR_ENTRY(1,"Системный сбой"),
		ERROR_ENTRY(2,"Вы пытаетесь превысить размер таблицы лексем"),ERROR_ENTRY(3,"Вы пытаетесь превысить размер таблицы идентификаторов"),ERROR_ENTRY_NODEF(4),
		ERROR_ENTRY(5,"Не найдена парная скобка"),ERROR_ENTRY_NODEF(6),ERROR_ENTRY_NODEF(7),
		ERROR_ENTRY(8,"Отсутствует main"),ERROR_ENTRY(9,"Нераспознанная лексема"),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20),
		ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40),
		ERROR_ENTRY_NODEF10(50), ERROR_ENTRY_NODEF10(60),
		ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80),
		ERROR_ENTRY_NODEF10(90), ERROR_ENTRY(100,"Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104,"Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110,"Ошибка при открытии файла с иходным кодом (-in)"),
		ERROR_ENTRY(111,"Недопустимый символ в исходном коде (-in)"),
		ERROR_ENTRY(112,"Ошибка при создании файла (-log)"),
		ERROR_ENTRY_NODEF(113), ERROR_ENTRY_NODEF(114),
		ERROR_ENTRY_NODEF(115),  ERROR_ENTRY_NODEF(116),
		ERROR_ENTRY_NODEF(117),  ERROR_ENTRY_NODEF(118),
		ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130),
		ERROR_ENTRY_NODEF10(140),ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170),
		ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300),
		ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY_NODEF100(600), ERROR_ENTRY_NODEF100(700),
		ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
	};
		ERROR geterror(int id)
		{
			if (0<id && id < ERROR_MAX_ENTRY)
			{
				return errors[id];
			}
			else return errors[0];

		}
		ERROR geterrorin(int id, int line, int col)
		{
			if (0 < id && id < ERROR_MAX_ENTRY)
			{
				errors[id].inext.line = line;
				errors[id].inext.col = col;
				return errors[id];
			}
			else return errors[0];
		}
};