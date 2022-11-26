#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

int main()
{
	clock_t start = clock();
	int n_in = 3, // ���������� ������
		n_ob = 30, // ������ ������� ��� ��������
		n_pr = 15, // ������ �������������� �������
		it = 0; // ������� ��������
	float w[5], // ������� ������������
		T, // ��������� ��������
		E = 0, sum = 0, E_min, // ������ �������� � ���.������
		t[60], // ������ ��������� ��������
		y[60], // ������ �������� �������� ����
		a, Y; // �������� ��������

	for (int i = 0; i < n_in; i++)
		w[i] = (1 + rand() % 9) / (float)10; // ������������� ������� �������������
	T = (1 + rand() % 9) / (float)10; // ������������� ���������� ��������
	float tmp = 0.0;

	for (int j = 0; j < 60; j++) // ���������� ������� �������, �� ������� �������� ��������, �.�. ���������� ����������
		t[j] = 1 * sin(0.5 * (j + 1)) + 0.1;

	cout << "Enter a: ";
	cin >> a;
	cout << "Enter Emin: ";
	cin >> E_min;
	cout << "--------------------------------------" << endl;
	//��������
	do
	{
		E = 0;
		sum = 0;
		//	cout << "--------------------------------------"<<endl;
		it++;
		//	cout << "it = " << it << endl;
		for (int i = 0; i < (n_ob - n_in); i++)
		{
			Y = 0;
			for (int j = 0; j < n_in; j++)
			{
				Y += w[j] * t[i + j];
				sum += pow(t[i + j], 2);
			}
			Y -= T; // ������������ �������� ����������

			for (int j = 0; j < n_in; j++)
				w[j] -= a * (Y - t[i + n_in]) * t[i + j]; // �������� ������� ������������
			T += a * (Y - t[i + n_in]); // ������ ��������� ��������
			a = (1 / (1 + sum));
		}

		for (int i = 0; i < (n_ob - n_in); i++)
		{
			Y = 0;
			for (int j = 0; j < n_in; j++)
				Y += w[j] * t[i + j];
			Y -= T; // ����������� �������� ����������
			E += 0.5 * pow((Y - t[i + n_in]), 2); // ������� ��������� ������������������ ������
		}

	} while (E >= E_min);

	cout << "it = " << it << endl;
	clock_t finish = clock();
	cout << "Time: " << (finish - start) << " ms\n";
	system("pause");
	return 0;
}
