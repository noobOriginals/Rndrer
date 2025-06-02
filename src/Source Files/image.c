#include <image.h>

// Std includes
#include <stdlib.h>
#include <stdio.h>

// Methods
Pixel imgCreatePixel(uint8 r, uint8 g, uint8 b, uint8 a) {
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
    img->pixels[y * img->width + x] = px;
}
void imgSetImageData(Image* img, int32 size, Pixel* arr) {
    for (int32 i = 0; i < size; i++) {
        img->pixels[i] = arr[i];
    }
}

// Output methods
void imgSaveImage(Image* img, const char* filename) {
    int64* content = (int64*)calloc(16, sizeof(int64));
    content[0] = 0x4D42;
    content[1] = 14 + 40 + img->size * 4;
    content[2] = 0;
    content[3] = 0;
    content[4] = 14 + 40;
    content[5] = 40;
    content[6] = img->width;
    content[7] = img->height;
    content[8] = 1;
    content[9] = 32;
    content[10] = 0;
    content[11] = img->size * 4;
    content[12] = 0;
    content[13] = 0;
    content[14] = 0;
    content[15] = 0;
    uint8 padding = 0;
    FILE* file = fopen(filename, "wb");
    fwrite(&content[0], sizeof(int16), 1, file);
    fwrite(&content[1], sizeof(uint32), 1, file);
    fwrite(&content[2], sizeof(uint16), 1, file);
    fwrite(&content[3], sizeof(uint16), 1, file);
    fwrite(&content[4], sizeof(uint32), 1, file);
    fwrite(&content[5], sizeof(uint32), 1, file);
    fwrite(&content[6], sizeof(int32), 1, file);
    fwrite(&content[7], sizeof(int32), 1, file);
    fwrite(&content[8], sizeof(uint16), 1, file);
    fwrite(&content[9], sizeof(uint16), 1, file);
    fwrite(&content[10], sizeof(uint32), 1, file);
    fwrite(&content[11], sizeof(uint32), 1, file);
    fwrite(&content[12], sizeof(int32), 1, file); // Ignoring
    fwrite(&content[13], sizeof(int32), 1, file); // Ignoring
    fwrite(&content[14], sizeof(int32), 1, file); // Ignoring
    fwrite(&content[15], sizeof(int32), 1, file); // Ignoring
    for (int32 i = 0; i < img->size; i++) {
        fwrite(&img->pixels[i].b, sizeof(uint8), 1, file);
        fwrite(&img->pixels[i].g, sizeof(uint8), 1, file);
        fwrite(&img->pixels[i].r, sizeof(uint8), 1, file);
        fwrite(&padding, sizeof(uint8), 1, file);
    }
    fclose(file);
}