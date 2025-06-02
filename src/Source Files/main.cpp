// Std includes
#include <iostream>

// Local includes
#include <util/types.h>
#include <image.h>

int main() {
    Image* image = imgCreateImage(800, 600);
    for (int32 x = 0; x < image->width; x++) {
        for (int32 y = 0; y < image->height; y++) {
            imgSetImagePixel(image, x, y, imgCreatePixel(x, y, 0, 0));
        }
    }
    imgSaveImage(image, "img.bmp");
    imgDestroyImage(image);
    return 0;
}
