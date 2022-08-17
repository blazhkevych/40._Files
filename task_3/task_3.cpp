/*
	3. Написать программу, которая сохраняет массив в бинарный
файл, а затем выполняет чтение массива из этого файла.

Путь к входному/выходному файлу задает пользователь !
*/

// ГОТОВО.

#include <iostream>
#include <windows.h>
using namespace std;

struct Student
{
	char name[20];
	char surname[20];
	int age;
	double GPA;
};

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

	Student st[3]
	{
		{"Gilbert", "Baker", 20, 10.3},
		{"Riz", "Ahmed", 21, 8.9},
		{"Antony", "Gott", 22, 11.5}
	};
	char fileNameWrite[MAX_PATH];
	cout << "Введите путь к файлу для записи: ";
	cin.getline(fileNameWrite, MAX_PATH);
	FILE* f_wright{ nullptr };
	fopen_s(&f_wright, fileNameWrite, "wb");
	//for (int i = 0; i < 3; i++)
	fwrite(&st, sizeof(Student), 3, f_wright);
	fclose(f_wright);

	char fileNameRead[MAX_PATH];
	cout << "Введите путь к файлу для чтения: ";
	cin.getline(fileNameRead, MAX_PATH);
	FILE* f_read{ nullptr };
	Student st2[3];
	fopen_s(&f_read, fileNameRead, "rb");
	//for (int i = 0; i < 3; i++)
	fread(&st2, sizeof(Student), 3, f_read);
	fclose(f_read);
	for (int i = 0; i < 3; i++)
		cout << st2[i].name << '\t' << st2[i].surname << '\t' << st2[i].age << '\t' << st2[i].GPA << endl;
}