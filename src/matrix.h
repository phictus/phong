#pragma once

typedef struct { float x, y, z; } Vec3;
typedef struct { float data[16]; } Mat4;

Mat4 phIdentity();
Mat4 phOrthographic(float left, float right, float bottom, float top, float near, float far);
void phTranslate(Mat4* matrix, const Vec3* vector);
void phScale(Mat4* matrix, const Vec3* vector);
