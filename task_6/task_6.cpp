/*
	6. Написать программу, которая считывает текст из файла и
выводит в другой файл слова из этого текста, расположив их
в порядке убывания частоты их появления. При этом для
каждого слова необходимо напечатать число его появлений
в исходном файле.

Путь к входному/выходному файлу задает пользователь !
3.10.32
*/

// ГОТОВО

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

class Word
{
public:
	string word{};
	int count{ 1 };
	void Print()
	{
		cout << setw(20) << this->word << setw(10) << this->count << endl;
	}
};

void WriteWords(ostream& o, const  vector<Word*>& words)
{
	for (auto s : words) {
		o << s->word << " - " << s->count << '\n';
	}
}
void WriteWords(ostream&& o, const  vector<Word*>& words)
{
	WriteWords(o, words);
}

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

	cout << "Введите путь к исходному файлу: "; // 1.txt
	string fileName{};
	cin >> fileName;

	ifstream f_read(fileName, ios::in);

	if (!f_read.is_open()) // Если открытие файла завершилось неудачей - выходим.
	{
		cout << "Error!\n";
		return 0;
	}

	f_read.seekg(0, ios::end); // Смещение файлового указателя на 0 от конца.
	long long sourceFileSize = f_read.tellg(); // Размер исходного файла.
	f_read.seekg(0, ios::beg); // Смещение файлового указателя на 0 от начала.

	string str{ istreambuf_iterator<char>(f_read), istreambuf_iterator<char>() }; // Вычитываем весь текстовый файл.

	// Привести все буквы один регистр верхний или нижний.
	transform(str.begin(), str.end(), str.begin(), tolower);

	vector<Word*> Words;
	stringstream ss(str);
	string buf;

	while (ss >> buf)
	{
		int found = buf.find_first_of(" ./*-+~!@#$%^&*()_+`1234567890-=|\\{}[]:\";',./<>?");
		while (found >= 0)
		{
			buf.erase(found, 1);
			found = buf.find_first_of(" ./*-+~!@#$%^&*()_+`1234567890-=|\\{}[]:\";',./<>?");
		}
		if (!buf.empty())
		{
			int cap = Words.size();
			bool coincidence{ false }; // Совпадение.
			for (int i = 0; i < cap; i++)
			{
				if (Words[i]->word == buf) // Входящее слово совпало с словом из списка.
				{
					Words[i]->count++;
					coincidence = true;
				}
			}
			if (coincidence == false) // Если совпадений не было, добавляем.
			{
				//Word* w = new Word{ buf };
				Words.push_back(new Word{ buf });
			}
		}
	}

	// Сортировка вектора.
	for (int startIndex = 0; startIndex < Words.size(); ++startIndex)
	{
		int biggerIndex = startIndex;

		for (int currentIndex = startIndex + 1; currentIndex < Words.size(); ++currentIndex)
		{
			if (Words[currentIndex]->count > Words[biggerIndex]->count) // Сортировка по убыванию
				biggerIndex = currentIndex;
		}

		Word* temp = Words[startIndex];
		Words[startIndex] = Words[biggerIndex];
		Words[biggerIndex] = temp;
	}

	cout << "\tСлово\t" << "Число появлений" << endl;
	for (int i = 0; i < Words.size(); i++)
		Words[i]->Print();

	cout << "Введите путь к результирующему файлу: "; // 2.txt
	string resultFilePath;
	cin >> resultFilePath;

	// Создаём выходной файловый поток и присоединяем к нему файл, который открывается на запись в текстовом режиме.
	ofstream out;
	out.open(resultFilePath, ios::out | ios::trunc);

	WriteWords(out, Words);
}