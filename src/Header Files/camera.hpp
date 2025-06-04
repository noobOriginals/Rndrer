#ifndef CAMERA_HPP
#define CAMERA_HPP

// Local includes
#include <util/types.h>
#include <util/math.hpp>
#include <util/image.hpp>
#include <geometry.hpp>

struct Camera {
    float32 aspectRatio;
    float32 focalLength;
    image::Image image;
    math::Vec3 pos;
    float32 viewportWidth;
    float32 viewportHeight;
    math::Vec3 pixelDeltaX;
    math::Vec3 pixelDeltaY;
    math::Vec3 pixelOrigin;
    Camera(math::Vec3 pos, float32 aspectRatio, float32 focalLength, int32 imageWidth, float32 viewportWidth) {
        this->pos = pos;
        this->aspectRatio = aspectRatio;
        this->focalLength = focalLength;
        this->image = image::Image(imageWidth, (int32)(imageWidth / aspectRatio));
        this->viewportWidth = viewportWidth;
        this->viewportHeight = viewportWidth * (float32) image.height / image.width;
        math::Vec3 viewportX = math::Vec3(viewportWidth, 0, 0);
        math::Vec3 viewportY = math::Vec3(0, viewportHeight, 0);
        this-> pixelDeltaX = viewportX / image.width;
        this->pixelDeltaY = viewportY / image.height;
        math::Vec3 viewPortOrigin = pos - math::Vec3(0, 0, focalLength) - viewportX / 2.0f - viewportY / 2.0f;
        this->pixelOrigin = viewPortOrigin + 0.5f * (pixelDeltaX + pixelDeltaY);
    }
    Camera& operator=(const Camera& cam) {
        pos = cam.pos;
        aspectRatio = cam.aspectRatio;
        focalLength = cam.focalLength;
        image = cam.image;
        viewportWidth = cam.viewportWidth;
        viewportHeight = cam.viewportHeight;
        pixelDeltaX = cam.pixelDeltaX;
        pixelDeltaY = cam.pixelDeltaY;
        pixelOrigin = cam.pixelOrigin;
        return *this;
    }
    math::Vec3 getPixelPos(int32 x, int32 y) {
        return pixelOrigin + y * pixelDeltaY + x * pixelDeltaX;
    }
    void render() {
        for (int32 y = 0; y < image.height; y++) {
            for (int32 x = 0; x < image.width; x++) {
                math::Vec3 pixelPos = pixelOrigin + y * pixelDeltaY + x * pixelDeltaX;
                geo::Ray ray(pos, pixelPos - pos);
                image.set(x, y, image::Pixel(
                    (uint8)((ray.dir.x + 1.0f) * 127.5f), // Map x from [-1, 1] to [0, 255]
                    (uint8)((ray.dir.y + 1.0f) * 127.5f), // Map y from [-1, 1] to [0, 255]
                    (uint8)((ray.dir.z + 1.0f) * 127.5f)  // Map z from [-1, 1] to [0, 255]
                ));
            }
        }
    }
    void saveRender(const char* filename) {
        image.save(filename);
    }
};

#endif