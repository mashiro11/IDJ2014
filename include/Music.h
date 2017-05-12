#ifndef MUSIC_H
#define MUSIC_H

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
using std::iterator;
using std::cout;
using std::endl;

class Music
{
    public:
        Music ();
        Music (string file);
        void Play (int times);
        void Stop ();
        void Open (string file);
        bool IsOpen ();
        static void Clear ();

        void SetVolume (int volume);
        void VolumeUpdate (int increment);

    protected:
        /* vazio */
    private:
        int volume;
        string file;
        Mix_Music* music;
        static unordered_map<string, Mix_Music*> assetTable;
};

#endif // MUSIC_H
