#pragma once

#include "Core/CoreTypes.h"
#include "EImageFormat.h"

#include <vector>

namespace TDME {
/**
 * @brief 플랫폼 독립적인 이미지 픽셀 데이터
 * @detail 모든 이미지 로더(PNG, BMP 등)의 출력 타입. 원본 포맷과 관계없이 RGBA8
 * 포맷으로 변환하여 저장.
 * @note
 *   - 메모리 레이아웃: [R G B A][R G B A] ... (각 픽셀마다 4바이트, RGBA 순서)
 *   - 저장 순서: 좌상단부터 행 단위 (top-to-bottom, left-to-right) (대부분의
 * 그래픽 API가 top-to-bottom)
 */
struct ImageData {
  uint32 Width = 0;                          // 이미지의 너비 (픽셀 단위)
  uint32 Height = 0;                         // 이미지의 높이 (픽셀 단위)
  EImageFormat Format = EImageFormat::RGBA8; // 픽셀 포맷
  std::vector<uint8> Pixels;                 // 픽셀 데이터

  /** @brief 유효한 이미지 데이터인지 확인 */
  [[nodiscard]] bool IsValid() const {
    return Width > 0 && Height > 0 && !Pixels.empty();
  }

  /** @brief 픽셀 데이터의 전체 크기 (바이트) */
  [[nodiscard]] uint32 GetByteSize() const {
    return Width * Height * GetBytesPerPixel();
  }

  /** @brief 한 행의 바이트 크기 (pitch/stride) */
  [[nodiscard]] uint32 GetRowPitch() const {
    return Width * GetBytesPerPixel();
  }

  /** @brief 픽셀당 바이트 수 */
  [[nodiscard]] static constexpr uint32 GetBytesPerPixel() {
    return 4; // 우선 RGBA8 포맷은 4바이트
  }
};
} // namespace TDME