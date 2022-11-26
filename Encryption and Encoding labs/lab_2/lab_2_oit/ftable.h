#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <math.h>

// ������� ������
class ftable
{
protected:
    std::string fileName; // ��� �����
    double entropy(); // ��������(������� ���������)
    void length(); // ��� ���������� (������� ��������)
    void sortAndDeleteZeros(); // ����������
public:
    ftable() : fileName("") { }
    ftable(std::string _fileName) : fileName(_fileName) { }
    void newFile(std::string _fileName); // �������� ������ �����
    struct ByteStruct; // ����� � �� ����������
    struct ByteCompare; // ���������
    std::vector<ByteStruct> table; // ������� ����������
    void buildTable(); // �������
    void writeToFile(std::string FileName); // ������ � ����
    double Entropy = 0.0; // ��������
    int Repeats = 0; // ����������
    int Symbols = 0; // �������� � �����

    ~ftable() { }
};

struct ftable::ByteStruct
{
    int byte; // ����
    int repeats; // ����������
    ByteStruct* lNode, * rNode; // ����� � ������ ����
    ByteStruct() : byte(0), repeats(0), lNode(nullptr), rNode(nullptr) { } // �����������
    ByteStruct(int Byte, int Repeats) : byte(Byte), repeats(Repeats), lNode(nullptr), rNode(nullptr) { }
};

struct ftable::ByteCompare {
    bool operator()(ByteStruct l, ByteStruct r) {
        return (l.repeats > r.repeats); // ��������
    }
    bool operator()(ByteStruct* l, ByteStruct* r) {
        return (l->repeats > r->repeats);
    }
};

void ftable::newFile(std::string _fileName) {
    fileName = _fileName;
}

// ������� ������� ������
void ftable::buildTable()
{
    int symbolCount = 0;

    if (fileName == "") {
        return;
    }
    table.erase(table.begin(), table.end()); // ������� �������
    std::ifstream file; // ��������� ���� � �������� ������
    file.open(fileName, std::ifstream::binary);
    if (file.is_open())
    {
        file.seekg(0, file.end);
        symbolCount = file.tellg(); // ������� ���������� �������� � �����
        Symbols = symbolCount;
        file.seekg(0, file.beg);
    }
    unsigned char* data; // ���������� �����
    data = new unsigned char[symbolCount]; // �������� ������
    file.read((char*)data, symbolCount); // ��������� ������
    file.close();
    for (int i = 0; i < 256; i++) {
        table.push_back(ByteStruct(i, 0)); // ���� �������� ������
    }
    for (int i = 0; i < symbolCount; ++i) {
        table[data[i]].repeats += 1; // ������� ���������� ������, ����� ����� ����� �������� ������� �������
    }
    sortAndDeleteZeros();
    entropy();
    length();
    delete[] data; // ����������� ������
}

// ������ � ����
void ftable::writeToFile(std::string FileName)
{
    std::cout << "Write Table of Freqs of " + fileName << std::endl;
    newFile(FileName);
    buildTable();
    std::ofstream outputFile("Algoritm/Tables/" + fileName + ".tab"); // ������� �������� ����
    outputFile << Entropy << std::endl;
    for (int i = 0; i < table.size(); i++) {
        outputFile << "\n" << table[i].byte << "\t" << table[i].repeats;	// ������� ������� ������
    }
    outputFile.close(); // ��������� ����
}

void ftable::sortAndDeleteZeros() {
    std::sort(table.begin(), table.end(), ByteCompare()); // ���������
    // ������� ������� ����������
    for (std::vector<ByteStruct>::const_iterator byteIterator = table.begin(); byteIterator != table.end(); ) {
        if ((*byteIterator).repeats == 0) {
            byteIterator = table.erase(byteIterator);
        }
        else {
            ++byteIterator;
        }
    }
}

void ftable::length() {
    int repeats = 0;
    for (std::vector<ByteStruct>::const_iterator byteIterator = table.begin(); byteIterator != table.end(); byteIterator++)
    {
        repeats += byteIterator->repeats; // ��� ����������
    }
    Repeats = repeats;
}

double ftable::entropy()
{
    double freqOfByte[256], entropy = 0;
    std::fill(freqOfByte, freqOfByte + 256, 0);
    for (int i = 0; i < table.size(); ++i) {
        freqOfByte[i] = (double)table[i].repeats / Symbols; // ������� �������
        entropy += (log10(1.0 / freqOfByte[i]) / log10(2.0)) * freqOfByte[i]; // ������� �������� �� ������� �������
    }
    Entropy = entropy;
    return entropy;
}
