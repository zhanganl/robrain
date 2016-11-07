#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <fstream>

#include "base/Log.h"

#include "FlvEncoder.h"
#include "FlvDumpFile.h"

using namespace std;



int GetOneNalu(u_char *pBufIn, int nInSize, u_char *pNalu, int &nNaluSize)
{
	u_char *p = pBufIn;
	int nStartPos = 0, nEndPos = 0;

	while (1) {
		if (p[0] == 0 && p[1] == 0 && p[2] == 0 && p[3] == 1) {
			nStartPos = p - pBufIn;
			break;
		}

		p++;

		if (p - pBufIn >= nInSize - 4) {
			return 0;
		}
	}

	p++;

	while (1) {
		if (p[0] == 0 && p[1] == 0 && p[2] == 0 && p[3] == 1) {
			nEndPos = p - pBufIn;
			break;
		}

		p++;

		if (p - pBufIn >= nInSize - 4) {
			nEndPos = nInSize;
			break;
		}
	}

	nNaluSize = nEndPos - nStartPos;
	memcpy(pNalu, pBufIn + nStartPos, nNaluSize);

	return 1;
}

int GetOneAACFrame(u_char *pBufIn, int nInSize, u_char *pAACFrame, int &nAACFrameSize)
{
	unsigned char *p = pBufIn;

	if (nInSize <= 7)
		return 0;

	int nFrameSize = ((p[3] & 0x3) << 11) + (p[4] << 3) + (p[5] >> 5);
	if (nInSize < nFrameSize)
		return 0;

	nAACFrameSize = nFrameSize;
	memcpy(pAACFrame, pBufIn, nFrameSize);

	return 1;
}

class CVideo
{
public:
	CVideo(string filename, CFlvEncoder *pencoder);
	~CVideo();

	int Write();

private:
	int 		m_TimeStamp;
	fstream 	m_File;
	int 		m_nFileSize;
	u_char 		*m_pBufferIn;
	u_char 		*m_pBufferOut;
	int 		m_nOffset;
	int 		m_count;
	CFlvEncoder *m_pencoder;
};

CVideo::CVideo(string filename, CFlvEncoder *pencoder)
: m_TimeStamp(0)
, m_File(NULL)
, m_nFileSize(0)
, m_pBufferIn(NULL)
, m_pBufferOut(NULL)
, m_nOffset(0)
, m_count(0)
, m_pencoder(pencoder)
{
	m_File.open(filename.c_str(), ios::binary | ios::in);

	m_File.seekg(0, ios::end);
	m_nFileSize = m_File.tellg();

	m_File.seekg(0, ios_base::beg);

	m_pBufferIn = new u_char[m_nFileSize];
	m_pBufferOut = new u_char[m_nFileSize];

	m_File.read((char *)m_pBufferIn, m_nFileSize);
}

CVideo::~CVideo()
{
	delete m_pBufferIn;
	delete m_pBufferOut;

	m_File.close();
}

int CVideo::Write()
{
	int nNaluSize = 0;

	if (GetOneNalu(m_pBufferIn + m_nOffset, m_nFileSize - m_nOffset, m_pBufferOut, nNaluSize) == 0) {
		DEBUG("\n");
		return -1;
	}

	m_pencoder->ConvertH264(m_pBufferOut, nNaluSize, m_TimeStamp);

	if (m_pBufferOut[4] != 0x67 && m_pBufferOut[4] != 0x68) {
		m_TimeStamp += 33;
	}

	m_nOffset += nNaluSize;

	if (m_nOffset >= m_nFileSize - 4) {
		DEBUG("\n");
		return -1;
	}

	m_count++;

	return m_TimeStamp;
}

class CAudio
{
public:
	CAudio(string filename, CFlvEncoder *pencoder);
	~CAudio();

	int Write();

private:
	int 		m_TimeStamp;
	fstream 	m_File;
	int 		m_nFileSize;
	u_char 		*m_pBufferIn;
	u_char 		*m_pBufferOut;
	int 		m_nOffset;
	int 		m_count;
	CFlvEncoder *m_pencoder;
};

CAudio::CAudio(string filename, CFlvEncoder *pencoder)
: m_TimeStamp(0)
, m_File(NULL)
, m_nFileSize(0)
, m_pBufferIn(NULL)
, m_pBufferOut(NULL)
, m_nOffset(0)
, m_count(0)
, m_pencoder(pencoder)
{
	m_File.open(filename.c_str(), ios::binary | ios::in);

	m_File.seekg(0, ios::end);
	m_nFileSize = m_File.tellg();

	m_File.seekg(0, ios_base::beg);

	m_pBufferIn = new u_char[m_nFileSize];
	m_pBufferOut = new u_char[m_nFileSize];

	m_File.read((char *)m_pBufferIn, m_nFileSize);
}

CAudio::~CAudio()
{
	delete m_pBufferIn;
	delete m_pBufferOut;

	m_File.close();
}

int CAudio::Write()
{
	int nAACFrameSize = 0;

	if (GetOneAACFrame(m_pBufferIn + m_nOffset, m_nFileSize - m_nOffset, m_pBufferOut, nAACFrameSize) == 0) {
		DEBUG("\n");
		return -1;
	}

	printf("nAACFrameSize = %d\n", nAACFrameSize);
	m_pencoder->ConvertAAC(m_pBufferOut, nAACFrameSize, m_TimeStamp);

	m_TimeStamp += double (1024 * 1000) / double (44100);
	m_nOffset += nAACFrameSize;

	if (m_nOffset >= m_nFileSize - 4) {
		DEBUG("\n");
		return -1;
	}

	m_count++;

	return m_TimeStamp;
}

