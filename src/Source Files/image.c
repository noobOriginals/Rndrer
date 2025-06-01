#include <image.h>

#include <stdlib.h>

// Methods
Pixel imgCreatePixel(int8 r, int8 g, int8 b, int8 a) {
    Pixel p;
    p.r = r;
    p.g = g;
    p.b = b;
    p.a = a;
    return p;
}
Image* imgCreateImage(int32 width, int32 height) {
    Image* img = (Image*)calloc(1, sizeof(Image));
    img->pixels = (Pixel*)calloc(width * height, sizeof(Pixel));
    img->width = width;
    img->height = height;
    img->size = width * height;
    return img;
}
void imgDestroyImage(Image* img) {
    free(img->pixels);
    free(img);
}
void imgSetImagePixel(Image* img, int32 x, int32 y, Pixel px) {

}
void imgSetImageData(Image* img, int32 size, Pixel* arr) {

}

// Output methods
void imgSaveImage(Image* img, const char* filename) {

}