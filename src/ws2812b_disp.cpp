#ifndef WS2812B_DISP_CPP
#define WS2812B_DISP_CPP

#include "../include/library.h"

inline int spi_init(char* dev, int * fd)
{
    *fd = open(dev, O_RDWR);
    int err = 0;

    if (fd < 0)
	return *fd; // io error

    // ustaw tryb SPI na standardowy, bez znaczenia wiÄ™kszoĹÄ‡ rzeczy
    uint8_t mode = 0;
    if (ioctl(*fd, SPI_IOC_WR_MODE, &mode) < 0)
	return err_spi_mode;

    // ustaw 8 bitĂłw na SPI. Niestety, Rpi nie obsĹuguje 9-bitowych transferĂłw
    uint8_t bits = 8;
    if ((ioctl(*fd, SPI_IOC_WR_BITS_PER_WORD, &bits)< 0) || (ioctl(*fd, SPI_IOC_RD_BITS_PER_WORD, &bits) < 0))
	return err_spi_bits;

    uint32_t speed = SPI_CLOCK;
    if ((ioctl(*fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) < 0) || (ioctl(*fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed) < 0))
	return err_spi_speed;
}

inline int spi_write(int fd, void * data, uint32_t size)
{
    int result = write(fd, data, size);
    if (result != size)
	printf("spi_write: size=%d, result=%d\n", size, result);
	return result; // line aded by puler 15.05.2017 ??
}

inline int ws2812b_reset(int fd)
{
    char bytes[WS_RST_BYTES];
    memset(bytes, WS_MK_BYTE(WS_RST, WS_RST), WS_RST_BYTES);
    if (spi_write(fd, bytes, WS_RST_BYTES) != WS_RST_BYTES)
	return  err_spi_datacount;
    return err_ok;
}

inline int ws2812b_update(int fd, uint32_t * data)
{
    uint8_t buf[SPI_MAX_SIZE];
    const uint8_t bit_coding[2] = {WS_B0, WS_B1};

    uint32_t pixel_bytes = 24 / 2; // 12 bajtĂłw na piksel, 24-bit RGB, 2 bity WS na bajt SPI
    uint32_t current_pixel = PIXEL_COUNT;
    uint32_t bytes_in_buf = 1; // uwzglednij jeden pusty takt
    memset(buf, WS_MK_BYTE(WS_RST, WS_RST), sizeof(buf));

    while (current_pixel)
    {
	current_pixel --;
	// piksele ulozone w zygzak, trzeba odwrocic co drugi wiersz
	uint32_t matrix_pixel = current_pixel;
	if (matrix_pixel & 0x10)
	    matrix_pixel ^= 0x0f;

	uint32_t pixel_value = data[matrix_pixel] & 0x00ffffff;
	// zamien bajty R i G: ws2812b oczekuje ramki w formacie GRB
	pixel_value = ((pixel_value << 8) & 0x00ff0000) |
                      ((pixel_value >> 8) & 0x0000ff00) |
                      (pixel_value & 0x000000ff);

	uint8_t bit_number = 24;

	while (bit_number > 1)
	{
	    uint8_t BitH = (pixel_value >> (bit_number - 1)) & 1;
	    uint8_t BitL = (pixel_value >> (bit_number - 2)) & 1;
	    buf[bytes_in_buf++] = WS_MK_BYTE(bit_coding[BitH], bit_coding[BitL]);
	    bit_number -= 2;
	}

        if (bytes_in_buf + pixel_bytes > sizeof(buf))
	{
	    int result = spi_write(fd, buf, bytes_in_buf);
	    if (result != bytes_in_buf)
		return err_spi_datacount;
	    bytes_in_buf = 0;
	}
    }
    if (bytes_in_buf)
    {
	int result = spi_write(fd, buf, bytes_in_buf);
	if (result != bytes_in_buf)
	    return err_spi_datacount;
    }
    return ws2812b_reset(fd);   // Puler comment: tu chyba powinien być else ???
    return err_ok;
}


#define swap(x, y) { int tmp = x; x = y; y = tmp; } while(0)

inline void fillrect(int x1, int y1, int x2, int y2, uint32_t RGB, uint32_t * Array)
{
    if (x1 < 0)
	x1 = 0;
    if (y1 < 0)
	y1 = 0;
    if (x2 > 15)
	x2 = 15;
    if (y2 > 15)
	y2 = 15;
    if (x1 > x2)
	swap(x1, x2);
    if (y1 > y2)
	swap(y1, y2);
    int x, y;

    for (x = x1; x <= x2; x++)
    {
        for (y = y1; y <= y2; y++)
        {
            Array[x + y * 16] = RGB;
        }
    }

    //Array[ 6 + 6 * 16 ] = 0x00FF0000;
}

//void ZST(int x, int y, uint32_t RGB, uint32_t * Array)
//{
//    Array[x + y * 16] = RGB;
//}

typedef union
{
    uint8_t b[4];
    uint32_t dw;
} TPixel;

//========================================================================
//#include "litery.h"



extern bool bMain_dziala;

//extern inline void Awaryjne_zatrzymanie( const int id )
//{
//    string str;
//
//    str  = "\033[31m";
//    str += "Nacisnieto Ctrl+C";
//    str += "\033[0m";
//
//    cout << str << endl;
//
//    bMain_dziala = false;
//}
//========================================================================


/*memset(xRGB, 0, PIXEL_COUNT*4);
        j += k;
        if ((j >= 7) || (j == 0))
            k = -k;

        color.b[0] += 1;
        color.b[1] += 3;
        color.b[2] += 5;
        fillrect(7-j, 7-j, 8+j, 8+j, color.dw, xRGB);*/
#endif // WS2812B_DISP_CPP
