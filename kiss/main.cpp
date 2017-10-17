
#include "kiss_fft.h"
#include <iostream>

int main()
{
        kiss_fft_cfg cfg = kiss_fft_alloc( nfft ,is_inverse_fft ,0,0 );

        while ( true )
        {
            // put kth sample in cx_in[k].r and cx_in[k].i
            
            kiss_fft( cfg , cx_in , cx_out );
            
            // transformed. DC is in cx_out[0].r and cx_out[0].i
	} 
	
        free(cfg);

	return 0;
}
