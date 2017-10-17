#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <math.h>
#include "kiss_fft.h"
#include "sndfile.h"

#define WIN 512

int main()
{
    char *music_file = "C:/voice.wav";
    SNDFILE *infile;
    SF_INFO      sfinfo;
    //int          readcount;

    short buf[WIN * 2];
    int nfft = WIN;
    double intensity = 0;
    kiss_fft_cfg cfg;
    kiss_fft_cpx cx_in[WIN];
    kiss_fft_cpx cx_out[WIN];
    short *sh;

    cfg = kiss_fft_alloc(nfft, 0, 0, 0);


    if (!( infile = sf_open(music_file, SFM_READ, &sfinfo) ))
    {   /* Open failed so print an error message. */
        printf("Not able to open input file %s.\n", "input.wav");
        /* Print the error message fron libsndfile. */
        sf_perror(NULL);
        return  1;
    }

    while ((sf_read_short(infile, buf, WIN)))//fread(buf, 1, WIN * 2, in)
    {
        //system("cls");

        for (int i = 0;i<WIN;i++) {
            sh = (short *)&buf[i * 2];
            cx_in[i].r = (float) (((double)*sh) / 32768.0);
            cx_in[i].i = 0.0;
        }

        kiss_fft(cfg, cx_in, cx_out);
        //Display the value of a position
        int position = 511;
        intensity = sqrt(pow(cx_out[position].r, 2) + pow(cx_out[position].i, 2));
        printf("%9.4f\n", intensity);

        //Display all values
        /*
        for (i = 0;i<WIN;i++) {
            //printf("Joe: cx_out[i].r:%f\n", cx_out[i].r);
            //printf("Joe: cx_out[i].i:%f\n", cx_out[i].i);
            intensity = sqrt(pow(cx_out[i].r,2) + pow(cx_out[i].i,2));
            printf("%d - %9.4f\n", i, intensity);
        }
        */

    }
    sf_close(infile);
    free(cfg);
    int temp;
    scanf_s("%d", &temp);

    return 0;
}
