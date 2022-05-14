﻿/*
	1. Написать программу, которая сохраняет все введенные
пользователем строки в файл. Запись в файл заканчивается,
когда пользователь вводит пустую строку. При каждом
следующем запуске программы файл не создается заново, а
пополняется.

Путь к входному/выходному файлу задает пользователь !

2:25:10
*/
/*
Параметры доступа к файлу.
Тип	Описание
r	Чтение. Файл должен существовать.
w	Запись нового файла. Если файл с таким именем уже существует, то его содержимое будет потеряно.
a	Запись в конец файла. Операции позиционирования (fseek, fsetpos, frewind) игнорируются.
	Файл создаётся, если не существовал.
r+	Чтение и обновление. Можно как читать, так и писать. Файл должен существовать.
w+	Запись и обновление. Создаётся новый файл. Если файл с таким именем уже существует, то его содержимое будет потеряно.
	Можно как писать, так и читать.
a+	Запись в конец и обновление. Операции позиционирования работают только для чтения, для записи игнорируются.
	Если файл не существовал, то будет создан новый.
*/

#include <iostream>
#include <Windows.h>
#include <stdio.h>
using namespace std;

int main()
{
	SetConsoleCP(1251);
	/*
	Задает кодовую страницу ввода, используемую консолью, связанной с вызывающим процессом.
	Консоль использует страницу входного кода для преобразования ввода с клавиатуры
	в соответствующее символьное значение.
	*/
	SetConsoleOutputCP(1251);
	/*
	Задает выходную кодовую страницу, используемую консолью, связанной с вызывающим процессом.
	Консоль использует свою кодовую страницу вывода для преобразования символьных значений,
	записанных различными функциями вывода, в изображения, отображаемые в окне консоли.
	*/

	char filename[MAX_PATH];
	cout << "Введите путь к файлу: ";
	cin.getline(filename, MAX_PATH);
	FILE* f1 = nullptr;
	// "a" Запись в конец файла. Операции позиционирования (fseek, fsetpos, frewind) игнорируются. 
	// Файл создаётся, если не существовал.
	fopen_s(&f1, filename, "a");
	if (f1 == nullptr)
	{
		perror("Error opening");
		return 0;
	}
	cout << "Введите строки для записи в файл: \n";
	while (true)
	{
		char str[100]{ '\0' };
		cin.getline(str, 100);
		if (str[0] == '\0')
		{
			fclose(f1);
			cout << endl;
			return 0;
		}
		fputs(str, f1);
		fputs("\n", f1); // каждая введенная строка с новой строки
	}
	fclose(f1);

	cout << endl;
	return 0;
}