int main(int argc, char *argv[])
{
  	int ch;
  	string videofile;
  	string audiofile;
  	bool bAudio = false, bVideo = false;
  
  	while((ch = getopt(argc, argv,"a:v:")) != -1) {

	    switch(ch) {
	    case 'a':
	      	audiofile = optarg;
	      	bAudio = true;
	        break;

	    case 'v':
	    	videofile = optarg;
	    	bVideo = true;
	        break;

	    default:
	    	break;
	   	}
	}

	CAudio *pAudio = NULL;
	CVideo *pVideo = NULL;
	uint32_t atime = 0, vtime = 0;
	bool bastop = false, bvstop = false;
	CFlvEncoder FlvEncoder;

	if(bAudio) {
		pAudio = new CAudio(audiofile, &FlvEncoder);
	}

	if(bVideo) {
		pVideo = new CVideo(videofile, &FlvEncoder);
	}

	int timestamp = 0;

	FlvEncoder.Start(bAudio, bVideo);

	while(1) {
		if(bAudio && bVideo) {
			if(atime <= vtime && !bastop) {
				if((timestamp = pAudio->Write()) < 0) {
					bastop = true;
				} else {
					atime = timestamp;
				} 
			} else if(!bvstop) {
				if((timestamp = pVideo->Write()) < 0) {
					bvstop = true;
				} else {
					vtime = timestamp;
				}	
			}

			if(bastop && bvstop) {
				break;
			}
		} else if(bAudio) {
			if((timestamp = pAudio->Write()) < 0) {
				break;
			}
				
			atime = timestamp;
		} else if(bVideo) {
			if((timestamp = pVideo->Write()) < 0) {
				break;
			}
			
			vtime = timestamp;
		}
	}

	FlvEncoder.Stop();

	if(bAudio && bVideo) {
		DumpFlv(&FlvEncoder, "encoder_test.flv");
	} else if(bAudio) {
		DumpFlv(&FlvEncoder, "aac.flv");
	} else if(bVideo) {
		DumpFlv(&FlvEncoder, "h264.flv");
	}

	if(pAudio != NULL)
		delete pAudio;

	if(pVideo != NULL)
		delete pVideo;

   	return 0;
}

#if 0
// fstream g_fileIn;
// int g_mode = 0;
// CFlvEncoder g_cnvt;
// unsigned char *g_pBufferIn, *g_pBufferOut;
// int g_nFileSize = 0;

int Initialize(int argc, char *argv[])
{
	g_mode = atoi(argv[1]);
	if (g_mode != 1 && g_mode != 2) {
		cout << "mode must be 1 or 2" << endl;
		return 0;
	}

	g_fileIn.open(argv[2], ios::binary | ios::in);
	if (!g_fileIn) {
		cout << argv[1] << " can not be open!\n";
		return 0;
	}

	g_fileIn.seekg(0, ios::end);
	std::streampos ps = g_fileIn.tellg();
	g_nFileSize = ps;
	g_fileIn.seekg(0, ios_base::beg);

	g_pBufferIn = new unsigned char[g_nFileSize];
	g_pBufferOut = new unsigned char[g_nFileSize];
	if (g_pBufferIn == NULL && g_pBufferOut == NULL)
		return 0;

	g_fileIn.read((char *)g_pBufferIn, g_nFileSize);
	if (g_nFileSize != g_fileIn.gcount())
		return 0;

	return 1;
}

int Release()
{
	delete g_pBufferIn;
	delete g_pBufferOut;

	g_fileIn.close();

	return 1;
}

int ConvertH264()
{
	int nOffset = 0;
	int count = 0;
	unsigned int nTimeStamp = 0;

	g_cnvt.Start(false, true);

	while (1) {
		int nNaluSize = 0;
		if (GetOneNalu(g_pBufferIn + nOffset, g_nFileSize - nOffset,
					   g_pBufferOut, nNaluSize) == 0)
			break;

		g_cnvt.ConvertH264(g_pBufferOut, nNaluSize, nTimeStamp);

		if (g_pBufferOut[4] != 0x67 && g_pBufferOut[4] != 0x68) {
			nTimeStamp += 33;
		}

		nOffset += nNaluSize;

		if (nOffset >= g_nFileSize - 4) {
			break;
		}

		count++;
	}

	g_cnvt.Stop();
	
	DumpFlv(&g_cnvt, "h264.flv");

	return 1;
}

int ConvertAAC()
{
	int nOffset = 0;
	int count = 0;
	unsigned int nTimeStamp = 0;

	g_cnvt.Start(true, false);

	while (1) {
		int nAACFrameSize = 0;
		if (GetOneAACFrame(g_pBufferIn + nOffset, g_nFileSize - nOffset,
						   g_pBufferOut, nAACFrameSize) == 0)
			break;

		printf("nAACFrameSize = %d\n", nAACFrameSize);
		g_cnvt.ConvertAAC(g_pBufferOut, nAACFrameSize, nTimeStamp);

		nTimeStamp += double (1024 * 1000) / double (44100);
		nOffset += nAACFrameSize;

		if (nOffset >= g_nFileSize - 4) {
			break;
		}

		count++;
	}
	
	g_cnvt.Stop();

	DumpFlv(&g_cnvt, "aac.flv");

	return 1;
}

int main(int argc, char *argv[])
{
	if (argc != 3) {
		cout << "Usage:\n\t" << "converter" << " [mode] [h.264 or aac file]" << endl;
		cout << "\tmode = 1 is h.264 to flv" << endl;
		cout << "\tmode = 2 is aac to flv\n" << endl;
		return 0;
	}

	if (Initialize(argc, argv) == 0)
		return 0;

	if (g_mode == 1)
		ConvertH264();

	if (g_mode == 2)
		ConvertAAC();

	Release();

	return 1;
}
#endif


