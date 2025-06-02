#ifndef RAY_H
#define RAY_H

#ifdef __cplusplus
extern "C" {
#endif

// Local includes
#include <util/vec.h>

typedef struct Ray2D {
    Vec2 orig, dir;
} Ray2D;
typedef struct Ray3D {
    Vec3 orig, dir;
} Ray3D;

Ray2D rayCreateRay2D(Vec2 origin, Vec2 direction);
Ray3D rayCreateRay3D(Vec3 origin, Vec3 direction);

#ifdef __cplusplus
}
#endif

#endif