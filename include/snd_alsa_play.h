#ifndef SND_ALSA_PLAY_INCLUDED
#define SND_ALSA_PLAY_INCLUDED

#include "../kiss_fft130/kiss_fft.h"

//#include "library.h"
//#include "func_matryca.h"
#include "../libsndfile/src/sndfile.h"

#include <alsa/asoundlib.h>

#define WIN 512


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#if HAVE_UNISTD_H
#include <unistd.h>
#else
//#include "sf_unistd.h"
#endif

#include <sndfile.h>

//#include "common.h"

#if HAVE_ALSA_ASOUNDLIB_H
	#define ALSA_PCM_NEW_HW_PARAMS_API
	#define ALSA_PCM_NEW_SW_PARAMS_API
	#include <alsa/asoundlib.h>
	#include <sys/time.h>
#endif

#if defined (__ANDROID__)

#elif defined (__linux__) || defined (__FreeBSD_kernel__) || defined (__FreeBSD__)
	#include 	<fcntl.h>
	#include 	<sys/ioctl.h>
	#include 	<sys/soundcard.h>

#elif (defined (__MACH__) && defined (__APPLE__))
	#include <AvailabilityMacros.h>
	#include <Availability.h>

#elif HAVE_SNDIO_H
	#include <sndio.h>

#elif (defined (sun) && defined (unix))
	#include <fcntl.h>
	#include <sys/ioctl.h>
	#include <sys/audioio.h>

#elif (OS_IS_WIN32 == 1)
	#include <windows.h>
	#include <mmsystem.h>

#endif

#define	SIGNED_SIZEOF(x)	((int) sizeof (x))
#define	BUFFER_LEN			(2048)


static snd_pcm_t * alsa_open (int channels, unsigned srate, int realtime) ;
static int alsa_write_float ( int fd, uint32_t *xRGB, snd_pcm_t *alsa_dev, float *data, int frames, int channels, kiss_fft_cfg &cfg );
void color_state( uint32_t *xRGB, unsigned vol, unsigned column, unsigned power );


static void
alsa_play ( int fd, uint32_t *xRGB, string music )
{
    static float buffer [BUFFER_LEN] ;
	SNDFILE *sndfile ;
	SF_INFO sfinfo ;snd_pcm_t * alsa_dev ;
	int		k, readcount, subformat ;

//    string a =  "/home/pi/projects/smart_led_board/audio/MSin44W16-13.WAV";
//	argv[1] = (char*)(music).c_str();

	for (k = 1 ; k < 2 ; k++)
	{	memset (&sfinfo, 0, sizeof (sfinfo)) ;

		printf ("Playing %s\n", music.c_str() ) ;
		if (! (sndfile = sf_open (music.c_str(), SFM_READ, &sfinfo)))
		{	puts (sf_strerror (NULL)) ;
			continue ;
			} ;

		if (sfinfo.channels < 1 || sfinfo.channels > 2)
		{	printf ("Error : channels = %d.\n", sfinfo.channels) ;
			continue ;
			} ;

		if ((alsa_dev = alsa_open (sfinfo.channels, (unsigned) sfinfo.samplerate, SF_FALSE)) == NULL)
//		if ((alsa_dev = alsa_open (sfinfo.channels, (unsigned) sfinfo.samplerate, SF_TRUE)) == NULL)
			continue ;

		subformat = sfinfo.format & SF_FORMAT_SUBMASK ;

        kiss_fft_cfg cfg = kiss_fft_alloc(WIN, 0, 0, 0); // init FFT

		if (subformat == SF_FORMAT_FLOAT || subformat == SF_FORMAT_DOUBLE)
		{	double	scale ;
			int 	m ;

			sf_command (sndfile, SFC_CALC_SIGNAL_MAX, &scale, sizeof (scale)) ;
			if (scale < 1e-10)
				scale = 1.0 ;
			else
				scale = 32700.0 / scale ;

			while ((readcount = sf_read_float (sndfile, buffer, BUFFER_LEN)))
			{	for (m = 0 ; m < readcount ; m++)
					buffer [m] *= scale ;
				alsa_write_float ( fd, xRGB, alsa_dev, buffer, BUFFER_LEN / sfinfo.channels, sfinfo.channels, cfg);
				} ;
			}
		else
		{	while ((readcount = sf_read_float (sndfile, buffer, BUFFER_LEN)))
				alsa_write_float ( fd, xRGB,alsa_dev, buffer, BUFFER_LEN / sfinfo.channels, sfinfo.channels, cfg);
			} ;

		snd_pcm_drain (alsa_dev) ;
		snd_pcm_close (alsa_dev) ;

		sf_close (sndfile) ;
		} ;

	return ;
} /* alsa_play */



