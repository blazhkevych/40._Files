/*
	6. Написать программу, которая считывает текст из файла и
выводит в другой файл слова из этого текста, расположив их
в порядке убывания частоты их появления. При этом для
каждого слова необходимо напечатать число его появлений
в исходном файле.

Путь к входному/выходному файлу задает пользователь !
3.10.32
НЕ РАБОТАЕТ !!!
*/

#include <iostream>
#include <windows.h>
#include <io.h>
using namespace std;

void RussianMessage(const char* str)
{
	char* p = new char[strlen(str) + 1];
	CharToOemA(str, p);
	cout << p;
	delete[] p;
}

struct FIleStat
{
	char* word{ nullptr };
	int* count{ nullptr };

}*fileStat;

int main()
{
	FIleStat* arrFileStat = new FIleStat[1000];

	char fileNameRead[MAX_PATH];
	cout << "Enter path name: ";
	cin.getline(fileNameRead, MAX_PATH);
	FILE* f_read{ nullptr };
	fopen_s(&f_read, fileNameRead, "r");
	if (f_read == nullptr)
	{
		perror("Error opening");
		return 0;
	}
	char buffer_for_string[1000];
	char* words[1000]{ nullptr };
	char seps[] = " ,\t\n";
	char* token = nullptr;
	char* next_token = nullptr;



	/*
	Попытка сичтать текстовый файл целиком, построчно
	char* buffer_for_stringTest = new char[1000];
	int lenght = _filelength(_fileno(f_read)); // _fileno (получает дескриптор), _filelength (дает размер файла в байтах)
	char* bufForAllFIle = new char[lenght];
	memset(bufForAllFIle, 0, lenght);
	while (!feof(f_read))
	{
		fgets(buffer_for_stringTest, 1000, f_read);
		strcat_s(bufForAllFIle,strlen(buffer_for_stringTest)+1, buffer_for_stringTest);
	}
	*/
	FILE* f1 = nullptr;
	fopen_s(&f1, fileNameRead, "rb");
	if (f1 == nullptr)
	{
		perror("Error opening");
		return 0;
	}
	int lenght = _filelength(_fileno(f1)); // _fileno (получает дескриптор), _filelength (дает размер файла в байтах)
	char* bufForDataFile = new char[lenght]; // буфер на весь файл
	memset(bufForDataFile, 0, lenght);
	fread(bufForDataFile, sizeof(char), lenght, f1);
	cout << bufForDataFile << endl;





	int i{ 0 };
	while (!feof(f_read))
	{
		fgets(buffer_for_string, 1000, f_read);

		// Establish string and get the first token:
		token = strtok_s(buffer_for_string, seps, &next_token); // "вырезаем" первое слово, передаем остаток дальше
		words[i] = token;
		i++;
		// While there are tokens in "string1" or "string2"
		while (token != nullptr)
		{
			// Get next token:
			if (token != nullptr)
			{
				token = strtok_s(nullptr, seps, &next_token);
				if (token) {
					words[i] = token;
					i++;

				}
			}
		}
		//место обработки данных из массива пока его не затерли новой строкой
		for (int i = 0; i < strlen(buffer_for_string) + 1; i++)
		{
			for (int j = 1; j < strlen(buffer_for_string) + 1; j++)
			{
				words
			}
		}
	}
	delete[]arrFileStat;
	fclose(f_read);
}