#pragma once

#include "Core/Math/TVector3.h"
#include "Core/Types/Color32.h"

//////////////////////////////////////////////////////////////
// VERTEX 2D 타입들 (Transform)
//////////////////////////////////////////////////////////////

namespace TDME
{
    /**
     * @brief 2D 정점 타입 (Position Only)
     * @note 단색 도형, 디버깅용 렌더링 등에 사용
     */
    struct Vertex2DP
    {
        Vector3 Position;

        Vertex2DP() = default;

        constexpr Vertex2DP(float x, float y, float z = 0.0f)
            : Position(x, y, z) {}

        constexpr Vertex2DP(const Vector2& position, float z = 0.0f)
            : Position(position.X, position.Y, z) {}

        constexpr Vertex2DP(const Vector3& position)
            : Position(position) {}
    };

    /**
     * @brief 2D 정점 타입 (Position + Color)
     * @note 정점별 색상이 다른 도형에 사용
     */
    struct Vertex2DPC
    {
        Vector3 Position;
        Color32 Color;

        Vertex2DPC() = default;

        constexpr Vertex2DPC(float x, float y, const Color32& color, float z = 0.0f)
            : Position(x, y, z), Color(color) {}

        constexpr Vertex2DPC(const Vector2& position, const Color32& color, float z = 0.0f)
            : Position(position.X, position.Y, z), Color(color) {}

        constexpr Vertex2DPC(const Vector3& position, const Color32& color)
            : Position(position), Color(color) {}
    };

    /**
     * @brief 2D 정점 타입 (Position + Texture Coord)
     * @note 텍스처 매핑이 필요한 도형에 사용 (색상 틴트 없음)
     */
    struct Vertex2DPT
    {
        Vector3 Position;
        Vector2 TexCoord;

        Vertex2DPT() = default;

        constexpr Vertex2DPT(float x, float y, float u, float v, float z = 0.0f)
            : Position(x, y, z), TexCoord(u, v) {}

        constexpr Vertex2DPT(float x, float y, const Vector2& uv, float z = 0.0f)
            : Position(x, y, z), TexCoord(uv) {}

        constexpr Vertex2DPT(const Vector2& position, float u, float v, float z = 0.0f)
            : Position(position.X, position.Y, z), TexCoord(u, v) {}

        constexpr Vertex2DPT(const Vector2& position, const Vector2& uv, float z = 0.0f)
            : Position(position.X, position.Y, z), TexCoord(uv) {}

        constexpr Vertex2DPT(const Vector3& position, const Vector2& uv)
            : Position(position), TexCoord(uv) {}
    };

    /**
     * @brief 2D 정점 타입 (Position + Color + Texture Coord)
     * @note 가장 일반적인 2D 용 정점 타입 (스프라이트에 색상 틴트를 적용할 수 있음)
     */
    struct Vertex2DPCPT
    {
        Vector3 Position;
        Color32 Color;
        Vector2 TexCoord;

        Vertex2DPCPT() = default;

        constexpr Vertex2DPCPT(float x, float y, const Color32& color, float u, float v, float z = 0.0f)
            : Position(x, y, z), Color(color), TexCoord(u, v) {}

        constexpr Vertex2DPCPT(float x, float y, const Color32& color, const Vector2& uv, float z = 0.0f)
            : Position(x, y, z), Color(color), TexCoord(uv) {}

        constexpr Vertex2DPCPT(const Vector2& position, const Color32& color, float u, float v, float z = 0.0f)
            : Position(position.X, position.Y, z), Color(color), TexCoord(u, v) {}

        constexpr Vertex2DPCPT(const Vector2& position, const Color32& color, const Vector2& uv, float z = 0.0f)
            : Position(position.X, position.Y, z), Color(color), TexCoord(uv) {}

        constexpr Vertex2DPCPT(const Vector3& position, const Color32& color, const Vector2& uv)
            : Position(position), Color(color), TexCoord(uv) {}
    };

    /**
     * @brief 2D 정점 타입 (Position + Normal + Texture Coord)
     * @note 노멀 매핑이 필요한 도형에 사용 (광원 효과 등 법선 벡터가 필요한 곳에서)
     */
    struct Vertex2DPNT
    {
        Vector3 Position;
        Vector3 Normal;
        Vector2 TexCoord;

        Vertex2DPNT() = default;

        constexpr Vertex2DPNT(float x, float y, float nx, float ny, float u, float v, float z = 0.0f)
            : Position(x, y, z), Normal(nx, ny, 0.0f), TexCoord(u, v) {}

        constexpr Vertex2DPNT(const Vector3& position, const Vector3& normal, const Vector2& uv)
            : Position(position), Normal(normal), TexCoord(uv) {}
    };

} // namespace TDME