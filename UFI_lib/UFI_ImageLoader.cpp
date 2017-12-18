
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <SDL2/SDL.h>
#include <png.h>
#include <jpeglib.h>
#include <sys/types.h>
#include <unistd.h>
#include "UFI_ImageLoader.h"

SDL_Surface* load_surface_jpeg(const char* file_name)
{
	unsigned int amask = 0xff000000;
	unsigned int bmask = 0x00ff0000;
	unsigned int gmask = 0x0000ff00;
	unsigned int rmask = 0x000000ff;
	SDL_Surface *res_surface;

	unsigned char a,r,g,b;
	int width, height;
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	FILE * infile;    	/* source file */
	JSAMPARRAY pJpegBuffer;   	/* Output row buffer */
	int row_stride;   	/* physical row width in output buffer */
	if ((infile = fopen(file_name, "rb")) == NULL) 
	{
		fprintf(stderr, "can't open %s\n", file_name);
		return NULL;
	}
	char tst[32];
	size_t rdsz = fread (tst, 1, 20, infile);
	if(rdsz < 20)
		;
	fseek (infile, 0, SEEK_SET);
	int isOk = 0;
	for(int x = 0; x < 16; ++ x)
	{
		if(tst[x] == 'J' && tst[x+1] == 'F' && tst[x+2] == 'I' && tst[x+3] == 'F')
		{
			isOk = 1;
			break;
		}
	}
	if(!isOk)
	{
		fprintf(stderr, "%s isn't normal jpeg!\n", file_name);
		return NULL;
	}
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, infile);
	(void) jpeg_read_header(&cinfo, TRUE);
	(void) jpeg_start_decompress(&cinfo);
	width = cinfo.output_width;
	height = cinfo.output_height;

	res_surface = SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);
	SDL_LockSurface(res_surface);
	uint8_t *pDummy = (uint8_t*)res_surface->pixels;

	if (!pDummy){
		fprintf(stderr, "Can't lock surface!\n");
		SDL_UnlockSurface(res_surface);
		SDL_FreeSurface(res_surface);
		return NULL;
	}
	row_stride = width * cinfo.output_components ;
	pJpegBuffer = (*cinfo.mem->alloc_sarray)
		((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

	while (cinfo.output_scanline < cinfo.output_height) 
	{
		(void) jpeg_read_scanlines(&cinfo, pJpegBuffer, 1);
		for (int x=0;x<width;x++) 
		{
			a = 0; // alpha value is not supported on jpg
			r = pJpegBuffer[0][cinfo.output_components*x];
			if (cinfo.output_components>2)
			{
				g = pJpegBuffer[0][cinfo.output_components*x+1];
				b = pJpegBuffer[0][cinfo.output_components*x+2];
			} else 
			{
				g = r;
				b = r;
			}
			*(pDummy++) = b;
			*(pDummy++) = g;
			*(pDummy++) = r;
			*(pDummy++) = a;
		}
	}
	fclose(infile);
	(void) jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	SDL_UnlockSurface(res_surface);

	return res_surface;
}

struct MemoryStruct {
	char *memory;
	size_t size;
	size_t pos;
};

void png_read_func(png_structp pngPtr, png_bytep data, png_size_t length)
{
	MemoryStruct* ms = (MemoryStruct*)png_get_io_ptr(pngPtr);
	memcpy(data, ms->memory + ms->pos, length);
	ms->pos += length;
}

SDL_Surface *load_surface_png(const char *file_name)
{
	int fl = open(file_name, O_RDONLY);
	if(fl < 0) return NULL;
	int fsz =lseek(fl, 0L, SEEK_END);
	lseek(fl, 0L, SEEK_SET);
	if(fsz > 92345678)
	{
		printf("map file too large (>92Mb)\n");
		return NULL; //file too large
	}
	if(fsz < 100)
	{
		printf("map file too small (<100b)\n");
		return NULL; //file too large
	}
	//uint8_t *pngImg = NULL;
	//int pngW = 0, pngH = 0;

	struct MemoryStruct img_png;

	img_png.memory = (char *)malloc(fsz);
	img_png.size = fsz;
	img_png.pos = 0;
	read(fl, img_png.memory, fsz);

	close(fl);

	uint8_t pngSignature[8];
	memcpy(pngSignature, img_png.memory, 8);
	img_png.pos = 8;
	if(!png_check_sig(pngSignature, 8))
		return NULL;

	// get PNG file info struct (memory is allocated by libpng)
	png_structp png_ptr = NULL;
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if(png_ptr == NULL)
		return NULL;

	// get PNG image data info struct (memory is allocated by libpng)
	png_infop info_ptr = NULL;
	info_ptr = png_create_info_struct(png_ptr);

	if(info_ptr == NULL)
	{
		// libpng must free file info struct memory before we bail
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		return NULL;
	}

	png_set_read_fn(png_ptr, &img_png, png_read_func);
	png_set_sig_bytes(png_ptr, 8);

//=============
	png_read_info(png_ptr, info_ptr);
	png_uint_32 width = 0;
	png_uint_32 height = 0;
	int bitDepth = 0;
	int colorType = -1;
	png_uint_32 retval = png_get_IHDR(png_ptr, info_ptr, &width, &height, &bitDepth, &colorType, NULL, NULL, NULL);

	if(retval != 1)
		return NULL; // add error handling and cleanup
	//printf("png: w=%d, h=%d, bpp=%d, colorType %d (%d %d %d) \n", width, height, bitDepth, colorType, PNG_COLOR_TYPE_RGB, PNG_COLOR_TYPE_RGB_ALPHA, PNG_COLOR_TYPE_PALETTE);

	unsigned int amask = 0xff000000;
	unsigned int bmask = 0x00ff0000;
	unsigned int gmask = 0x0000ff00;
	unsigned int rmask = 0x000000ff;
	SDL_Surface *res_surface;

	res_surface = SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);
	SDL_LockSurface(res_surface);
	uint8_t *cpix = (uint8_t*)res_surface->pixels;

	if(colorType == PNG_COLOR_TYPE_RGB)
	{
		int w = width;
		int h = height;

		int bytesPerRow = png_get_rowbytes(png_ptr, info_ptr);
		uint8_t* rowData = (uint8_t*)malloc(bytesPerRow);
		for(int x = 0; x < h; ++x)
		{
			png_read_row(png_ptr, (png_bytep)rowData, NULL);
			for(int n = 0; n < w; ++n)
			{
				*cpix++ = 0;
				*cpix++ = rowData[n*3];
				*cpix++ = rowData[n*3+1];
				*cpix++ = rowData[n*3+2];
			}
		}
	}
	if(colorType == PNG_COLOR_TYPE_RGB_ALPHA)
	{
		int w = width;
		int h = height;

		int bytesPerRow = png_get_rowbytes(png_ptr, info_ptr);
		uint8_t* rowData = (uint8_t*)malloc(bytesPerRow);
		for(int x = 0; x < h; ++x)
		{
			png_read_row(png_ptr, (png_bytep)rowData, NULL);
			for(int n = 0; n < w; ++n)
			{
				*cpix++ = rowData[n*4+0];
				*cpix++ = rowData[n*4+1];
				*cpix++ = rowData[n*4+2];
				*cpix++ = rowData[n*4+3];
			}
		}
	}
	if(colorType == PNG_COLOR_TYPE_PALETTE)
	{
		png_color *plt;
		int psz = 0;
		png_get_PLTE(png_ptr, info_ptr, &plt, &psz);
		int w = width;
		int h = height;

		int bytesPerRow = png_get_rowbytes(png_ptr, info_ptr);
		uint8_t* rowData = (uint8_t*)malloc(bytesPerRow);
		for(int x = 0; x < h; ++x)
		{
			png_read_row(png_ptr, (png_bytep)rowData, NULL);
			for(int n = 0; n < w; ++n)
			{
				png_color cl = plt[rowData[n]];
				*cpix++ = cl.blue;
				*cpix++ = cl.green;
				*cpix++ = cl.red;
				*cpix++ = 0;
			}
		}
	}
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	free(img_png.memory);
	SDL_UnlockSurface(res_surface);
	return res_surface;
}