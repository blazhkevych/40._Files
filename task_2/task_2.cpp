/*
	2. Написать программу, которая подсчитывает количество
строк и количество слов в текстовом файле.

Путь к входному/выходному файлу задает пользователь !

2:54:35
*/

#include <iostream>
#include <Windows.h>
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
	fopen_s(&f1, filename, "r");
	if (f1 == nullptr)
	{
		perror("Ошибка открытия");
		return 0;
	}

	char ch;
	int word_count = 0, line_count = 0;
	int in_word = 0;
	while ((ch = fgetc(f1)) != EOF)
	{
		if (ch == ' ' || ch == '\t' || ch == '\0' || ch == '\n')
		{
			if (in_word)
			{
				in_word = 0;
				word_count++;
			}

			if (ch = '\0' || ch == '\n')
				line_count++;
		}
		else
			in_word = 1;
	}

	if (in_word == 1)
	{
		word_count++;
		line_count++;
	}

	fclose(f1);
	cout << "Слов в файле: " << word_count << endl;
	cout << "Строк в файле: " << line_count << endl;
	return 0;
}