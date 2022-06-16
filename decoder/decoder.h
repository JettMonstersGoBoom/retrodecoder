#include <stdint.h>
//	max 4 planes 
//	max 16 x 16 pixels
typedef struct 
{
	const char *name;
	int width;
	int height;
	int total;
	int planes;
	int planeoffsets[4];
	int xoffsets[16];
	int yoffsets[16];
	int charincrement;
	uint32_t colors[16];
} codec_t;

int getPix(uint8_t *rom,int len,codec_t *c,int sx,int sy,int tile);
void setPix(uint8_t *rom,int len,codec_t *c,int sx,int sy,int color,int tile);

