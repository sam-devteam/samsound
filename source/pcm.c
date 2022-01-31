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


#include "pcm.h"
#include "stdlib.h"

SAM_SoundHandle* SAM_openSoundDevice(const char* deviceName, SAM_StreamType streamType, int channels, unsigned int sampleRate) {
    SAM_SoundHandle* tmp = (SAM_SoundHandle*) malloc(sizeof(SAM_SoundHandle));
    snd_pcm_hw_params_t* params;
    int pcm;
    enum _snd_pcm_stream stream;

    if (streamType == 1) {
        stream = SND_PCM_STREAM_PLAYBACK;
    } else if (streamType == 2) {
        stream = SND_PCM_STREAM_CAPTURE;
    }

    pcm = snd_pcm_open(&tmp->pcm_handle, deviceName,
                        stream, 0);
    if (pcm < 0)
        printf("ERROR: Can't open \"%s\" PCM device. %s\n",
               deviceName, snd_strerror(pcm));

    // allocate and set pcm params, and copy params
    snd_pcm_hw_params_alloca(&params);

    snd_pcm_hw_params_any(tmp->pcm_handle, params);
    // set access to read write interleaved
    pcm = snd_pcm_hw_params_set_access(tmp->pcm_handle, params,
                                       SND_PCM_ACCESS_RW_INTERLEAVED);
    if (pcm < 0) { printf("ERROR: Can't set interleaved mode. %s\n", snd_strerror(pcm)); }

    // set format to 16 bits
    pcm = snd_pcm_hw_params_set_format(tmp->pcm_handle, params,
                                       SND_PCM_FORMAT_S16_LE);
    if (pcm < 0) { printf("ERROR: Can't set format. %s\n", snd_strerror(pcm)); }

    // set amount of channels
    pcm = snd_pcm_hw_params_set_channels(tmp->pcm_handle, params, channels);
    if (pcm < 0) { printf("ERROR: Can't set channels number. %s\n", snd_strerror(pcm)); }

    // set sample rate
    pcm = snd_pcm_hw_params_set_rate_near(tmp->pcm_handle, params, &sampleRate, 0);
    if (pcm < 0)
        printf("ERROR: Can't set rate. %s\n", snd_strerror(pcm));

    // write the parameters
    pcm = snd_pcm_hw_params(tmp->pcm_handle, params);
    if (pcm < 0)
        printf("ERROR: Can't set harware parameters. %s\n", snd_strerror(pcm));

    // save params in variables
    unsigned int val, periodTime;

    snd_pcm_uframes_t frames;

    // get channels
    snd_pcm_hw_params_get_channels(params, &val);
    tmp->channels = (int) val;

    // get sampleRate
    snd_pcm_hw_params_get_rate(params, &val, 0);
    tmp->sampleRate = (int) val;

    // get period and period time
    snd_pcm_hw_params_get_period_size(params, &frames, 0);
    tmp->frames = frames;

    snd_pcm_hw_params_get_period_time(params, &periodTime, NULL);
    tmp->periodTime = periodTime;

    return tmp;
}

SAM_SoundBuffer* SAM_setSoundBuffer(SAM_SoundHandle* soundHandle) {
    SAM_SoundBuffer* soundBuffer = (SAM_SoundBuffer*) malloc(sizeof(SAM_SoundBuffer));
    /* Allocate buffer to hold single period */
    soundBuffer->buffer_size = soundHandle->frames * soundHandle->channels * 2;
    soundBuffer->buffer = (char *) malloc(soundBuffer->buffer_size);
    soundBuffer->buffer_offset = 0;
    printf("buff size: %i\n", soundBuffer->buffer_size);

    return soundBuffer;
}

void SAM_displayInfomation(SAM_SoundHandle* soundHandle) {
    printf("PCM DEVICE name: '%s'\n", snd_pcm_name(soundHandle->pcm_handle));

    printf("PCM DEVICE state: %s\n", snd_pcm_state_name(snd_pcm_state(soundHandle->pcm_handle)));

    printf("channels: %i ", soundHandle->channels);

    if (soundHandle->channels == 1)
        printf("(mono)");
    else if (soundHandle->channels == 2)
        printf("(stereo)");

    printf("\nsample rate: %i\n", soundHandle->sampleRate);
}

void SAM_freeSoundHandle(SAM_SoundHandle* soundHandle) {
    snd_pcm_drain(soundHandle->pcm_handle);
    snd_pcm_close(soundHandle->pcm_handle);
    free(soundHandle);
}

void SAM_freeSoundBuffer(SAM_SoundBuffer* soundBuffer) {
    free(soundBuffer->buffer);
    free(soundBuffer);
}