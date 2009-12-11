/*
 *  PNGTexture.cpp
 *  rerace
 *
 *  Created by Andrew Wagner on 11/21/09.
 *  Code Found at: http://macdevcenter.com/pub/a/mac/2005/10/14/texture-maps.html?page=1
 *
 */

#include "PNGTexture.h"
#include <UnixImageIO/UnixImageIO.h>
#include <fstream>
#include <GLUT/GLUT.h>

using namespace std;

int setupGLTexture(const char *file_name, int size, int texName) 
{
	if (file_name == NULL)
		return 0;
	
	unsigned char* image = read_png_file(file_name, size);
	
	if (image == NULL)
		return 0;
	
	/* create a new texture object
	 * and bind it to texname (unsigned integer < 0)
	 */
	glBindTexture(GL_TEXTURE_2D, texName);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size, size, 0, 
				 GL_RGB, GL_UNSIGNED_BYTE, image);
	return 1;
}

unsigned char* read_png_file(const char* file_name, int size)
{
	png_uint_32 width = 64;
	png_uint_32 height = 64;
	
	/* Open the PNG file. */
	FILE* infile;
	infile = fopen(file_name, "rb");
	if (!infile) {
		return NULL;
	}
	char sig[8];
	/* Check for the 8-byte signature */
	fread(sig, 1, 8, infile);
	if (!png_check_sig((unsigned char *) sig, 8)) {
		fclose(infile);
		return NULL;
	}
	
	png_structp png_ptr; 
	png_infop info_ptr; 
	png_infop end_ptr;
	
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		fclose(infile);
		return NULL; /* out of memory */
	}
	
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_read_struct(&png_ptr, (png_infopp) NULL, (png_infopp) NULL);
		fclose(infile);
		return NULL; /* out of memory */
	}
	
	end_ptr = png_create_info_struct(png_ptr);
	if (!end_ptr) {
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
		fclose(infile);
		return NULL; /* out of memory */
	}
	
	/*
	 * block to handle libpng errors, 
	 * then check whether the PNG file had a bKGD chunk
	 */
	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_ptr);
		fclose(infile);
		return NULL;
	}
	
	/*
	 * takes our file stream pointer (infile) and 
	 * stores it in the png_ptr struct for later use.
	 */
	png_ptr->io_ptr = (png_voidp)infile;
	
	/*
	 * lets libpng know that we already checked the 8 
	 * signature bytes, so it should not expect to find 
	 * them at the current file pointer location
	 */
	png_set_sig_bytes(png_ptr, 8);
	
	png_read_info(png_ptr, info_ptr);
	int bit_depth = 16;
	int color_type = PNG_COLOR_TYPE_RGB_ALPHA;
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, 
				 &color_type, NULL, NULL, NULL);
	//*pwidth = width;
	//*pheight = height;
	
	/* snipped out the color type code, see source pngLoad.c */
	/* Update the png info struct.*/
	png_read_update_info(png_ptr, info_ptr);
	
	/* Rowsize in bytes. */
	int rowbytes = png_get_rowbytes(png_ptr, info_ptr);
	
	/* Allocate the image_data buffer. */
	unsigned char* image_data;
	if ((image_data = (unsigned char *) malloc(rowbytes * height))==NULL) {
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		return NULL;
	}
	png_bytepp row_pointers;
	if ((row_pointers = (png_bytepp)malloc(height*sizeof(png_bytep))) == NULL) {
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		free(image_data);
		image_data = NULL;
		return NULL;
	}
	
	/* set the individual row_pointers to point at the correct offsets */
    for (int i = 0;  i < height;  ++i)
        row_pointers[height - 1 - i] = image_data + i*rowbytes;
	
	png_read_image(png_ptr, row_pointers);
	
	return image_data;
}