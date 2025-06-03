// Std includes
#include <iostream>

// Local includes
#include <util/types.h>
#include <util/vec.hpp>
#include <util/image.hpp>
#include <ray.hpp>
#include <raycaster.hpp>
#include <time.h>

using namespace vec;

int32 main() {
    // Set constants
    float32 focalLength = 2.0f;
    float32 aspectRatio = 4.0f / 3.0f;
    int32 imageWidth = 1200;
    int32 imageHeight = (int32)(imageWidth / aspectRatio);

    vec3 cameraPos = vec3(0, 0, 0);
    float32 viewportWidth = 10.0f;
    float32 viewportHeight = viewportWidth * (float32) imageHeight / imageWidth;
    vec3 viewportX = vec3(viewportWidth, 0, 0);
    vec3 viewportY = vec3(0, viewportHeight, 0);
    vec3 pixelDeltaX = viewportX / imageWidth;
    vec3 pixelDeltaY = viewportY / imageHeight;
    vec3 viewPortOrigin = cameraPos - vec3(0, 0, focalLength) - viewportX / 2.0f - viewportY / 2.0f;
    vec3 pixelOrigin = viewPortOrigin + 0.5f * (pixelDeltaX + pixelDeltaY);

    Image img(imageWidth, imageHeight);

    for (int32 y = 0; y < imageHeight; y++) {
        for (int32 x = 0; x < imageWidth; x++) {
            vec3 pixelPos = pixelOrigin + y * pixelDeltaY + x * pixelDeltaX;
            ray3d ray(cameraPos, pixelPos - cameraPos);
            pixelRGB pixel = raycaster::raycast(ray);
            img.set(x, y, pixel);
        }
    }

    img.save("../../output.bmp");
    return 0;
}
