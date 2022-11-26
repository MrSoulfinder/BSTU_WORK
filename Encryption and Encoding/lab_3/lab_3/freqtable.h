#pragma once
#define _CRT_SECURE_NO_WARNINGS

#ifndef _FREQTABLE_H_

#define _FREQTABLE_H_

#include <iostream>

#include <fstream>

#include <math.h>

#include <string>

#include <sstream>

#include <algorithm>

#include <queue>

#include <vector>

// ������� ������

class freqtable

{

protected:

	std::string fileName = ""; // ��� �����

	int fileSize(); // ������ �����

	double entropy(); // ��������

	void allRepeats(); // ��� ����������

public:

	freqtable() { }

	freqtable(std::string _fileName) : fileName(_fileName) { }

	struct ByteRepeats; // ���� � ��� ����������

	struct ByteRepeatsCompare; // ����������

	std::vector<ByteRepeats> repeatsTable; // ���� ������� ������

	void update(std::string _fileName); // ����� �������� �����

	void calculate(); // �������

	void write(); // ������ � ����

	void read(); // ����������� � �����

	double Entropy;

	int AllRepeats;

	int FileSize;

	~freqtable() { }

};

struct freqtable::ByteRepeats

{

	int byte; // ����

	int repeats; // ����������

	ByteRepeats* left, * right;

	ByteRepeats() : byte(0), repeats(0), left(nullptr), right(nullptr) { }

	ByteRepeats(int _b, int _r) : byte(_b), repeats(_r), left(nullptr), right(nullptr) { }

};

// ����������

struct freqtable::ByteRepeatsCompare

{

	bool operator()(ByteRepeats l, ByteRepeats r)

	{

		return (l.repeats > r.repeats);

	}

	bool operator()(ByteRepeats* l, ByteRepeats* r)

	{

		return (l->repeats > r->repeats);

	}

};

void freqtable::update(std::string _fileName)

{

	fileName = _fileName;

}

int freqtable::fileSize()

{

	int size = 0;

	std::ifstream file(fileName, std::ifstream::binary); // ��������� ���� � �������� ������

	file.seekg(0, file.end);

	size = file.tellg(); // ������� ���������� �������� � �����

	file.seekg(0, file.beg);

	file.close();

	FileSize = size;

	return size;

}

void freqtable::calculate()

{

	if (fileName == "")

	{

		return;

	}

	repeatsTable.erase(repeatsTable.begin(), repeatsTable.end()); // �������, ���� ����� ��������������

	std::ifstream file(fileName, std::ifstream::binary); // ��������� ���� � �������� ������

	int symbolCount = fileSize(); // ���������� ��������

	unsigned char* data; // ���������� �����

	data = new unsigned char[symbolCount]; // ���������� ������

	file.read((char*)data, symbolCount); // ��������� ������

	file.close();

	for (int i = 0; i < 256; i++)

	{

		repeatsTable.push_back(ByteRepeats(i, 0)); // ���� �������� ������

	}

	for (int i = 0; i < symbolCount; ++i)

	{

		++repeatsTable[data[i]].repeats; // ������� ���������� ������

	}

	std::sort(repeatsTable.begin(), repeatsTable.end(), ByteRepeatsCompare()); // ���������

	// ������� ����� � �������� ������������

	for (std::vector<ByteRepeats>::iterator i = repeatsTable.begin(); i != repeatsTable.end();)

	{

		if (i->repeats == 0)

		{

			i = repeatsTable.erase(i);

		}

		else

		{

			i++;

		}

	}

	entropy(); // ������� ��������

	allRepeats();

	delete[] data; // ����������� ������

}

// ��� ����������

void freqtable::allRepeats()

{

	int allRep = 0;

	for (int i = 0; i < repeatsTable.size(); i++)

	{

		allRep += repeatsTable[i].repeats;

	}

	AllRepeats = allRep;

}

// ��������

double freqtable::entropy()

{

	double freq[256], entropy = 0;

	std::fill(freq, freq + 256, 0);

	for (int i = 0; i < repeatsTable.size(); ++i)

	{

		if (repeatsTable[i].repeats == 0)

		{

			continue;

		}

		freq[i] = (double)repeatsTable[i].repeats / fileSize(); // ������� �������

		entropy += (log10(1.0 / freq[i]) / log10(2.0)) * freq[i]; // ������� �������� �� ������� �������

	}

	Entropy = entropy;

	return entropy;

}

// ������ � ����

void freqtable::write()

{

	std::cout << "Try to calculate FreqTable of " + fileName << std::endl;

	calculate();

	std::ofstream outputFile(fileName + ".tab"); // ������� �������� ����

	outputFile << Entropy << std::endl;

	for (int i = 0; i < repeatsTable.size(); i++)

	{

		outputFile << "\n" << repeatsTable[i].byte << "\t\t" << repeatsTable[i].repeats; // ������� ��������� �������

	}

	outputFile << std::endl;

	outputFile.close(); // ��������� ����

}

// ����������� � �����

void freqtable::read()

{

	std::string line;

	repeatsTable.erase(repeatsTable.begin(), repeatsTable.end()); // �������

	std::ifstream file(fileName + ".tab"); // ��������� ���� � �������� ������

	if (file.is_open())

	{

		int lineCount = 0;

		while (getline(file, line))

		{

			if (lineCount == 0)

			{

				std::stringstream ss(line);

				ss >> Entropy;

				lineCount++;

			}

			int found = line.find('\t'); // ���� ���������

			if (found != -1)

			{

				std::string _byte, _repeats;

				_byte = line.substr(0, found); // ����

				_repeats = line.substr(found + 1, line.length() - 1); // ����������

				repeatsTable.push_back(ByteRepeats(std::stoi(_byte), std::stoi(_repeats)));

			}

		}

	}

	allRepeats();

	file.close();

}

#endif
