#include <stdio.h>
#include "decoder.h"

/* get a single bit */
static int decoderGetBit( uint8_t * buffer, long bitnumber, long bufsize )
{
	long nbyte = bitnumber >> 3;
	int nbit = bitnumber & 7;    
	int mask = 0x80 >> nbit;
	if( nbyte < 0 || nbyte > bufsize ) return( 0 );

	return ((buffer[nbyte] & mask) == mask);
}

/*	set a single bit */
static void decoderSetBit( uint8_t * buffer, long bitnumber, int value, long bufsize )
{
    long nbyte = bitnumber >> 3;
    int nbit = bitnumber & 7;
    int mask = 0x80 >> nbit;
    if( nbyte < 0 || nbyte > bufsize ) return;
    buffer[nbyte] &= ~mask;
    if (value)
        buffer[nbyte] |= mask;
}

int getPix(uint8_t *rom,int len,codec_t *c,int sx,int sy,int tile)
{
int p;
	if (tile>c->total) return 0;
	int startOffsetBits =  (c->charincrement * tile );
	int	tx = sx%c->width;
	int	ty = sy%c->height;
	int xoffs = c->xoffsets[tx];
	int yoffs = c->yoffsets[ty];
	int bits = 0;
	for (p=0;p<c->planes;p++)
	{		
		int poffs = c->planeoffsets[p]; 
		int ret = decoderGetBit( rom,	startOffsetBits + poffs + xoffs + yoffs, len );
		bits|=ret<<(p);
	}
	return bits;
}
/*
	set a pixel in a tile. 
*/
void setPix(uint8_t *rom,int len,codec_t *c,int sx,int sy,int color,int tile)
{
int p;	
	if (tile>c->total) return;
	int startOffsetBits = (c->charincrement * tile );
	int	tx = sx%c->width;
	int	ty = sy%c->height;
	int xoffs = c->xoffsets[tx];
	int yoffs = c->yoffsets[ty];
	for (p=0;p<c->planes;p++)
	{
		int pmask = 1<<(p);
		int bit = 0;
		int poffs = c->planeoffsets[p];    /* the offset for the plane */
		if ((color&pmask)==0)
			bit=0;
		else 
			bit=1;
		decoderSetBit(rom,	startOffsetBits + poffs + xoffs + yoffs, bit, len );
	}
}
