#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <iostream>
#include <fstream>

#include "FlvParser.h"
#include "FlvDumpFile.h"

using namespace std;



void Process(fstream &fin)
{
	CFlvParser parser;

	int nBufSize = 2000 * 1024;
	int nFlvPos = 0;
	unsigned char *pBuf, *pBak;
	pBuf = new unsigned char[nBufSize];
	pBak = new unsigned char[nBufSize];

	while (1) {
		int nReadNum = 0;
		int nUsedLen = 0;
		fin.read((char *)pBuf + nFlvPos, nBufSize - nFlvPos);
		nReadNum = fin.gcount();
		if (nReadNum == 0) {
			break;
		}

		nFlvPos += nReadNum;

		parser.Parse(pBuf, nFlvPos, nUsedLen);
		if (nFlvPos != nUsedLen) {
			memcpy(pBak, pBuf + nUsedLen, nFlvPos - nUsedLen);
			memcpy(pBuf, pBak, nFlvPos - nUsedLen);
		}

		nFlvPos -= nUsedLen;
	}

	PrintInfo(&parser);
	
	DumpH264(&parser, "test.h264");
	DumpAAC(&parser, "test.aac");
	// DumpFlv(&parser, filename);

	delete[] pBak;
	delete[] pBuf;

	return;
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		cout << "FlvParser [input flv]" << endl;
		return 0;
	}

	fstream fin;
	fin.open(argv[1], ios_base::in | ios_base::binary);
	if (!fin) {
		return 0;
	}

	Process(fin);

	fin.close();

	return 1;
}

