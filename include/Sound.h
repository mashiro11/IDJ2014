#ifndef SOUND_H
#define SOUND_H

#include <iostream>
#include <string>
#include <unordered_map>

#include <SDL_mixer.h>

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

