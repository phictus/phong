#include "matrix.h"

Mat4 phIdentity()
{
    Mat4 matrix;

    matrix.data[1 + 0 * 4] = 0.0f;
    matrix.data[2 + 0 * 4] = 0.0f;
    matrix.data[3 + 0 * 4] = 0.0f;
    matrix.data[0 + 1 * 4] = 0.0f;
    matrix.data[2 + 1 * 4] = 0.0f;
    matrix.data[3 + 1 * 4] = 0.0f;
    matrix.data[0 + 2 * 4] = 0.0f;
    matrix.data[1 + 2 * 4] = 0.0f;
    matrix.data[3 + 2 * 4] = 0.0f;
    matrix.data[0 + 3 * 4] = 0.0f;
    matrix.data[1 + 3 * 4] = 0.0f;
    matrix.data[2 + 3 * 4] = 0.0f;

    matrix.data[0 + 0 * 4] = 1.0f;
    matrix.data[1 + 1 * 4] = 1.0f;
    matrix.data[2 + 2 * 4] = 1.0f;
    matrix.data[3 + 3 * 4] = 1.0f;

    return matrix;
}

Mat4 phOrthographic(float left, float right, float bottom, float top, float near, float far)
{
    Mat4 matrix = phIdentity();

    matrix.data[0 + 0 * 4] = 2.0f / (right - left);
    matrix.data[1 + 1 * 4] = 2.0f / (top - bottom);
    matrix.data[2 + 2 * 4] = 2.0f / (near - far);

    matrix.data[0 + 3 * 4] = (left + right) / (left - right);
    matrix.data[1 + 3 * 4] = (bottom + top) / (bottom - top);
    matrix.data[2 + 3 * 4] = (far + near) / (far - near);

    return matrix;
}

void phTranslate(Mat4* matrix, const Vec3* vector)
{
    matrix->data[0 + 3 * 4] = vector->x;
    matrix->data[1 + 3 * 4] = vector->y;
    matrix->data[2 + 3 * 4] = vector->z;
}

void phScale(Mat4* matrix, const Vec3* vector)
{
    matrix->data[0 + 0 * 4] = vector->x;
    matrix->data[1 + 1 * 4] = vector->y;
    matrix->data[2 + 2 * 4] = vector->z;
}
