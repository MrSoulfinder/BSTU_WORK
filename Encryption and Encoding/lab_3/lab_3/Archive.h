#pragma once
#define _CRT_SECURE_NO_WARNINGS

#ifndef _ARCHIVE_H_

#define _ARCHIVE_H_

#include <bitset>

#include <stdio.h>

#include <string.h>

#include "freqtable.h"

#include "huffman.h"

// ����� ������

class archive

{

protected:

	std::string fileName; // ��� �����

	huffman* huff; // �������� ��������

public:

	archive() { }

	void compress(std::string _fileName); // ���������

	void decompress(std::string _fileName); // ������������

	~archive();

};

archive::~archive()

{

	delete huff;

}

void archive::compress(std::string _fileName)

{

	delete huff;

	huff = nullptr;

	fileName = _fileName;

	huff = new huffman(fileName);

	huff->write(); // ������� ��� ��������

	std::ifstream file(fileName, std::ifstream::binary); // ��������� ���� � �������� ������

	int symbolCount = huff->FileSize; // ���������� ��������

	unsigned char* data; // ���������� �����

	data = new unsigned char[symbolCount]; // ���������� ������

	file.read((char*)data, symbolCount); // ��������� ������

	file.close();

	std::string huffmanCode = "";

	for (int i = 0; i < symbolCount; i++)

	{

		huffmanCode += huff->getCodeOfByte(data[i]); // ���������� ���� � ����� ������

	}

	int huffmanLength = huff->length();

	std::cout << "Length of Huffman code:\t" << huffmanLength << std::endl;

	std::ofstream outputFile(fileName + ".arch", std::ofstream::binary);

	for (int i = 0; i < huffmanLength; i += 8)

	{

		std::string eightBits;

		std::bitset<8> bits;

		eightBits = huffmanCode.substr(i, 8);

		if (eightBits.length() == 8)

		{

			bits = std::bitset<8>(eightBits); // ��������� ���� � �����

		}

		else

		{

			int i = 0;

			for (i; i < eightBits.length(); i++) // �� ��������� ������ ��� ������� ������ ����

				if (eightBits[i] == '1')

				{

					bits.set(bits.size() - i - 1);

				}

				else

				{

					bits.reset(bits.size() - i - 1);

				}

		}

		char n = bits.to_ulong();

		outputFile << n; // ���������� � ����

	}

	outputFile.close();

	delete[] data;

}

// ������� �������������� ������ �������� � ������ ���

void string2binary(const unsigned char* bytes, size_t len, std::string& bitStr) {

	size_t i;

	char buffer[9] = "";

	for (i = 0; i < len; i++) {

		sprintf(buffer,

			"%c%c%c%c%c%c%c%c",

			(bytes[i] & 0x80) ? '1' : '0',

			(bytes[i] & 0x40) ? '1' : '0',

			(bytes[i] & 0x20) ? '1' : '0',

			(bytes[i] & 0x10) ? '1' : '0',

			(bytes[i] & 0x08) ? '1' : '0',

			(bytes[i] & 0x04) ? '1' : '0',

			(bytes[i] & 0x02) ? '1' : '0',

			(bytes[i] & 0x01) ? '1' : '0');

		bitStr += buffer;

		buffer[0] = '\0';

	}

}

// ������������

void archive::decompress(std::string _fileName)

{

	delete huff;

	huff = nullptr;

	fileName = _fileName;

	huff = new huffman(fileName);

	huff->readFreqTable(); // ��������� ������� ������ �� �����

	std::ifstream file;

	file.open(_fileName + ".arch", std::ifstream::binary); // ��������� ���� � �������� ������

	file.seekg(0, file.end);

	int size = file.tellg(); // ������� ���������� �������� � �����

	unsigned char* data = new unsigned char[size]; // ���������� ������

	file.seekg(0, file.beg);

	file.read((char*)data, size); // ��������� ������

	file.close();

	std::string encodedData, decodedData;

	encodedData.reserve(size * 8); // �������� ������

	int sizeDifference = size * 8 - huff->length(); // ���������� ������ ������� ����

	string2binary(data, size, encodedData);

	encodedData.erase(encodedData.length() - sizeDifference, sizeDifference);

	decodedData = huff->decode(encodedData); // ����������

	std::ofstream outputFile("!" + fileName, std::ofstream::binary);

	outputFile << decodedData; // ������� �������������� �����

	outputFile.close();

	delete[] data;

}

#endif