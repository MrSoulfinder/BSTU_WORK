#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

int main()
{
	clock_t start = clock();
	int n_in = 5, // ���������� ������
		n_ob = 30, // ������ ������� ��� ��������
		n_pr = 15, // ������ �������������� �������
		it = 0; // ������� ��������
	float w[5], // ������� ������������
		T, // ��������� ��������
		E, E_min, // ������ �������� � ���.������
		t[60], // ������ ��������� ��������
		y[60], // ������ �������� �������� ����
		a, Y; // �������� ��������

	for (int i = 0; i < n_in; i++)
		w[i] = (1 + rand() % 9) / (float)10; // ������������� ������� �������������
	T = (1 + rand() % 9) / (float)10; // ������������� ���������� ��������
	float tmp = 0.0;

	for (int j = 0; j < 60; j++) // ���������� ������� �������, �� ������� �������� ��������, �.�. ���������� ����������
		t[j] = 3 * sin(7 * (j + 1)) + 0.3;

	cout << "Enter a: ";
	cin >> a;
	cout << "Enter Emin: ";
	cin >> E_min;
	cout << "--------------------------------------" << endl;
	cout.width(11); cout << "t   |";
	cout.width(11); cout << "Y   |";
	cout.width(16); cout << "E   |" << endl;
	//��������
	do
	{
		E = 0;
		cout << "--------------------------------------" << endl;
		it++;
		cout << "it = " << it << endl;
		for (int i = 0; i < (n_ob - n_in); i++)
		{
			Y = 0;
			for (int j = 0; j < n_in; j++)
				Y += w[j] * t[i + j];
			Y -= T; // ������������ �������� ����������

			for (int j = 0; j < n_in; j++)
				w[j] -= a * (Y - t[i + n_in]) * t[i + j]; // �������� ������� ������������
			T += a * (Y - t[i + n_in]); // ������ ��������� ��������
		}

		for (int i = 0; i < (n_ob - n_in); i++)
		{
			Y = 0;
			for (int j = 0; j < n_in; j++)
				Y += w[j] * t[i + j];
			Y -= T; // ����������� �������� ����������
			E += 0.5 * pow((Y - t[i + n_in]), 2); // ������� ��������� ������������������ ������
			cout.width(10); cout << t[i + n_in] << "|";
			cout.width(10); cout << Y << "|";
			cout.width(15); cout << E << "|" << endl;
		}

	} while (E >= E_min);

	// ���������������
	cout << "=====================================" << endl;
	cout << "		Prediction		" << endl;
	cout.width(16); cout << "t   |";
	cout.width(16); cout << "Y   |";
	cout.width(19); cout << "E   |" << endl;

	for (int i = (n_ob - n_in); i < (n_ob + n_pr); i++)
	{
		Y = 0;
		for (int j = 0; j < n_in; j++)
			Y += w[j] * t[i + j];
		Y -= T;
		E = 0.5 * pow((Y - t[i + n_in]), 2);
		cout.width(15); cout << t[i + n_in] << "|";
		cout.width(15); cout << Y << "|";
		cout.width(18); cout << E << "|" << endl;
		t[i + n_in] = Y;
	}
	clock_t finish = clock();
	cout << "Time: " << (finish - start) << " ms\n";
	system("pause");
	return 0;
}
