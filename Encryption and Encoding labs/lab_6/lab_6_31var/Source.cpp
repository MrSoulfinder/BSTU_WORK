#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;
const int ALP = 33;//���-�� ���� � ��������
unsigned char TABLE[ALP + ALP] = { 0 }; //������ ��� ���������

void suport()//������� ���������� ������� ���������

{

	int p = 0;//��� ����� ���� � � � � ������� ASCII
	for (int i = 0; i < ALP + ALP; i++)//���� �� ������� ����� �������

	{

		if (i == 6) //���� 6 ������� � ������� ��������

		{

			TABLE[i] = '�';//������ � ���. ����� �
			p++;
			continue;//������� � ����. ��������
		}

		if (i == 6 + ALP)//���� 6 ������� � ������� ��������

		{

			TABLE[i] = '�';//������ � ���. ����� �
			p++;
			continue;//������� � ����. ��������

		}
		TABLE[i] = unsigned char(192 + i - p); //������ � ������ ����� �� �������
	}
}

int position(unsigned char ch)//���������� ����� ����� � ��������

{
	for (int i = 0; i < ALP + ALP; i++)
		if (TABLE[i] == ch) return i + 1;
	return 0;

}

unsigned char decod(int a, int b)//������� �������� ������� ���� ����

{

	int ind = 0;
	if (a > b) ind = a - b; //���� �� ��������� ������� � ����� ��������
	else ind = ALP + ALP - (b - a); //���� ��������� ������� � ����� ��������
	return TABLE[ind - 1]; //���������� �������������� ����� �� ��� �� ��������
}

void read(string file, string key)//�������� �������

{
	ifstream fin(file); //��������� ����
	if (!fin.is_open()) //�������� ��������

	{
		cout << file << " - error_open" << endl; //�����, ���� �� ������
	}

	else

	{

		suport(); //�. ���������� ������� ��������
		string buf; //������, � ������� ��������� �� �����
		int p = 0; //����� ����� � ������� �����
		ofstream fout(file + ".dec"); //������ �������������� ����
		while (getline(fin, buf)) //���� ���������� ���������

		{
			if (buf.empty()) //���� ������ ������, ��
				fout << endl;//����� ������� ������ ������ � �������������� ����

			else
			{
				for (int i = 0; buf[i] != '\0'; i++)//���� �� ������ � ������ �������� � ������
				{
					if (int a = position(buf[i])) //����������� ����� ����� ������ � ��������

					{

						int b = position(key[p]);//����������� ����� ����� ����� � ��������
						buf[i] = decod(a, b);//�. ���������� �������� � �����. �����

					}
					p++; //������� � ��������� ����� �����
					if (p == key.length()) p = 0;//���� ����� �� ������� �����, �� ������� � ������ �����

				}
				fout << buf << endl;//����� ��������� ������ � �������������� ����
			}
		}
		fout.close();//�������� ��������������� �����
		cout << endl << "Mission complete!" << endl;//����� ��������� � �������
	}
	fin.close();//�������� ��������� �����
}

int main()

{
	SetConsoleCP(1251);//��� ������� ��������� ��������� �����
	string key, file; //������ ��� ����� � �������� ��������� �����
	cout << "Enter the key:" << endl; //����� ��������� �� �������
	cin >> key; //���� �����
	cout << endl << "Enter file name:" << endl;//����� ��������� �� �������
	cin >> file; //���� ����� ��������� �����
	read(file, key); //�������� �������
	return 0;
}