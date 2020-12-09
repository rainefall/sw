#include "Audio.h"

using namespace SouthwestEngine;

FMOD::System* AudioSystem::__fmodSystem;

FMOD_RESULT AudioSystem::Initialize() {
    FMOD_RESULT result;
    result = FMOD::System_Create(&__fmodSystem); // Create the main system object.
    if (result != FMOD_RESULT::FMOD_OK)
        return result;
    result = __fmodSystem->init(512, FMOD_INIT_NORMAL, 0); // Initialize FMOD.
    return result;
}

FMOD::System* AudioSystem::GetSystem() {
    return __fmodSystem;
}

void AudioSystem::Update() {
    __fmodSystem->update();
}

void AudioSystem::Stop() {
    __fmodSystem->release();
}