#ifndef SOUND_H
#define SOUND_H

#include <iostream>
#include <string>
#include <unordered_map>

#ifdef _WIN32
	#include <SDL_mixer.h>
#else
	#include <SDL2/SDL_mixer.h>
#endif

using std::string;
using std::unordered_map;
using std::cout;
using std::endl;

class Sound
{
    public:
        Sound();
        Sound(string file);
        void Play (int times);
        void Stop ();
        void Open (string file);
        bool IsOpen ();
        static void Clear();
    protected:
        /* vazio */
    private:
        string file;
        Mix_Chunk* chunk;
        int channel;
        static unordered_map<string, Mix_Chunk*> assetTable;

};

#endif // SOUND_H

