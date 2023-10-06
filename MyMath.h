#pragma once
#include "Matrix4x4.h"
#include <Vector3.h>

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate);

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);

Vector3 Normalise(const Vector3& v);

Vector3 Subtract(const Vector3& v1, const Vector3& v2);