#pragma once
#if _DEBUG
#ifndef ASSETCOMPILE_H

#include "sw.h"

namespace SouthwestEngine {
	class AssetCompiler {
		// compile the Contents folder into archive files and a file table
		static void Compile();
	};
}

#endif
#endif