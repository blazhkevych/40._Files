/*
	6. �������� ���������, ������� ��������� ����� �� ����� �
������� � ������ ���� ����� �� ����� ������, ���������� ��
� ������� �������� ������� �� ���������. ��� ���� ���
������� ����� ���������� ���������� ����� ��� ���������
� �������� �����.

���� � ��������/��������� ����� ������ ������������ !
3.10.32
�� �������� !!!
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
	FIleStat* arrStruct = new FIleStat[1000];

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
	������� ������� ��������� ���� �������, ���������
	char* buffer_for_stringTest = new char[1000];
	int lenght = _filelength(_fileno(f_read)); // _fileno (�������� ����������), _filelength (���� ������ ����� � ������)
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
	int lenght = _filelength(_fileno(f1)); // _fileno (�������� ����������), _filelength (���� ������ ����� � ������)
	char* bufForDataFile = new char[lenght]; // ����� �� ���� ����
	memset(bufForDataFile, 0, lenght);
	fread(bufForDataFile, sizeof(char), lenght, f1);
	cout << bufForDataFile << endl;





	int i{ 0 };
	while (!feof(f_read))
	{
		fgets(buffer_for_string, 1000, f_read);

		// Establish string and get the first token:
		token = strtok_s(buffer_for_string, seps, &next_token); // "��������" ������ �����, �������� ������� ������
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
			//����� ��������� ������ �� ������� ���� ��� �� ������� ����� �������
		}
	}
	delete[]arrStruct;
	fclose(f_read);
}