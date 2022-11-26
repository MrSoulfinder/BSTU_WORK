#include <iostream>
#include <cstdio>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

struct table
{
	int byte; // ����� �����
	float chastota; // ������������� �������
};

void swap(table& a1, table& a2) // ����������
{
	table value;
	value = a1;
	a1 = a2;
	a2 = value;
}

int main(int argc, char** argv) {
	unsigned char Fchar;
	int SumOfBytes = 0, // ����� �����
		BYTE = 256; // ���-�� �������� �����
	table T[256];
	double entropy = 0; // ��������
	char s1[30]; // ��� �����
	for (int i = 0; i < BYTE; i++)
	{
		T[i].byte = i;
		T[i].chastota = 0;
	}

	FILE* sfile;
	cin.getline(s1, 30); // ������ ������� �����
	if (sfile = fopen(s1, " rb")) // ��������� ����
	{
		while (!feof(sfile))
		{
			fread(&Fchar, sizeof(char), 1, sfile);
			T[(int)Fchar].chastota++;
			SumOfBytes++;
		}
		T[(int)Fchar].chastota--;
		SumOfBytes--;
		for (int i = 0; i < BYTE; i++)
			for (int j = 0; j < BYTE - i; j++)
				if (T[j].chastota < T[j + 1].chastota) // ��������� ����������
					swap(T[j], T[j + 1]);

		for (int i = 0; i < BYTE; i++)
		{
			T[i].chastota = T[i].chastota; // ������� ������� �����
			if (T[i].chastota)
				entropy += -T[i].chastota / SumOfBytes * (log(T[i].chastota / SumOfBytes) / log(2)); // ������� ��������

		}
		fclose(sfile);

	}

	// ������ ����� ����

	ofstream new_file;
	char s2[20] = "Pic14bmp.tab", s3[20] = "Arh14rar.tab", s4[20] = "Pic14jpg.tab",
		s5[20] = "text14doc.tab", s6[20] = "text14docx.tab", s7[20] = "text14txt.tab";
	if (strcmp(s1, "Pic14.bmp") == 0)
		new_file.open(s2, ios_base::out);
	if (strcmp(s1, "Arh14.rar") == 0)
		new_file.open(s3, ios_base::out);
	if (strcmp(s1, "Pic14.jpg") == 0)
		new_file.open(s4, ios_base::out);
	if (strcmp(s1, "text14.doc") == 0)
		new_file.open(s5, ios_base::out);
	if (strcmp(s1, "text14.docx") == 0)
		new_file.open(s6, ios_base::out);
	if (strcmp(s1, "text14.txt") == 0)
		new_file.open(s7, ios_base::out);

	// ��������� ����

	new_file << SumOfBytes << endl
		<< entropy << endl << ceil((SumOfBytes * entropy) / 8) << endl << "" << endl;
	for (int i = 0; i < 256; i++) {
		new_file << setw(4) << T[i].byte << " " << T[i].chastota << endl;
	}
	new_file.close();
	system("pause");

	return 0;
}