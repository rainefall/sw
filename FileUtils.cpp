#include "FileUtils.h"

namespace SouthwestEngine {
	char* FileUtils::ReadEntireFile(const char* path) {
		char* buffer = 0;
		long length;
		FILE* f;
		fopen_s(&f, path, "rb");

		if (f)
		{
			fseek(f, 0, SEEK_END);
			length = ftell(f);
			fseek(f, 0, SEEK_SET);
			buffer = (char*)malloc(length);
			if (buffer)
			{
				fread(buffer, 1, length, f);
			}
			fclose(f);
		}

		return buffer;
	}
}