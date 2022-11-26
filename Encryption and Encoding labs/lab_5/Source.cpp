#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
int main()
{
    char fname[15]; //��� �����
    char key[10]; //����
    char ALF[67]; //������� �������

    /*�������������� �������*/
    for (size_t i = 0; i < 6; i++)
    {
        ALF[i] = i + 192;
        ALF[i + 33] = i + 224;
    }
    for (size_t i = 7; i < 33; i++)
    {
        ALF[i] = i + 191;
        ALF[i + 33] = i + 223;
    }
    ALF[6] = '�';
    ALF[39] = '�';

    /*������ ��� �����, ������� ����� �����������*/
    printf("Enter filename: ");
    scanf("%s15", fname);
    FILE* fp = fopen(fname, "r");

    /*���������� ��� �������������� �����*/
    for (size_t i = strlen(fname); i--;)
        if (fname[i] == '.')
        {
            fname[i] = '\0';
            strcat(fname, "(S).txt");
            break;
        }

    FILE* fp1 = fopen(fname, "w"); //������ ����������� ����
    printf("Enter Key: ");
    scanf("%s20", key); //������ ����
    int c = 0, //��������� ������
        i = 0, j = 0, k = 0;
    int code = 0;

    while ((c = fgetc(fp)) != EOF) //��������� �������, ���� �� ����������� ����� �����
    {
        j = 0;
        /*���������� ������ �� ������ � ������� �������
        ���� j = -1, �� ������*/
        while (ALF[j] != '\0')
        {
            if (ALF[j] == (char)c)
            {
                j = -1;
                break;
            }
            j++;
        }

        if (j == -1) //���� ������ �������� ������ �������� ��������
        {
            j = k = 0;
            while ((char)c != ALF[j]) //���� �������� ������ �� ����� ������ � ��������
                j++; // j - ����� ������� � ������� ��������
            while (key[i] != ALF[k]) //���� ������ �� ����� �� ����� ������ � ��������
                k++; // k - ����� i-�� ������� ����� � ��������
            code = j + k; //�������������� ������
            if (code > 66) //���� ��� ������ ����� �������� �������� �������
                code -= 66;
            fprintf(fp1, "%c", ALF[code - 1]);
        }
        else fprintf(fp1, "%c", c);
        /*�������� ����� ��� �������� �������� ������ �� ������������ ����*/

        if (c != 10)
        {
            if (key[i + 1] != '\0')
                i++;
            else if (key[i + 1] == '\0')
                i = 0;
        }
    }
    system("pause");
}
