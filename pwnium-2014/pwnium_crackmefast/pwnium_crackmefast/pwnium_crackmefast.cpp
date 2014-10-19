// pwnium_crackmefast.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>

#pragma comment(lib, "urlmon")

#define XORPASS_SIZE 8

DWORD dwXorPassword[XORPASS_SIZE];

CHAR szDecodedPass[XORPASS_SIZE + 1];

BOOL SubmitData() 
{
	char szFullUrl[MAX_PATH] = {0};

	sprintf_s(szFullUrl, "http://41.231.53.44:9393/check.php?p=%s", szDecodedPass);

	return SUCCEEDED(URLDownloadToFileA(NULL, szFullUrl, "C:\\Users\\s0beit\\Documents\\Visual Studio 2012\\Projects\\pwnium_crackmefast\\Debug\\result.txt", 0, NULL));

	return TRUE;
}

BOOL DownloadFileToDisk()
{
	return SUCCEEDED(URLDownloadToFile(NULL, _T("http://41.231.53.44:9393/"), _T("C:\\Users\\s0beit\\Documents\\Visual Studio 2012\\Projects\\pwnium_crackmefast\\Debug\\hackme.bin"), 0, NULL));
}

BOOL ObtainDecodeInformation()
{
	BOOL bReturn = FALSE;

	memset(dwXorPassword, 0, sizeof(dwXorPassword));
	memset(szDecodedPass, 0, sizeof(szDecodedPass));

	HANDLE hFile = CreateFileA("C:\\Users\\s0beit\\Documents\\Visual Studio 2012\\Projects\\pwnium_crackmefast\\Debug\\hackme.bin",
		GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	if(hFile != INVALID_HANDLE_VALUE) {
		DWORD dwFileSize = GetFileSize(hFile, NULL), dwBytesRead = 0;

		printf("File Size: 0x%X\n", dwFileSize);

		PBYTE pbFileBuffer = new BYTE[dwFileSize];

		if(ReadFile(hFile, pbFileBuffer, dwFileSize, &dwBytesRead, NULL)) {
			DWORD dwKeyPosition = 0x1310; // Header + Offset to DWORD array

			for(DWORD i = 0; i < XORPASS_SIZE; i++) {
				printf("XOR KEY [%i]: 0x%X\n", i, ((DWORD*)(pbFileBuffer + dwKeyPosition))[i]);

				szDecodedPass[i] = (((DWORD*)(pbFileBuffer + dwKeyPosition))[i] ^ 1);
			}

			printf("Password: %s\n", szDecodedPass);

			bReturn = TRUE;
		}

		delete[] pbFileBuffer;

		CloseHandle(hFile);

	} else {
		printf("Unable to open file!\n");
	}

	return bReturn;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if(DownloadFileToDisk()) {
		if(ObtainDecodeInformation()) {
			if(SubmitData()) {
				printf("Success!!!\n");
			} else {
				printf("Failed to submit data!\n");
			}
		} else {
			printf("Failed to ObtainDecodeInformation!\n");
		}
	} else {
		printf("Failed to DownloadFileToDisk!\n");
	}

	return 0;
}

