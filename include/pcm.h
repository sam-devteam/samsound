/*
 * This file is part of SAM-Sound
 *
 * SAM-Sound is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later version.
 *
 * SAM-Sound is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>.
*/


#include <alsa/asoundlib.h>

#ifndef SAMSOUND_PCM_H
#define SAMSOUND_PCM_H

typedef struct SAM_SoundHandle {
    snd_pcm_t* pcm_handle;
    snd_pcm_uframes_t frames;
    unsigned int periodTime;
    int channels, sampleRate;
} SAM_SoundHandle;

typedef struct SAM_SoundBuffer {
    char * buffer;
    int buffer_size;
    int buffer_offset;

} SAM_SoundBuffer;

typedef enum SAM_StreamType {
    SAM_STREAM_PLAYBACK = 1,

    SAM_STREAM_CAPTURE = 2
} SAM_StreamType;

SAM_SoundHandle* SAM_openSoundDevice(const char* deviceName, SAM_StreamType streamType, int channels, unsigned int sampleRate);
SAM_SoundBuffer* SAM_setSoundBuffer(SAM_SoundHandle* soundHandle);

void SAM_displayInfomation(SAM_SoundHandle* soundHandle);

void SAM_freeSoundHandle(SAM_SoundHandle* soundHandle);
void SAM_freeSoundBuffer(SAM_SoundBuffer* soundBuffer);


#endif //SAMSOUND_PCM_H
