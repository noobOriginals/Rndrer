// Std includes
#include <iostream>

// Local includes
#include <util/types.h>
#include <image.h>
#include <time.h>

int main() {
    int64 startTime = clock();

    const int32 width = 800;
    const int32 height = 600;

    Image* image = imgCreateImage(width, height);
    for (int32 x = 0; x < width; x++) {
        for (int32 y = 0; y < height; y++) {
            imgSetImagePixel(image, x, y, imgCreatePixel((uint8)((y * width + x) * 255 / (image->size - 1)), (uint8)(y * 255 / (height - 1)), (uint8)(x * 255 / (width - 1))));
        }
    }
    imgSaveImage(image, "../../output.bmp");
    imgDestroyImage(image);

    int64 endTime = clock();
    std::cout << endTime - startTime << " milliseconds\n";
    return 0;
}
