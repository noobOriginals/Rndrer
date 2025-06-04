#ifndef RENDER_HPP
#define RENDER_HPP

// Local includes
#include <util/types.h>
#include <util/math.hpp>
#include <util/image.hpp>
#include <geometry.hpp>

namespace render {

image::Pixel raycast(geo::Ray r) {
    geo::Sphere s(math::Vec3(0.0f, 0.0f, -1.0f), 0.5f);
    float32 t = s.hitRay(r);
    if (t > 0) {
        math::Vec3 unit = math::normalize(r.at(t) - s.c);
        math::Vec3 col = 0.5f * math::Vec3(unit.x + 1.0f, unit.y + 1.0f, unit.z + 1.0f);
        return geo::vecToPixel(col);
    }
    else {
        return image::Pixel(10, 10, 10); // Background color
    }
}

}

struct Render {
    float32 aspectRatio;
    float32 focalLength;
    image::Image image;
    math::Vec3 pos;
    float32 viewportWidth;
    float32 viewportHeight;
    math::Vec3 pixelDeltaX;
    math::Vec3 pixelDeltaY;
    math::Vec3 pixelOrigin;
    Render(math::Vec3 pos, float32 aspectRatio, float32 focalLength, int32 imageWidth, float32 viewportWidth) {
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
    Render& operator=(const Render& cam) {
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
    void run() {
        for (int32 y = 0; y < image.height; y++) {
            for (int32 x = 0; x < image.width; x++) {
                math::Vec3 pixelPos = pixelOrigin + y * pixelDeltaY + x * pixelDeltaX;
                geo::Ray ray(pos, pixelPos - pos);
                image.set(x, y, render::raycast(ray));
            }
        }
    }
    void save(const char* filename) {
        image.save(filename);
    }
};

#endif