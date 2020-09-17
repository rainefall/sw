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
		/** Read file into string. */
		static inline std::string Slurp(const std::string& path) {
			std::ostringstream buf;
			std::ifstream input(path.c_str());
			buf << input.rdbuf();
			return buf.str();
		}
	};
}

#endif