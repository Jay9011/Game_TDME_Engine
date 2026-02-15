#include "pch.h"
#include "Core/Image/BMPLoader.h"

#include "Core/CoreTypes.h"
#include <cstring>
#include <optional>

namespace TDME
{
    std::optional<ImageData> BMPLoader::Load(const std::vector<uint8>& data)
    {
        // 1. 헤더 파싱
        // 최소 크기 검증 : 파일 헤더 (14) + 정보 헤더 (40)
        constexpr size_t MIN_HEADER_SIZE = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
        if (data.size() < MIN_HEADER_SIZE)
        {
            return std::nullopt;
        }

        // 바이트 배열에서 헤더를 직접 읽음 (memcpy로 안전하게 복사)
        BMPFileHeader fileHeader;
        BMPInfoHeader infoHeader;
        std::memcpy(&fileHeader, data.data(), sizeof(BMPFileHeader));
        std::memcpy(&infoHeader, data.data() + sizeof(BMPFileHeader), sizeof(BMPInfoHeader));

        // 2. 유효성 검증
        // 'BM' 시그니처 확인 (리틀 엔디안에서 0x4D42)
        if (fileHeader.Signature != 0x4D42)
        {
            return std::nullopt;
        }

        // 24비트 또는 32비트만 지원
        if (infoHeader.BitCount != 24 && infoHeader.BitCount != 32)
        {
            return std::nullopt;
        }

        // 비압축(BI_RGB)만 지원
        if (infoHeader.Compression != 0)
        {
            return std::nullopt;
        }

        // 3. 픽셀 변환
        const uint32 width  = static_cast<uint32>(infoHeader.Width);
        const uint32 height = static_cast<uint32>(infoHeader.Height < 0 ? -infoHeader.Height : infoHeader.Height);

        const bool   isBottomUp    = infoHeader.Height > 0;
        const uint32 bytesPerPixel = infoHeader.BitCount / 8; // 3 또는 4

        // BMP 행 패딩: 각 행은 4바이트 배수로 정렬
        const uint32 rowSize = (width * bytesPerPixel + 3) & ~3u; // 픽셀별 바이트 수에 3을 더한 후 비트 연산을 통해 4의 배수로 맞춤 (..1100)

        // 픽셀 데이터 시작 위치 검증
        if (data.size() < fileHeader.DataOffset + rowSize * height)
        {
            return std::nullopt;
        }

        // RGBA8 출력 버퍼
        ImageData result;
        result.Width  = width;
        result.Height = height;
        result.Format = EImageFormat::RGBA8;
        result.Pixels.resize(width * height * 4);

        const uint8* srcData = data.data() + fileHeader.DataOffset;

        for (uint32 y = 0; y < height; y++)
        {
            // bottom-up 인 경우 행 순서 뒤집기
            const uint32 srcY   = isBottomUp ? (height - 1 - y) : y;
            const uint8* srcRow = srcData + srcY * rowSize;
            uint8*       dstRow = result.Pixels.data() + y * width * 4;

            for (uint32 x = 0; x < width; x++)
            {
                const uint8* srcPixel = srcRow + x * bytesPerPixel;
                uint8*       dstPixel = dstRow + x * 4;

                // BGR(A) => RGBA 변환
                dstPixel[0] = srcPixel[2];                              // R <- B 위치의 실제 R
                dstPixel[1] = srcPixel[1];                              // G <- G 그대로
                dstPixel[2] = srcPixel[0];                              // B <- R 위치의 실제 B
                dstPixel[3] = (bytesPerPixel == 4) ? srcPixel[3] : 255; // A <- 기본값 255 (불투명)
            }
        }

        return result;
    }
} // namespace TDME