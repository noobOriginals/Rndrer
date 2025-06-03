#ifndef IMAGE_HPP
#define IMAGE_HPP

// Std includes
#include <cstdlib>
#include <cstdio>

// Local includes
#include <util/types.h>

// Structs
struct pixelRGB {
    uint8 r, g, b;
    pixelRGB() {
        r = g = b = 0;
    }
    pixelRGB(uint8 x) {
        r = g = b = x;
    }
    pixelRGB(uint8 x, uint8 y, uint8 z) {
        r = x;
        g = y;
        b = z;
    }
    pixelRGB operator=(const pixelRGB& p) {
        r = p.r;
        g = p.g;
        b = p.b;
        return pixelRGB(r, g, b);
    }
};
struct Image {
    pixelRGB* pixels;
    int32 width, height, size;
    Image(int32 w, int32 h) {
        width = w;
        height = h;
        size = w * h;
        pixels = (pixelRGB*)calloc(size, sizeof(pixelRGB));
    }
    ~Image() {
        free(pixels);
    }
    void set(int32 x, int32 y, pixelRGB px) {
        pixels[y * width + x].r = px.r;
        pixels[y * width + x].g = px.g;
        pixels[y * width + x].b = px.b;
    }
    void setPixels(int32 size, pixelRGB* pxs) {
        for (int32 i = 0; i < size; i++) {
            pixels[i].r = pxs[i].r;
            pixels[i].g = pxs[i].g;
            pixels[i].b = pxs[i].b;
        }
    }
    void save(const char* filename) {
        int64* content = (int64*)calloc(16, sizeof(int64));
        content[0] = 0x4D42; // "BM" file header
        content[1] = 14 + 40 + size * 3; // File size in bytes (14 file header size + 40 DIB header size + nr. pixels * 3 bytes per pixel)
        content[2] = 0; // Ignored
        content[3] = 0; // Ignored
        content[4] = 14 + 40; // Pixel data offset in bytes (14 file header size + 40 DIB header size)
        content[5] = 40; // DIB header
        content[6] = width; // Image width in pixels
        content[7] = height; // Image height in pixels
        content[8] = 1; // Color planes, must be 1
        content[9] = 8 * 3; // Bits per pixel
        content[10] = 0; // Compression method, 0 for BI_RGB compression (no compression)
        content[11] = size * 3; // Size of the raw bitmap data
        content[12] = 0; // Ignored
        content[13] = 0; // Ignored
        content[14] = 0; // Ignored
        content[15] = 0; // Ignored
        uint8 padding = 0;
        FILE* file = fopen(filename, "wb");
        fwrite(&content[0], sizeof(uint16), 1, file);
        fwrite(&content[1], sizeof(uint32), 1, file);
        fwrite(&content[2], sizeof(uint16), 2, file); // Ignored
        fwrite(&content[4], sizeof(uint32), 1, file);
        fwrite(&content[5], sizeof(uint32), 1, file);
        fwrite(&content[6], sizeof(int32), 1, file);
        fwrite(&content[7], sizeof(int32), 1, file);
        fwrite(&content[8], sizeof(uint16), 1, file);
        fwrite(&content[9], sizeof(uint16), 1, file);
        fwrite(&content[10], sizeof(uint32), 1, file);
        fwrite(&content[11], sizeof(uint32), 1, file);
        fwrite(&content[12], sizeof(int32), 4, file); // Ignored
        for (int32 i = 0; i < size; i++) {
            fwrite(&pixels[i].b, sizeof(uint8), 1, file);
            fwrite(&pixels[i].g, sizeof(uint8), 1, file);
            fwrite(&pixels[i].r, sizeof(uint8), 1, file);
        }
        fclose(file);
    }
};

#endif