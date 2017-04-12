#include "../include/Music.h"


unordered_map<string, Mix_Music*> Music::assetTable;
const int ms = 100;
Music::Music()
{
    music = NULL;
    volume = MIX_MAX_VOLUME;
    VolumeUpdate(volume);
}

Music::Music(string file)
{
    Open(file);
}

void Music::Play (int times)
{
    //se times == -1, a musica repete infinitamente
    int erro = Mix_PlayMusic(music, times);
    if(erro == -1){//se houve um erro
        cout << endl << "Erro em Music::Play(): Mix_PlayMusic() retornou -1" << endl;
        cout << SDL_GetError() << endl;
    }
}

void Music::Stop ()
{
    Mix_FadeOutMusic(ms);
}

void Music::Open (string file)
{
    if ( assetTable.find(file) != assetTable.end()){//existe uma textura com esse endereco
            music = assetTable.find(file)->second;//usa ela própria
    }else{//se não existe ainda
        music = Mix_LoadMUS( file.c_str() );//carrega
        if(music == NULL){
            cout << endl << "Erro em Music::Open(): Mix_LoadMUS() retornou NULL" << endl;
            cout << SDL_GetError() << endl;
        }
        assetTable.emplace(file, music);//e adiciona na tabela
        #ifdef DEBUG
        cout << "Music: " << file << " carregado - ";
        cout << "MusicTableSize: " << assetTable.size() << endl;
        #endif // DEBUG
    }
}

bool Music::IsOpen ()
{
    if(music != NULL) return true;
    return false;
}

void Music::Clear()
{
    for(unordered_map<string, Mix_Music*>::iterator aux = assetTable.begin(); aux != assetTable.end(); aux++){
            Mix_FreeMusic(aux->second);
    }
    assetTable.clear();
}

void Music::SetVolume(int volume)
{
    this-> volume = Mix_VolumeMusic(volume);
}

void Music::VolumeUpdate (int increment)
{
    if(volume + increment > MIX_MAX_VOLUME) volume = MIX_MAX_VOLUME;
    else if(volume + increment < 0) volume = 0;
    else (this->volume) = Mix_VolumeMusic( (this->volume) + increment ) + increment ;
}
