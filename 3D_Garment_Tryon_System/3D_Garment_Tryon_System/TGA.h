

#include <gl/glut.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include <iostream>

typedef struct TGAHEADER
{
    GLbyte	identsize;						 // Size of ID field that follows header (0)
    GLbyte	colorMapType;					  // 0 = None, 1 = paletted
    GLbyte	imageType;						// 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8=rle
    //unsigned short	colorMapStart;          // First colour map entry
    unsigned short	colorMapLength;         // Number of colors
    unsigned char 	colorMapBits;			 // bits per palette entry
    unsigned short	xstart;                 // image x origin
    unsigned short	ystart;                 // image y origin
    unsigned short	width;                  // width in pixels
    unsigned short	height;                 // height in pixels
    GLbyte	bits;							// bits per pixel (8 16, 24, 32)
    GLbyte	descriptor;					 // image descriptor
} ;

class LoadTGA
{
public:
	LoadTGA(void);
	~LoadTGA(void);
	GLbyte *gltLoadTGA(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat);
};

GLbyte *gltLoadTGA(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat)
	{
    FILE *pFile;			// File pointer
    TGAHEADER tgaHeader;		// TGA file header

	/*std::cout<<sizeof(tgaHeader.identsize)<<"\n";
	std::cout<<sizeof(tgaHeader.colorMapType)<<"\n";
	std::cout<<sizeof(tgaHeader.imageType)<<"\n";
	//std::cout<<sizeof(tgaHeader.colorMapStart)<<"\n";
	std::cout<<sizeof(tgaHeader.colorMapLength)<<"\n";
	std::cout<<sizeof(tgaHeader.colorMapBits)<<"\n";
	std::cout<<sizeof(tgaHeader.xstart)<<"\n";
	std::cout<<sizeof(tgaHeader.ystart)<<"\n";
	std::cout<<sizeof(tgaHeader.width)<<"\n";
	std::cout<<sizeof(tgaHeader.height)<<"\n";
	std::cout<<sizeof(tgaHeader.bits)<<"\n";
	std::cout<<sizeof(tgaHeader.descriptor)<<"\n";
	std::cout<<sizeof(tgaHeader)<<"\n";
	*/

    unsigned long lImageSize;		// Size in bytes of image
    short sDepth;			// Pixel depth;
    GLbyte	*pBits = NULL;          // Pointer to bits
    
    // Default/Failed values
    *iWidth = 0;
    *iHeight = 0;
    *eFormat = GL_BGR_EXT;
    *iComponents = GL_RGB8;
    
    // Attempt to open the fil
    pFile = fopen(szFileName, "rb");
    if(pFile == NULL)
        return NULL;
	
    // Read in header (binary)
	
    fread(&tgaHeader, 18/* sizeof(TGAHEADER)*/, 1, pFile);
	
	/*std::cout<<"identsize: "<<(tgaHeader.identsize)<<"\n";
	std::cout<<"colorMapType: "<<(tgaHeader.colorMapType)<<"\n";
	std::cout<<"imageType: "<<(tgaHeader.imageType)<<"\n";
	//std::cout<<"colorMapStart: "<<(tgaHeader.colorMapStart)<<"\n";
	std::cout<<"colorMapLength: "<<(tgaHeader.colorMapLength)<<"\n";
	std::cout<<"colorMapBits: "<<(tgaHeader.colorMapBits)<<"\n";
	std::cout<<"xstart: "<<(tgaHeader.xstart)<<"\n";
	std::cout<<"ystart: "<<(tgaHeader.ystart)<<"\n";
	std::cout<<"width: "<<(tgaHeader.width)<<"\n";
	std::cout<<"height: "<<(tgaHeader.height)<<"\n";
	std::cout<<"bits: "<<(tgaHeader.bits)<<"\n";
	std::cout<<"descriptor: "<<(tgaHeader.descriptor)<<"\n";
	*/


    // Do byte swap for big vs little endian
#ifdef __APPLE__
    LITTLE_ENDIAN_WORD(&tgaHeader.colorMapStart);
    LITTLE_ENDIAN_WORD(&tgaHeader.colorMapLength);
    LITTLE_ENDIAN_WORD(&tgaHeader.xstart);
    LITTLE_ENDIAN_WORD(&tgaHeader.ystart);
    LITTLE_ENDIAN_WORD(&tgaHeader.width);
    LITTLE_ENDIAN_WORD(&tgaHeader.height);
#endif
	
	
    // Get width, height, and depth of texture
    *iWidth = tgaHeader.width;
    *iHeight = tgaHeader.height;
    sDepth = tgaHeader.bits / 8;
    
    // Put some validity checks here. Very simply, I only understand
    // or care about 8, 24, or 32 bit targa's.
    if(tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
        return NULL;
	
    // Calculate size of image buffer
    lImageSize = tgaHeader.width * tgaHeader.height * sDepth;
    
    // Allocate memory and check for success
    pBits = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
    if(pBits == NULL)
        return NULL;
    
    // Read in the bits
    // Check for read error. This should catch RLE or other 
    // weird formats that I don't want to recognize
    if(fread(pBits, lImageSize, 1, pFile) != 1)
		{
        free(pBits);
        return NULL;
		}
    
    // Set OpenGL format expected
    switch(sDepth)
		{
        case 3:     // Most likely case
            *eFormat = GL_BGR_EXT;
            *iComponents = GL_RGB8;
            break;
        case 4:
            *eFormat = GL_BGRA_EXT;
            *iComponents = GL_RGBA8;
            break;
        case 1:
            *eFormat = GL_LUMINANCE;
            *iComponents = GL_LUMINANCE8;
            break;
		};
	
    
    // Done with File
    fclose(pFile);
	
    // Return pointer to image data
    return pBits;
	}