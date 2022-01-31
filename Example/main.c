#include <stdio.h>
#include <stdlib.h>

#include "pcm.h"

int main(int argc, char * argv[]) {

    SAM_SoundHandle* soundHandle = SAM_openSoundDevice("default", SAM_STREAM_PLAYBACK, 2, 44100);

    SAM_displayInfomation(soundHandle);

    SAM_SoundBuffer* soundBuffer = SAM_setSoundBuffer(soundHandle);

    long pcm;
    unsigned int seconds, loops;

    seconds = 100;

    FILE* ptr = fopen("sam.wav", "rb");


    for (loops = (seconds * 1000000) / soundHandle->periodTime; loops > 0; loops--) {
        soundBuffer->buffer_offset++;
        fread(soundBuffer->buffer, soundBuffer->buffer_size, 1, ptr);
        fseek(ptr, soundBuffer->buffer_size*soundBuffer->buffer_offset, SEEK_SET);

        pcm = snd_pcm_writei(soundHandle->pcm_handle, soundBuffer->buffer,  soundHandle->frames);
        if (pcm < 0) {
            printf("ERROR. Can't write to PCM device. %s\n", snd_strerror((int) pcm));
        }
    }

    SAM_freeSoundHandle(soundHandle);
    SAM_freeSoundBuffer(soundBuffer);

    return 0;
}