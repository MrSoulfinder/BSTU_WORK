#pragma once
#include "ftable.h"

// �������� �������-����
class sfano
{
protected:
    std::string fileName;
    ftable FTable;
    struct SfanoCode;
    void saveCode(std::vector<SfanoCode>& sfCodes, int left, int right);
    double length();
public:
    sfano() { }
    sfano(std::string FileName);
    std::vector<SfanoCode> sfCode;
    void buildSfanoTable();
    void newFile(std::string FileName);
    void writeToFile(std::string FileName);

    ~sfano() { }
};

sfano::sfano(std::string FileName) {
    fileName = FileName;
    FTable = ftable(fileName);
    FTable.buildTable();
}

struct sfano::SfanoCode
{
    ftable::ByteStruct byte; // ����
    std::string code; // ���
    SfanoCode(ftable::ByteStruct Byte, std::string Code) : byte(Byte), code(Code) { }
    SfanoCode() : byte(ftable::ByteStruct(0, 0)), code("") { }
};

void sfano::newFile(std::string FileName)
{
    fileName = FileName;
    FTable = ftable(fileName);
    FTable.buildTable();
}

// ������� �����
void sfano::saveCode(std::vector<SfanoCode>& sfCodes, int left, int right)
{
    if (left == right)
        return;
    int leftPosition = left; // ������ ������
    int rightPosition = right; // ����� ������
    int leftSum = 0;
    int rightSum = 0;

    // ���� ��������
    while (leftPosition < rightPosition) {
        if (leftSum <= rightSum) {
            leftSum += sfCode[leftPosition].byte.repeats;
            leftPosition++;
        }
        else {
            rightSum += sfCode[rightPosition].byte.repeats;
            rightPosition--;
        }
    }

    // ������������ ����
    for (int leftPointer = left; leftPointer < leftPosition; leftPointer++) {
        sfCode[leftPointer].code += "1";
    }
    for (int rightPointer = leftPosition; rightPointer <= right; rightPointer++) {
        sfCode[rightPointer].code += "0";
    }
    // ���� �����
    saveCode(sfCode, left, leftPosition - 1);
    // ���� ������
    saveCode(sfCode, leftPosition, right);
}

// ������� �����
double sfano::length()
{
    double length = 0;
    int allRepeats = FTable.Repeats;
    for (int i = 0; i < sfCode.size(); i++)
    {
        length += sfCode[i].byte.repeats * sfCode[i].code.length(); // ���� ����� �����
    }
    return length / allRepeats;
}

// �������� �������
void sfano::buildSfanoTable()
{
    sfCode.erase(sfCode.begin(), sfCode.end());
    for (int i = 0; i < FTable.table.size(); ++i)
    {
        sfCode.push_back(SfanoCode(ftable::ByteStruct(FTable.table[i].byte, FTable.table[i].repeats), "")); // ��������� ����� � �������
    }
    saveCode(sfCode, 0, FTable.table.size() - 1);
}

// ������ � ����
void sfano::writeToFile(std::string FileName)
{
    std::cout << "Write SF of " + fileName << std::endl;
    newFile(FileName);
    buildSfanoTable();
    std::ofstream outputFile("Algoritm/SF/" + fileName + ".s-f"); // ������� �������� ����
    outputFile << FTable.Entropy << '\n' << length() << std::endl;
    for (int i = sfCode.size() - 1; i >= 0; i--)
    {
        outputFile << "\n" << sfCode[i].byte.byte << "\t" << sfCode[i].code;
    }
    outputFile.close(); // ��������� ����
}
