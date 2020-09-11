#pragma once
#ifndef FILEUTILS_H
#define FILEUTILS_H

#include "sw.h"

namespace SouthwestEngine {
	class FileUtils {
	private:
		// No
		FileUtils();
	public:
		static char* ReadEntireFile(const char* path);
	};
}

#endif