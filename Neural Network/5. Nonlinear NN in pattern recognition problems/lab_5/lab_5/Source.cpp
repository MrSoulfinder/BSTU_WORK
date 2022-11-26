#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <cstdio>

#define INPUT 	30
#define HIDE		8
#define OUTPUT	10	
#define alpha 	0.1
#define E		0.4

using namespace std;
double	w_layer2[INPUT][HIDE],		//������� ������������ ����� ������� � ������� �����
T_layer2[HIDE],		//��������� �������� �� �������� ����
w_layer3[HIDE][OUTPUT],	//������� ������������ ������ ����� ������� � �������� �����
T_layer3[OUTPUT],		//��������� �������� �� ��������� ����
y_layer2[HIDE],		//�������� �������� �� ��������
y_layer3[OUTPUT];		//�������� �������� �� ���������

char input_buffer[INPUT + 1];		//�����, ��������� � ����������
double g_layer2[HIDE];		//������ �������� ��������
double g_layer3[OUTPUT];		//������ �������� ���������

bool input_sample[OUTPUT][INPUT] = {

{
0,1,1,1,0,
1,0,0,0,1,
1,0,0,0,1,
1,0,0,0,1,
1,0,0,0,1,
0,1,1,1,0
},
{
0,0,1,0,0,
0,1,1,0,0,
1,0,1,0,0,
0,0,1,0,0,
0,0,1,0,0,
1,1,1,1,1
},
{
0,1,1,1,0,
1,0,0,0,1,
0,0,0,1,0,
0,0,1,0,0,
0,1,0,0,0,
1,1,1,1,1
},
{
0,1,1,1,0,
1,0,0,0,1,
0,0,1,1,0,
0,0,1,1,0,
1,0,0,0,1,
0,1,1,1,0
},
{
0,0,0,1,0,
0,0,1,1,0,
0,1,0,1,0,
1,1,1,1,1,
0,0,0,1,0,
0,0,0,1,0
},
{
1,1,1,1,1,
1,0,0,0,0,
1,1,1,1,0,
0,0,0,0,1,
0,0,0,0,1,
1,1,1,1,0
},
{
0,1,1,1,0,
1,0,0,0,0,
1,1,1,1,0,
1,0,0,0,1,
1,0,0,0,1,
0,1,1,1,0
},
{
0,1,1,1,1,
0,0,0,0,1,
0,0,0,1,0,
0,0,1,0,0,
0,0,1,0,0,
0,0,1,0,0
},
{
0,1,1,1,0,
1,0,0,0,1,
0,1,1,1,0,
1,0,0,0,1,
1,0,0,0,1,
0,1,1,1,0
},
{
0,1,1,1,0,
1,0,0,0,1,
1,0,0,0,1,
0,1,1,1,0,
0,0,0,0,1,
0,1,1,1,0
} };

FILE* fo;

//���������� ����������� ����� ������
int out_network(char temp[]) {
	//������� �������� �������� �������� ����
	for (int i = 0; i < HIDE; i++) {
		y_layer2[i] = 0;
		for (int j = 0; j < INPUT; j++)
			if (temp[j])
				y_layer2[i] += w_layer2[j][i];
		y_layer2[i] -= T_layer2[i];
		y_layer2[i] = 1 / (1 + exp(-y_layer2[i]));
	}
	//������� �������� �������� ��������� ����
	for (int i = 0; i < OUTPUT; i++) {
		y_layer3[i] = 0;
		for (int j = 0; j < HIDE; j++)
			y_layer3[i] += y_layer2[j] * w_layer3[j][i];
		y_layer3[i] -= T_layer3[i];
	}
	//���������� ����� �������� ������
	double max_val = y_layer3[0];
	int result = 0;
	for (int i = 1; i < OUTPUT; i++)
		if (y_layer3[i] > max_val) {
			max_val = y_layer3[i];
			result = i;
		}
	return result;
}
//������������� ������
int recognition(char temp[]) {
	for (int i = 0; i < INPUT; i++) {
		if (temp[i] == '0')
			input_buffer[i] = 0;
		else
			input_buffer[i] = 1;
	}
	return out_network(input_buffer);
}

int main() {
	fo = fopen("error.txt", "wt");
	setlocale(0, "");
	srand(time(NULL));
	/// �������� ������ ���� � ������
	for (int i = 0; i < HIDE; i++) {
		for (int j = 0; j < INPUT; j++)
			w_layer2[j][i] = double(rand() - 16384) / 16384;
		for (int j = 0; j < OUTPUT; j++)
			w_layer3[i][j] = double(rand() - 16384) / 16384;
		T_layer2[i] = double(rand() - 16384) / 16384;
	}
	for (int i = 0; i < OUTPUT; i++)
		T_layer3[i] = double(rand() - 16384) / 16384;

	/// ����� ������� ��������
	for (int k = 0; k < 6; k++) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 5; j++) {
				if (input_sample[i][j + k * 5] == 0)
					printf(" ");
				else
					printf("%d", input_sample[i][j + k * 5]);
			}
			printf("  ");
		}
		printf("\n");
	}

	/// ��������
	int counter = 0;
	bool flag = 1;	//������� ��������� ��������
	while (flag) {
		flag = 0;
		//��� ������ ��������� �������:
		for (int k = 0; k < OUTPUT; k++) {
			//��������� ��������� �������
			for (int i = 0; i < INPUT; i++)
				input_buffer[i] = input_sample[k][i];
			//�������� �������� �������� ��������
			out_network(input_buffer);
			//������� ������ �������� ��������� ����
			double E_sqrt = 0;
			for (int i = 0; i < OUTPUT; i++) {
				if (i == k)
					g_layer3[i] = y_layer3[i] - 1;
				else
					g_layer3[i] = y_layer3[i];
				E_sqrt += pow(g_layer3[i], 2);
			}
			fprintf(fo, "%f\n", E_sqrt);
			//���� ���� �� ��� ������ ����������, ��������� � ��������� �������� ��������
			for (int i = 0; i < OUTPUT; i++)
				if (abs(g_layer3[i]) >= E)
					flag = 1;
			//������� ������ �������� ��������
			for (int i = 0; i < HIDE; i++) {
				g_layer2[i] = 0;
				for (int j = 0; j < OUTPUT; j++) {
					g_layer2[i] += g_layer3[j] * y_layer3[j] * (1 - y_layer3[j]) * w_layer3[i][j];
				}
			}
			//������������� �������� ������� ������������� � ��������� �������� �������� ����
			for (int j = 0; j < HIDE; j++) {
				for (int i = 0; i < INPUT; i++)
					w_layer2[i][j] -= alpha * g_layer2[j] * y_layer2[j] * (1 - y_layer2[j]) * input_buffer[i];
				T_layer2[j] += alpha * g_layer2[j] * y_layer2[j] * (1 - y_layer2[j]);
			}
			//������������� �������� ������� ������������� � ��������� �������� ��������� ����
			for (int j = 0; j < OUTPUT; j++) {
				for (int i = 0; i < HIDE; i++)
					w_layer3[i][j] -= alpha * g_layer3[j] * y_layer2[i];
				T_layer3[j] += alpha * g_layer3[j];
			}
			counter++;
		}
	}
	printf("������� �� %d ��������\n", counter);

	///������������� �������
	while (true) {
		printf("������� ����� ��� �������������: ");
		gets_s(input_buffer);
		printf("������������ ����� --> ����� %d\n", recognition(input_buffer));
	}
	fclose(fo);

	return 0;
}
