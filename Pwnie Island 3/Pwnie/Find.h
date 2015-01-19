#pragma once

class Find
{
public:
	unsigned long Pattern(unsigned char *bMask, char * szMask, unsigned long dwAddress, unsigned long dwLen)
	{
		for (unsigned long i = 0; i < dwLen; i++)
			if (_DataCompare((unsigned char*)(dwAddress + i), bMask, szMask))
				return (unsigned long)(dwAddress + i);

		return 0;
	}

private:
	bool _DataCompare(const unsigned char* pData, const unsigned char* bMask, const char* szMask)
	{
		for (; *szMask; ++szMask, ++pData, ++bMask)
			if (*szMask == '\x01' && *pData != *bMask)
				return false;

		return (*szMask) == 0;
	}
};

extern Find find;