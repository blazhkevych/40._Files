/*
	4. Написать программу, которая разбивает файл на кусочки
указанного размера, а затем создает копию исходного файла
из этих кусков.

Путь к входному/выходному файлу задает пользователь !

2.57.15
*/

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <io.h>
using namespace std;

// Делит, в бинарном режиме, любой файл на кусочки (размер, куска в байтах задает пользователь) 
// и возвращает размер файла в байтах
unsigned long int CutFileIntoPieces(const char* filename, int onePieceSizeInBytes)
{
	FILE* f1 = nullptr;
	fopen_s(&f1, filename, "rb");
	if (f1 == nullptr)
	{
		perror("Error opening");
		return 0;
	}
	int lenght = _filelength(_fileno(f1)); // _fileno (получает дескриптор), _filelength (дает размер файла в байтах)
	char* bufForDataPiece = new char[onePieceSizeInBytes]; // буфер на 1 кусочек
	memset(bufForDataPiece, 0, onePieceSizeInBytes);
	char bufferFileName[20];
	FILE* f2 = nullptr;
	for (int i = 0; i < lenght / onePieceSizeInBytes + 1; i++)
	{
		snprintf(bufferFileName, sizeof(bufferFileName), "file_%d.bin", i);
		fopen_s(&f2, bufferFileName, "wb");
		int read = fread(bufForDataPiece, sizeof(char), onePieceSizeInBytes, f1);
		fwrite(bufForDataPiece, sizeof(char), read, f2);
		fclose(f2);
	}
	delete[]bufForDataPiece;
	fclose(f1);

	return lenght;
}

// Собирает, в бинарном режиме, файл из кусочков
void CollectFileFromPieces(const char* fileNameResult, int fileSize, int partSize)
{
	FILE* fp_read = nullptr;
	char partName[20]; // имя кусочка
	char* buffer = new char[partSize]; // память под результирующий файл в размере заданной части файла
	memset(buffer, 0, partSize); // обуляем буфер в заданном размере части файла
	FILE* fp_write = nullptr; // создаем указатель на результирующий файл (составленный из частей)
	fopen_s(&fp_write, fileNameResult, "wb"); // открываем результирующий файл для записи
	for (int i = 0; i < fileSize / partSize + 1; i++)
	{
		snprintf(partName, sizeof(partName), "file_%d.bin", i); // формируем имя части файла по шаблону
		fopen_s(&fp_read, partName, "rb"); // открываем "файл-часть" под сформированным именем по шаблону
		int read = fread(buffer, sizeof(char), partSize, fp_read); // считываем "sizeof(char) на partSize" байт в буфер из "файла-части" 
		fwrite(buffer, sizeof(char), read, fp_write); // пишем из буфера "sizeof(char) на partSize" байт в поток fp_write
		fclose(fp_read); // закрываем открытый "файл-часть"
	}
	delete[]buffer;
	fclose(fp_write);
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

	char filename[MAX_PATH];
	char fileNameResult[MAX_PATH];
	cout << "Введите путь к исходному файлу: ";
	cin.getline(filename, MAX_PATH);
	cout << "Введите размер 1 кусочка в байтах: ";
	int  onePieceSizeInBytes{ 0 };
	cin >> onePieceSizeInBytes;
	int fileSize = CutFileIntoPieces(filename, onePieceSizeInBytes);
	cout << flush;
	cin.get();
	cout << "Введите путь к результирующему файлу : ";
	cin.getline(fileNameResult, MAX_PATH);
	CollectFileFromPieces(fileNameResult, fileSize, onePieceSizeInBytes);
}