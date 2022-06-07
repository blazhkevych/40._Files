/*
	5. Написать программу, выполняющую шифрование и
дешифрование текстового файла с заданным ключом,
используя оператор ^ (поразрядное исключающее или).

Путь к входному/выходному файлу задает пользователь !

НЕ РАБОТАЕТ !!!

3.04.48
*/

#include <iostream>
#include <windows.h>
#include <io.h>

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

	char fileNameRead[MAX_PATH];
	cout << "Введите путь к файлу для шифрования: ";
	cin.getline(fileNameRead, MAX_PATH);
	FILE* f_read{ nullptr };
	fopen_s(&f_read, fileNameRead, "r");
	int fileLength = _filelength(_fileno(f_read)); // _fileno (получает дескриптор), _filelength (дает размер файла в байтах)
	char* bufferForFile = new char[fileLength]; 
	char key ;
	cout << "Введите ключ для шифрования: ";
	cin>>key;
	for (int i = 0; i < fileLength; i++)
	{
		for (size_t j = 0; j < sizeof(key); j++)
		{
			bufferForFile[i] = bufferForFile[i] ^ key[j];
			i++;
		}
	}



	delete[]bufferForFile;
}