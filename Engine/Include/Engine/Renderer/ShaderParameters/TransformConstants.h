#pragma once

#include <Core/Math/TMatrix4x4.h>

namespace TDME
{
    struct TransformConstants
    {
        Matrix World      = Matrix::Identity();
        Matrix View       = Matrix::Identity();
        Matrix Projection = Matrix::Identity();
    };
} // namespace TDME