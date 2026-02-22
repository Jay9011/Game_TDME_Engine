#pragma once

#include "Core/Math/TVector3.h"
#include "Core/Types/Color32.h"

//////////////////////////////////////////////////////////////
// VERTEX 타입들
//////////////////////////////////////////////////////////////

namespace TDME
{
    /**
     * @brief 정점 타입 (Position Only)
     * @note 단색 도형, 디버깅용 렌더링 등에 사용
     */
    struct VertexP
    {
        Vector3 Position;

        VertexP() = default;

        constexpr VertexP(float x, float y, float z = 0.0f)
            : Position(x, y, z) {}

        constexpr VertexP(const Vector2& position, float z = 0.0f)
            : Position(position.X, position.Y, z) {}

        constexpr VertexP(const Vector3& position)
            : Position(position) {}
    };

    /**
     * @brief 정점 타입 (Position + Color)
     * @note 정점별 색상이 다른 도형에 사용
     */
    struct VertexPC
    {
        Vector3 Position;
        Color32 Color;

        VertexPC() = default;

        constexpr VertexPC(float x, float y, const Color32& color, float z = 0.0f)
            : Position(x, y, z), Color(color) {}

        constexpr VertexPC(const Vector2& position, const Color32& color, float z = 0.0f)
            : Position(position.X, position.Y, z), Color(color) {}

        constexpr VertexPC(const Vector3& position, const Color32& color)
            : Position(position), Color(color) {}
    };

    /**
     * @brief 정점 타입 (Position + Texture Coord)
     * @note 텍스처 매핑이 필요한 도형에 사용 (색상 틴트 없음)
     */
    struct VertexPT
    {
        Vector3 Position;
        Vector2 TexCoord;

        VertexPT() = default;

        constexpr VertexPT(float x, float y, float u, float v, float z = 0.0f)
            : Position(x, y, z), TexCoord(u, v) {}

        constexpr VertexPT(float x, float y, const Vector2& uv, float z = 0.0f)
            : Position(x, y, z), TexCoord(uv) {}

        constexpr VertexPT(const Vector2& position, float u, float v, float z = 0.0f)
            : Position(position.X, position.Y, z), TexCoord(u, v) {}

        constexpr VertexPT(const Vector2& position, const Vector2& uv, float z = 0.0f)
            : Position(position.X, position.Y, z), TexCoord(uv) {}

        constexpr VertexPT(const Vector3& position, const Vector2& uv)
            : Position(position), TexCoord(uv) {}
    };

    /**
     * @brief 정점 타입 (Position + Color + Texture Coord)
     * @note 가장 일반적인 2D 용 정점 타입 (스프라이트에 색상 틴트를 적용할 수 있음)
     */
    struct VertexPCT
    {
        Vector3 Position;
        Color32 Color;
        Vector2 TexCoord;

        VertexPCT() = default;

        constexpr VertexPCT(float x, float y, const Color32& color, float u, float v, float z = 0.0f)
            : Position(x, y, z), Color(color), TexCoord(u, v) {}

        constexpr VertexPCT(float x, float y, const Color32& color, const Vector2& uv, float z = 0.0f)
            : Position(x, y, z), Color(color), TexCoord(uv) {}

        constexpr VertexPCT(const Vector2& position, const Color32& color, float u, float v, float z = 0.0f)
            : Position(position.X, position.Y, z), Color(color), TexCoord(u, v) {}

        constexpr VertexPCT(const Vector2& position, const Color32& color, const Vector2& uv, float z = 0.0f)
            : Position(position.X, position.Y, z), Color(color), TexCoord(uv) {}

        constexpr VertexPCT(const Vector3& position, const Color32& color, const Vector2& uv)
            : Position(position), Color(color), TexCoord(uv) {}
    };

    /**
     * @brief 정점 타입 (Position + Normal + Texture Coord)
     * @note 노멀 매핑이 필요한 도형에 사용 (광원 효과 등 법선 벡터가 필요한 곳에서)
     */
    struct VertexPNT
    {
        Vector3 Position;
        Vector3 Normal;
        Vector2 TexCoord;

        VertexPNT() = default;

        constexpr VertexPNT(float x, float y, float nx, float ny, float u, float v, float z = 0.0f)
            : Position(x, y, z), Normal(nx, ny, 0.0f), TexCoord(u, v) {}

        constexpr VertexPNT(const Vector3& position, const Vector3& normal, const Vector2& uv)
            : Position(position), Normal(normal), TexCoord(uv) {}
    };

} // namespace TDME