#pragma once
#ifndef AUDIO_H
#define AUDIO_H

#include "sw.h"

namespace SouthwestEngine {
	class AudioSystem {
	private:
		static FMOD::System* __fmodSystem;
	public:
		static FMOD_RESULT Initialize();
		static FMOD::System* GetSystem();
		static void Update();
		static void Stop();
	};
}

#endif