static snd_pcm_t *
alsa_open (int channels, unsigned samplerate, int realtime)
{	const char * device = "default" ;
	snd_pcm_t *alsa_dev = NULL ;
	snd_pcm_hw_params_t *hw_params ;
	snd_pcm_uframes_t buffer_size ;
	snd_pcm_uframes_t alsa_period_size, alsa_buffer_frames ;
	snd_pcm_sw_params_t *sw_params ;

	int err ;

	if (realtime)
	{	alsa_period_size = 256 ;
		alsa_buffer_frames = 3 * alsa_period_size ;
		}
	else
	{	alsa_period_size = 1024 ;
		alsa_buffer_frames = 4 * alsa_period_size ;
		} ;

	if ((err = snd_pcm_open (&alsa_dev, device, SND_PCM_STREAM_PLAYBACK, 0)) < 0)
	{	fprintf (stderr, "cannot open audio device \"%s\" (%s)\n", device, snd_strerror (err)) ;
		goto catch_error ;
		} ;

	snd_pcm_nonblock (alsa_dev, 0) ;

	if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0)
	{	fprintf (stderr, "cannot allocate hardware parameter structure (%s)\n", snd_strerror (err)) ;
		goto catch_error ;
		} ;

	if ((err = snd_pcm_hw_params_any (alsa_dev, hw_params)) < 0)
	{	fprintf (stderr, "cannot initialize hardware parameter structure (%s)\n", snd_strerror (err)) ;
		goto catch_error ;
		} ;

	if ((err = snd_pcm_hw_params_set_access (alsa_dev, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0)
	{	fprintf (stderr, "cannot set access type (%s)\n", snd_strerror (err)) ;
		goto catch_error ;
		} ;

	if ((err = snd_pcm_hw_params_set_format (alsa_dev, hw_params, SND_PCM_FORMAT_FLOAT)) < 0)
	{	fprintf (stderr, "cannot set sample format (%s)\n", snd_strerror (err)) ;
		goto catch_error ;
		} ;

	if ((err = snd_pcm_hw_params_set_rate_near (alsa_dev, hw_params, &samplerate, 0)) < 0)
	{	fprintf (stderr, "cannot set sample rate (%s)\n", snd_strerror (err)) ;
		goto catch_error ;
		} ;

	if ((err = snd_pcm_hw_params_set_channels (alsa_dev, hw_params, channels)) < 0)
	{	fprintf (stderr, "cannot set channel count (%s)\n", snd_strerror (err)) ;
		goto catch_error ;
		} ;

	if ((err = snd_pcm_hw_params_set_buffer_size_near (alsa_dev, hw_params, &alsa_buffer_frames)) < 0)
	{	fprintf (stderr, "cannot set buffer size (%s)\n", snd_strerror (err)) ;
		goto catch_error ;
		} ;

	if ((err = snd_pcm_hw_params_set_period_size_near (alsa_dev, hw_params, &alsa_period_size, 0)) < 0)
	{	fprintf (stderr, "cannot set period size (%s)\n", snd_strerror (err)) ;
		goto catch_error ;
		} ;

	if ((err = snd_pcm_hw_params (alsa_dev, hw_params)) < 0)
	{	fprintf (stderr, "cannot set parameters (%s)\n", snd_strerror (err)) ;
		goto catch_error ;
		} ;

	/* extra check: if we have only one period, this code won't work */
	snd_pcm_hw_params_get_period_size (hw_params, &alsa_period_size, 0) ;
	snd_pcm_hw_params_get_buffer_size (hw_params, &buffer_size) ;
	if (alsa_period_size == buffer_size)
	{	fprintf (stderr, "Can't use period equal to buffer size (%lu == %lu)", alsa_period_size, buffer_size) ;
		goto catch_error ;
		} ;

	snd_pcm_hw_params_free (hw_params) ;

	if ((err = snd_pcm_sw_params_malloc (&sw_params)) != 0)
	{	fprintf (stderr, "%s: snd_pcm_sw_params_malloc: %s", __func__, snd_strerror (err)) ;
		goto catch_error ;
		} ;

	if ((err = snd_pcm_sw_params_current (alsa_dev, sw_params)) != 0)
	{	fprintf (stderr, "%s: snd_pcm_sw_params_current: %s", __func__, snd_strerror (err)) ;
		goto catch_error ;
		} ;

	/* note: set start threshold to delay start until the ring buffer is full */
	snd_pcm_sw_params_current (alsa_dev, sw_params) ;

	if ((err = snd_pcm_sw_params_set_start_threshold (alsa_dev, sw_params, buffer_size)) < 0)
	{	fprintf (stderr, "cannot set start threshold (%s)\n", snd_strerror (err)) ;
		goto catch_error ;
		} ;

	if ((err = snd_pcm_sw_params (alsa_dev, sw_params)) != 0)
	{	fprintf (stderr, "%s: snd_pcm_sw_params: %s", __func__, snd_strerror (err)) ;
		goto catch_error ;
		} ;

	snd_pcm_sw_params_free (sw_params) ;

	snd_pcm_reset (alsa_dev) ;

catch_error :

	if (err < 0 && alsa_dev != NULL)
	{	snd_pcm_close (alsa_dev) ;
		return NULL ;
		} ;

	return alsa_dev ;
} /* alsa_open */

// ----------------------------------------------------------------------------

void draw_colors( int fd, uint32_t *xRGB, kiss_fft_cpx cx_out[WIN], double &maximum, int pass)
{
        memset( xRGB, 0x00, PIXEL_COUNT * 4 );

            for ( int i = 0; i < 16; i++ )
            {
                for ( int x = 0; x < 16; x++ )
                {
                    int index = pass*i+x*30;

                    double intensity = sqrt(pow(cx_out[index].r, 2) + pow(cx_out[index].i, 2));;

                    intensity = intensity / maximum * 16;

                    int pos = 0;

                    if ( intensity > 15 )
                        pos = 15;
                    else
                        pos = intensity;

                    color_state( xRGB, pos, x , 1);
//
                   // printf( "%f\n", pos);

//                    xRGB[ x*16 + pos ] = 0x010001;

                }
//                printf("%9.4f\n", intensity);
            }

        ws2812b_update(fd, xRGB);
}

// ----------------------------------------------------------------------------

void proces_audio_fft( int fd, uint32_t *xRGB, float *data, kiss_fft_cfg &cfg )
{
 double maxValue = 0;

    short buf[WIN * 2];
    int nfft = WIN;
    double intensity = 0;

    kiss_fft_cpx cx_in[WIN];
    kiss_fft_cpx cx_out[WIN];
    short *sh;

    static double maximum(20.0);
    {
        for (int i = 0;i<WIN;i++) {
            sh = (short *)&data[i * 2];
            cx_in[i].r = (float) (((double)*sh) / 32768.0);
            cx_in[i].i = 0.0;
        }


    signal( SIGINT, Awaryjne_zatrzymanie );


        kiss_fft( cfg, cx_in, cx_out );
        //Display the value of a position
        int position = 0;
//        intensity = sqrt(pow(cx_out[position].r, 2) + pow(cx_out[position].i, 2));
//        printf("%9.4f\n", intensity);

        double curr = sqrt(pow(cx_out[0].r, 2) + pow(cx_out[0].i, 2));
        maximum = ( curr > maximum ) ? curr : maximum;

        int pass = 1;
//        for ( ; pass < WIN / 255; pass++ )
        {
            draw_colors( fd, xRGB, cx_out, maximum, pass );
        }
//        for (int i = 0; i < WIN; i+=512)
//        {
//            double curr = sqrt(pow(cx_out[i].r, 2) + pow(cx_out[i].i, 2));
//            maximum = ( curr > maximum ) ? curr : maximum;
//        }

        //Display all values

        for (int i = 0;i<WIN;i++) {
//            printf("Joe: cx_out[i].r:%f\n", cx_out[i].r);
//            printf("Joe: cx_out[i].i:%f\n", cx_out[i].i);
//            intensity = sqrt(pow(cx_out[i].r,2) + pow(cx_out[i].i,2));
//            printf("%d - %9.4f\n", i, intensity);
        }
    }

//    printf("Maximum: %9.4f\n", maximum);

}

// ---------------------------------------------------------------------------------

static int
alsa_write_float ( int fd, uint32_t *xRGB, snd_pcm_t *alsa_dev, float *data, int frames, int channels, kiss_fft_cfg &cfg )
{	static	int epipe_count = 0 ;

	int total = 0 ;
	int retval ;

	if (epipe_count > 0)
		epipe_count -- ;

	while (total < frames)
	{
        retval = snd_pcm_writei (alsa_dev, data + total * channels, frames - total) ;
//        printf( "%d\n", total);

        proces_audio_fft( fd, xRGB, data, cfg );

		if (retval >= 0)
		{	total += retval ;
			if (total == frames)
				return total ;

			continue ;
			} ;

		switch (retval)
		{	case -EAGAIN :
					puts ("alsa_write_float: EAGAIN") ;
					continue ;
					break ;

			case -EPIPE :
					if (epipe_count > 0)
					{	printf ("alsa_write_float: EPIPE %d\n", epipe_count) ;
						if (epipe_count > 140)
							return retval ;
						} ;
					epipe_count += 100 ;

#if 0
					if (0)
					{	snd_pcm_status_t *status ;
						snd_pcm_status_alloca (&status) ;
						if ((retval = snd_pcm_status (alsa_dev, status)) < 0)
							fprintf (stderr, "alsa_out: xrun. can't determine length\n") ;
						else if (snd_pcm_status_get_state (status) == SND_PCM_STATE_XRUN)
						{	struct timeval now, diff, tstamp ;
							gettimeofday (&now, 0) ;
							snd_pcm_status_get_trigger_tstamp (status, &tstamp) ;
							timersub (&now, &tstamp, &diff) ;
							fprintf (stderr, "alsa_write_float xrun: of at least %.3f msecs. resetting stream\n",
									diff.tv_sec * 1000 + diff.tv_usec / 1000.0) ;
							}
						else
							fprintf (stderr, "alsa_write_float: xrun. can't determine length\n") ;
						} ;
#endif

					snd_pcm_prepare (alsa_dev) ;
					break ;

			case -EBADFD :
					fprintf (stderr, "alsa_write_float: Bad PCM state.n") ;
					return 0 ;
					break ;

			case -ESTRPIPE :
					fprintf (stderr, "alsa_write_float: Suspend event.n") ;
					return 0 ;
					break ;

			case -EIO :
					puts ("alsa_write_float: EIO") ;
					return 0 ;

			default :
					fprintf (stderr, "alsa_write_float: retval = %d\n", retval) ;
					return 0 ;
					break ;
			} ; /* switch */
		} ; /* while */

	return total ;
} /* alsa_write_float */


// ----------------------------------------------------------------------------


void color_state( uint32_t *xRGB, unsigned vol, unsigned column = 0, unsigned power = 1)
{
    for(int i = 0; i <= vol; i++)
    {
        if      ( i <= 10 )
            xRGB[ (15-i) * 16 + column ] = 0x000100 << power;
        else if ( i <= 14 )
            xRGB[ (16-i) * 16 + column ] = 0x010100 << power;
        else if ( i <= 16 )
            xRGB[ (16-i) * 16 + column ] = 0x010000 << power;
        else
            cout << "\n color_state() error. vol = " << vol << endl;
    }
}


#endif // SND_ALSA_PLAY_INCLUDED
