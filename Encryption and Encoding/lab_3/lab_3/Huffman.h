#pragma once
#define _CRT_SECURE_NO_WARNINGS

#ifndef _HUFFMAN_H_

#define _HUFFMAN_H_

#include "calg.h"

// ����� ��� ��������� ��������

class huffman : public calg

{

protected:

	void calculateCodes(freqtable::ByteRepeats* root, std::string codeline); // ����������� ������� �������� ���� ��������

	double averageLength(); // ������� �����

	std::priority_queue<freqtable::ByteRepeats*, std::vector<freqtable::ByteRepeats*>, freqtable::ByteRepeatsCompare> minByte; // ������

public:

	huffman() { }

	huffman(std::string _fileName) : calg(_fileName) { }

	void calculate(); // �������� ������ � ������� �����

	void write(); // ������ � ����

	void readFreqTable(); // ������ ������� ������� ������ � ������� �����

	std::string decode(std::string codeline); // �������������

	int length(); // ����� ������� ����

	~huffman() { }

};

// ������� �������� �����

void huffman::calculateCodes(freqtable::ByteRepeats* root, std::string codeline)

{

	if (!root)

	{

		return;

	}

	if (root->byte != 256)

	{

		codes.push_back(ByteAndCode(*root, codeline)); // ���� ������, �� ���������

	}

	calculateCodes(root->left, codeline + "0"); // ���� �� ����� �����

	calculateCodes(root->right, codeline + "1"); // ���� �� ������ �����

}

int huffman::length()

{

	int _length = 0;

	for (int i = 0; i < codes.size(); i++)

	{

		_length += codes[i].byte.repeats * codes[i].code.length(); // ��������� �����

	}

	return _length;

}

double huffman::averageLength()

{

	double _length = length();

	int allRepeats = ftable.AllRepeats;

	return _length / allRepeats; // ��������� ������� �����

}

void huffman::calculate()

{

	freqtable::ByteRepeats* left, * right, * top;

	for (int i = 0; i < ftable.repeatsTable.size(); ++i)

		minByte.push(new freqtable::ByteRepeats(ftable.repeatsTable[i].byte, ftable.repeatsTable[i].repeats)); // �������� ������

		// Iterate while size of heap doesn't become 1

	while (minByte.size() != 1)

	{

		left = minByte.top();

		minByte.pop(); // ������� �����

		right = minByte.top();

		minByte.pop(); // ������� ������

		top = new freqtable::ByteRepeats(256, left->repeats + right->repeats); // ������� ������ � ����� �����

		top->left = left;

		top->right = right;

		minByte.push(top); // ��������� ������

	}

	codes.erase(codes.begin(), codes.end()); // �������, ���� �������������

	calculateCodes(minByte.top(), ""); // �������� ������� �������� �����

}

// ����������

std::string huffman::decode(std::string codeline)

{

	std::string ans = "";

	freqtable::ByteRepeats* curr = minByte.top(); // ��������� ������

	for (int i = 0; i < codeline.size(); i++)

	{

		if (codeline[i] == '0')

			curr = curr->left; // ���� �� ����� �����

		else

			curr = curr->right; // ���� �� ������ �����

			// reached leaf node

		if (curr->left == nullptr and curr->right == nullptr)

		{

			ans += (char)curr->byte;

			curr = minByte.top();

		}

	}

	return ans;

}

// ������ �� ����

void huffman::write()

{

	std::cout << "\nTry to calculate Huffman of " + fileName << std::endl;

	ftable.write();

	FileSize = ftable.FileSize;

	calculate();

	std::ofstream outputFile(fileName + ".huf"); // ������� �������� ����

	outputFile << ftable.Entropy << '\n' << averageLength() << std::endl;

	for (int i = 0; i < codes.size(); i++)

	{

		if (codes[i].byte.byte == 256)

			break;

		outputFile << "\n" << codes[i].byte.byte << "\t" << codes[i].code;

	}

	outputFile.close(); // ��������� ����

}

// ���������� � �����

void huffman::readFreqTable()

{

	std::cout << "Try to read Huffman of " + fileName << std::endl;

	ftable.read();

	calculate();

	std::ofstream outputFile(fileName + ".huf"); // ������� �������� ����

	outputFile << ftable.Entropy << '\n' << averageLength() << std::endl;

	for (int i = 0; i < codes.size(); i++)

	{

		if (codes[i].byte.byte == 256)

			break;

		outputFile << "\n" << codes[i].byte.byte << "\t" << codes[i].code;

	}

	outputFile.close(); // ��������� ����

}

#endif
