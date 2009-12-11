/*
 *  PNGTexture.h
 *  rerace
 *
 *	File to read in png files and generate a texture from them
 *
 *  Created by Andrew Wagner and Keith Thompson on 11/21/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

unsigned char* read_png_file(const char* file_name, int size);
int setupGLTexture(const char *file_name, int size, int texName);
