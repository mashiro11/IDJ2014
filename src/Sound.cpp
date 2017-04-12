#include "../include/Sound.h"

unordered_map<string, Mix_Chunk*> Sound::assetTable;
Sound::Sound()
{
    chunk = NULL;
}

Sound::Sound(string file)
{
    Open(file);
}

void Sound::Play (int times)
{
    //se channel == -1, o canal em que o som é colocado é administrado pela própria função
    channel = Mix_PlayChannel(-1, chunk, times);
    if(channel == -1){//se houve um erro
        cout << endl << "Erro em Music::Play(): Mix_PlayMusic() retornou -1" << endl;
        cout << SDL_GetError() << endl;
    }
}

void Sound::Stop ()
{
    Mix_HaltChannel(channel);
}

void Sound::Open (string file)
{
    if ( assetTable.find(file) != assetTable.end()){//existe uma textura com esse endereco
            chunk = assetTable.find(file)->second;//usa ela própria
    }else{//se não existe ainda
        chunk = Mix_LoadWAV( file.c_str() );//carrega
        if(chunk == NULL){
            cout << endl << "Erro em Music::Open(): Mix_LoadMUS() retornou NULL" << endl;
            cout << SDL_GetError() << endl;
        }
        assetTable.emplace(file, chunk);//e adiciona na tabela
        #ifdef DEBUG
        cout << "Chunk: " << file << " carregado - ";
        cout << "MusicTableSize: " << assetTable.size() << endl;
        #endif // DEBUG
    }
}

bool Sound::IsOpen ()
{
    if(chunk != NULL) return true;
    return false;
}

void Sound::Clear()
{
    for(unordered_map<string, Mix_Chunk*>::iterator aux = assetTable.begin(); aux != assetTable.end(); aux++){
            Mix_FreeChunk(aux->second);
    }
    assetTable.clear();
}
