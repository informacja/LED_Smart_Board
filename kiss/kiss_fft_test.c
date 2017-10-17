#include "kiss_fft.h"
#include "kissfft/tools/kiss_fftr.h"

kiss_fft_cpx* copycpx(float *mat, int nframe)
{
	int i;
	kiss_fft_cpx *mat2;
	mat2=(kiss_fft_cpx*)KISS_FFT_MALLOC(sizeof(kiss_fft_cpx)*nframe);
        kiss_fft_scalar zero;
        memset(&zero,0,sizeof(zero) );
	for(i=0; i<nframe ; i++)
	{
		mat2[i].r = mat[i];
		mat2[i].i = zero;
	}
	return mat2;
}

int main(void)
{
    int i,size = 12;
    int isinverse = 1;
    float buf[size];
    float array[] = {0.1, 0.6, 0.1, 0.4, 0.5, 0, 0.8, 0.7, 0.8, 0.6, 0.1,0};  
    
    kiss_fft_cpx out_cpx[size],out[size],*cpx_buf;

    kiss_fftr_cfg fft = kiss_fftr_alloc(size*2 ,0 ,0,0);
    kiss_fftr_cfg ifft = kiss_fftr_alloc(size*2,isinverse,0,0);

    cpx_buf = copycpx(array,size);
    kiss_fftr(fft,(kiss_fft_scalar*)cpx_buf, out_cpx);
    kiss_fftri(ifft,out_cpx,(kiss_fft_scalar*)out );

    printf("Input:    tOutput:n");
    for(i=0;i<size;i++)
    {
	buf[i] = (out[i].r)/(size*2);
	printf("%ft%fn",array[i],buf[i]);
    }

    kiss_fft_cleanup();   
    free(fft);
    free(ifft);
    return 0;
    

}
