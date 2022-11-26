#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

int MIN(int min, char key[]);

void main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char fname[15] = { NULL };  //��� �����
    char key[20] = { NULL };  //����
    /*������ ��� �����, ������� ����� ������������*/
    printf("ENTER FILENAME -> ");
    scanf("%s15", fname);
    printf("ENTER KEY -> ");
    scanf("%s20", key); //������ ����
    FILE* fp = fopen(fname, "rb");
    /*���������� ��� ��������������� �����*/
    for (int i = strlen(fname); i--;)
        if (fname[i] == '.')
        {
            fname[i] = '\0';
            strcat(fname, "!.txt");
            break;
        }
    FILE* fp1 = fopen(fname, "wb"); //������ ������������� ����
    int k = 0, // k - ����� �����
        c = 0; // � - �������� ������
        /*������� ����� �����*/
    while ((c = fgetc(fp)) != EOF)
        k++;
    fseek(fp, 0, SEEK_SET);
    // m - ���������� �����
    int m = k / strlen(key);
    //������� �� ��������
    int ost = k % strlen(key);
    int n = 0;
    //�������������� �������
    int** table;
    table = (int**)calloc((m + 1), sizeof(int*));
    for (int i = 0; i < (m + 1); i++)
        table[i] = (int*)calloc(strlen(key), sizeof(int));
    size_t x = 0;
    //����������� �������
    while (x <= strlen(key))
    {
        n = MIN((int)key[x], key);
        for (int j = 0; j < m; j++)
        {
            table[j][n] = fgetc(fp);
        }
        //���������� ��������� ������ ������� ����� ���� �� ������
        if (n <= (ost - 1))
        {
            table[m][n] = fgetc(fp);
        }
        x++;
    }
    int n1 = 0;
    //������ � �������� ����
    for (int i = 1; i < m; i++)
    {
        for (size_t j = 0; j < strlen(key); j++)
        {
            fputc(table[i][j], fp1);
            n1++;
            if (n1 == k)
                break;
        }
    }
}
//������� ���������� ����� ������� ������� ���������
int MIN(int min, char key[])
{
    int k = 0;
    for (size_t i = 0; i <= strlen(key); i++)
    {
        if ((int)key[i] < min)
            k++;
    }
    return k;
}

