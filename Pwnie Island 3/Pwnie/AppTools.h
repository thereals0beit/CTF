#pragma once

class AppTools
{
public:
	void module(HMODULE hModule) {
		char p[MAX_PATH] = {0};
		GetModuleFileName(hModule, p, MAX_PATH);
		std::string pp = p;
		setPath(pp.substr(0, pp.find_last_of("\\") + 1));
	}

	void setPath(std::string path) {
		basepath = path;
	}

	std::string getFilePath(std::string file) {
		return basepath + file;
	}

	void writeFile(const char* filepath, const char* string) {
		HANDLE hFile = CreateFile(filepath, FILE_APPEND_DATA, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		
		if(hFile != INVALID_HANDLE_VALUE) {
			DWORD dummy = 0;
			
			WriteFile(hFile, string, strlen(string), &dummy, NULL);
			CloseHandle(hFile);
		}
	}

	void log(const char* format, ...) {
		char logBuffer[2048] = {0};

		va_list args;
		va_start(args, format);
		vsnprintf_s(logBuffer, _countof(logBuffer), _TRUNCATE, format, args);
		va_end(args);

		//writeFile(getFilePath("hook.log").c_str(), logBuffer);

		FILE* fp = NULL;

		errno_t e = fopen_s(&fp, getFilePath("hook.log").c_str(), "a");

		if (e == 0 && fp) {
			fprintf_s(fp, "%s\n", logBuffer);
			fclose(fp);
		}
	}

public:
	std::string basepath;
};

extern AppTools app;