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


#include "stdio.h"

#ifndef EXAMPLE_WAVE_H
#define EXAMPLE_WAVE_H

// WAVE file header format
typedef struct WaveHeader {
    unsigned char riff[4];                      // RIFF string
    unsigned int overall_size;               // overall size of file in bytes
    unsigned char wave[4];                      // WAVE string
    unsigned char fmt_chunk_marker[4];          // fmt string with trailing null char
    unsigned int length_of_fmt;                 // length of the format data
    unsigned int format_type;                   // format type. 1-PCM, 3- IEEE float, 6 - 8bit A law, 7 - 8bit mu law
    unsigned int channels;                      // no.of channels
    unsigned int sample_rate;
    unsigned int byterate;                      // SampleRate * NumChannels * BitsPerSample/8
    unsigned int block_align;                   // NumChannels * BitsPerSample/8
    unsigned int bits_per_sample;               // bits per sample, 8- 8bits, 16- 16 bits etc
    unsigned char data_chunk_header[4];        // DATA string or FLLR string
    unsigned int data_size;                     // NumSamples * NumChannels * BitsPerSample/8 - size of the next chunk that will be read
} WaveHeader;

FILE* ptr = fopen("sam.wav", "rb");

struct WaveHeader waveHeader;

unsigned char buffer4[4];
unsigned char buffer2[2];

// read the wave file header data
fread(waveHeader.riff, sizeof(waveHeader.riff), 1, ptr);

fread(buffer4, sizeof(buffer4), 1, ptr);
printf("%u %u %u %u\n", buffer4[0], buffer4[1], buffer4[2], buffer4[3]);

// convert little endian to big endian 4 byte int
waveHeader.overall_size  =
buffer4[0] |
(buffer4[1]<<8) |
(buffer4[2]<<16) |
(buffer4[3]<<24);

printf("(5-8) Overall size: bytes:%u, Kb:%u \n", waveHeader.overall_size, waveHeader.overall_size/1024);


fread(waveHeader.wave, sizeof(waveHeader.wave), 1, ptr);
printf("(9-12) Wave marker: %s\n", waveHeader.wave);

fread(waveHeader.fmt_chunk_marker, sizeof(waveHeader.fmt_chunk_marker), 1, ptr);
printf("(13-16) Fmt marker: %s\n", waveHeader.fmt_chunk_marker);

fread(buffer4, sizeof(buffer4), 1, ptr);
printf("%u %u %u %u\n", buffer4[0], buffer4[1], buffer4[2], buffer4[3]);

// convert little endian to big endian 4 byte integer
waveHeader.length_of_fmt = buffer4[0] |
                           (buffer4[1] << 8) |
                           (buffer4[2] << 16) |
                           (buffer4[3] << 24);
printf("(17-20) Length of Fmt header: %u \n", waveHeader.length_of_fmt);

fread(buffer2, sizeof(buffer2), 1, ptr); printf("%u %u \n", buffer2[0], buffer2[1]);

waveHeader.format_type = buffer2[0] | (buffer2[1] << 8);
char format_name[10] = "";
if (waveHeader.format_type == 1)
strcpy(format_name,"PCM");
else if (waveHeader.format_type == 6)
strcpy(format_name, "A-law");
else if (waveHeader.format_type == 7)
strcpy(format_name, "Mu-law");

printf("(21-22) Format type: %u %s \n", waveHeader.format_type, format_name);

fread(buffer2, sizeof(buffer2), 1, ptr);
printf("%u %u \n", buffer2[0], buffer2[1]);

waveHeader.channels = buffer2[0] | (buffer2[1] << 8);
printf("(23-24) Channels: %u \n", waveHeader.channels);

fread(buffer4, sizeof(buffer4), 1, ptr);
printf("%u %u %u %u\n", buffer4[0], buffer4[1], buffer4[2], buffer4[3]);

waveHeader.sample_rate =
buffer4[0] |
(buffer4[1] << 8) |
(buffer4[2] << 16) |
(buffer4[3] << 24);

printf("(25-28) Sample rate: %u\n", waveHeader.sample_rate);

fread(buffer4, sizeof(buffer4), 1, ptr);
printf("%u %u %u %u\n", buffer4[0], buffer4[1], buffer4[2], buffer4[3]);

waveHeader.byterate  =
buffer4[0] |
(buffer4[1] << 8) |
(buffer4[2] << 16) |
(buffer4[3] << 24);

printf("(29-32) Byte Rate: %u , Bit Rate:%u\n", waveHeader.byterate, waveHeader.byterate*8);



fread(buffer2, sizeof(buffer2), 1, ptr);
printf("%u %u \n", buffer2[0], buffer2[1]);

waveHeader.block_align =
buffer2[0] |
(buffer2[1] << 8);
printf("(33-34) Block Alignment: %u \n", waveHeader.block_align);

fread(buffer2, sizeof(buffer2), 1, ptr);
printf("%u %u \n", buffer2[0], buffer2[1]);

waveHeader.bits_per_sample =
buffer2[0] |
(buffer2[1] << 8);

printf("(35-36) Bits per sample: %u \n", waveHeader.bits_per_sample);



fread(waveHeader.data_chunk_header, sizeof(waveHeader.data_chunk_header), 1, ptr);
printf("(37-40) Data Marker: %s \n", waveHeader.data_chunk_header);


fread(buffer4, sizeof(buffer4), 1, ptr);
printf("%u %u %u %u\n", buffer4[0], buffer4[1], buffer4[2], buffer4[3]);

waveHeader.data_size = buffer4[0] |
                       (buffer4[1] << 8) |
                       (buffer4[2] << 16) |
                       (buffer4[3] << 24 );
printf("(41-44) Size of data chunk: %u \n", waveHeader.data_size);


// calculate no.of samples
long num_samples = (8 * waveHeader.data_size) / (waveHeader.channels * waveHeader.bits_per_sample);

printf("Number of samples:%lu \n", num_samples);

long size_of_each_sample = (waveHeader.channels * waveHeader.bits_per_sample) / 8;

printf("Size of each sample:%ld bytes\n", size_of_each_sample);

// calculate duration of file
float duration_in_seconds = (float) waveHeader.overall_size / waveHeader.byterate;
printf("Approx.Duration in seconds=%f\n", duration_in_seconds);
seconds = (int)duration_in_seconds;

printf("seconds: %d\n", seconds);

#endif //EXAMPLE_WAVE_H
