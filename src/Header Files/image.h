#ifndef IMAGE_H
#define IMAGE_H

#ifdef __cplusplus
extern "C" {
#endif

// Local includes
#include <util/types.h>

// Structs
typedef struct Pixel {
    uint8 r, g, b, a;
} Pixel;
typedef struct Image {
    Pixel* pixels;
    int32 width;
    int32 height;
    int32 size;
} Image;

// Methods
Pixel imgCreatePixel(uint8 r, uint8 g, uint8 b, uint8 a);
Image* imgCreateImage(int32 width, int32 height);
void imgDestroyImage(Image* img);
void imgSetImagePixel(Image* img, int32 x, int32 y, Pixel px);
void imgSetImageData(Image* img, int32 size, Pixel* arr);

// Output methods
void imgSaveImage(Image* img, const char* filename);

#ifdef __cplusplus
}
#endif

#endif