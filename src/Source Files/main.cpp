// Std includes
#include <iostream>

// Local includes
#include <util/types.h>
#include <camera.hpp>

int32 main() {
    Camera camera(
        math::Vec3(0, 0, 0), // Position of the camera
        4.0f / 3.0f,       // Aspect ratio
        2.0f,               // Focal length
        1200,                // Image width
        10.0f                // Viewport width
    );
    camera.render();
    camera.saveRender("../../render.bmp");
    return 0;
}
