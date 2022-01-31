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


#ifndef SAMSOUND_H
#define SAMSOUND_H
#ifdef __cplusplus
extern "C" {
#endif

void SAM_soundInit();

static void SAM_play();

static void SAM_record();

static void SAM_stop();


#ifdef __cplusplus
}
#endif
#endif //SAMSOUND_H
