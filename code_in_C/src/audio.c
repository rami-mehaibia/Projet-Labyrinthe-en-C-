#include "audio.h"

//Function that makes the wav you selected play
AudioShenanigans AUDIOLOAAAAAD(char *pathofwav, AudioShenanigans a)
{
    //printf("device at beginning : %d\n",a.dvce);
    if(a.dvce>0){
    SDL_PauseAudioDevice(a.dvce,1);
    SDL_CloseAudioDevice(a.dvce);
    SDL_FreeWAV(a.wavStart);
    }
    if (SDL_LoadWAV(pathofwav, &a.wavSpec, &a.wavStart, &a.wavLength) == NULL)
    {
        printf("Le fichier audio %s n'a pas pu être chargé !\n", pathofwav);
    }

    a.dvce = SDL_OpenAudioDevice(NULL, 0, &a.wavSpec, NULL, 0);
    if (a.dvce == 0)
    {
        printf("pas pu trouvé de device...\n");
    }
    a.success = SDL_QueueAudio(a.dvce, a.wavStart, a.wavLength);
    if (a.success != 0)
    {
        printf("Erreur de load du fichier audio %s\n", pathofwav);
    }
    SDL_PauseAudioDevice(a.dvce, 0);
    //printf("device at end : %d\n",a.dvce);
    return a;
    //printf("Length : %d\n", a.wavLength);
    
    //printf("Succes of audio : %d, loaded %s\n\n",a.success,pathofwav);
}