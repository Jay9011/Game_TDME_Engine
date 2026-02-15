#pragma once

#include "Core/CoreTypes.h"

#include "ImageData.h"

#include <optional>
#include <vector>

namespace TDME
{
    /**
     * @brief BMP 이미지 파일 파서
     * @details 24비트(BFR)과 32비트(BGRA) 비압축 BMP를 지원.
     *          파싱 결과는 RGBA8 포맷의 ImageData로 통일.
     * @note BMP의 bottom-up 행 순서를 top-down으로 변환하여 저장.
     * @see TDME::ImageData
     */
    class BMPLoader
    {
    public:
        /**
         * @brief 바이트 배열에서 BMP 이미지를 파싱
         * @param data FileUtility::ReadFileToVector()로 읽어온 바이트 배열
         * @return std::optional<ImageData> 성공시 RGBA8 포맷의 ImageData, 실패시 std::nullopt
         */
        [[nodiscard]] static std::optional<ImageData> Load(const std::vector<uint8>& data);

    private:
#pragma pack(push, 1) // 패딩 없이 정확히 메모리에 맞춤
        /**
         * @brief BMP 파일 헤더 (14 bytes)
         * @details 파일의 시작 부분에 위치하며, 파일의 기본 정보를 담고 있음.
         */
        struct BMPFileHeader
        {
            uint16 Signature;  // 'BM' (0x4D42)
            uint32 FileSize;   // 전체 파일 크기 (바이트)
            uint16 Reserved1;  // 예약 (0)
            uint16 Reserved2;  // 예약 (0)
            uint32 DataOffset; // 데이터 오프셋 (픽셀 데이터 시작 위치)
        };

        /**
         * @brief BMP 정보 헤더 (40 bytes, BITMAPINFOHEADER)
         * @details 이미지 크기, 비트 깊이, 압축 방식 등을 포함하는 비트맵의 세부 정보를 담고 있음.
         */
        struct BMPInfoHeader
        {
            uint32 HeaderSize;      // 헤더 크기 (40)
            int32  Width;           // 이미지 너비 (픽셀)
            int32  Height;          // 이미지 높이 (픽셀) (양수 = bottom-up, 음수 = top-down)
            uint16 Planes;          // 색상 평면 수 (항상 1)
            uint16 BitCount;        // 픽셀당 비트 수 (24 또는 32)
            uint32 Compression;     // 압축 방식 (0 = BI_RGB, 비압축)
            uint32 ImageSize;       // 픽셀 데이터 크기 (바이트)
            int32  XPixelsPerMeter; // 수평 해상도 (픽셀/미터)
            int32  YPixelsPerMeter; // 수직 해상도 (픽셀/미터)
            uint32 ColorsUsed;      // 사용된 색상 수
            uint32 ColorsImportant; // 중요한 색상 수
        };
#pragma pack(pop) // 패딩 복원
    };
} // namespace TDME