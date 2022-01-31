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


#include "samsound.h"
#include "pcm.h"
#include <alsa/asoundlib.h>

SAM_SoundHandle* pcmHandle;

void SAM_soundInit() {
    pcmHandle = SAM_openSoundDevice("default", SAM_STREAM_PLAYBACK, 2, 44100);
}

void SAM_play() {

}

