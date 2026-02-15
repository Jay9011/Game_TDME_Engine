#pragma once

#include "Core/CoreTypes.h"

#include <filesystem>
#include <fstream>
#include <optional>
#include <vector>

namespace TDME
{
    /**
     * @brief 파일 관련 유틸리티 작업을 수행하기 위한 클래스.
     */
    class FileUtility
    {
    public:
        /**
         * @brief 지정한 경로의 바이너리 파일을 읽어 바이트 벡터로 반환.
         * @detail 이미지, 모델 등 바이너리 파일용
         * @param path 읽을 파일의 경로 (std::filesystem::path)
         * @return 파일을 성공적으로 읽으면 파일 내용 전체를 담은 std::vector<uint8>를 포함한 std::optional을 반환. (읽기 실패시 std::nullopt를 반환)
         */
        [[nodiscard]] static std::optional<std::vector<uint8>> ReadBinaryFile(const std::filesystem::path& path)
        {
            // 1. 바이너리 모드 + 끝에서 열기 (ate = at end)
            std::ifstream file(path, std::ios::binary | std::ios::ate);
            if (!file.is_open())
            {
                return std::nullopt; // 파일 열기 실패
            }

            // 2. 현재 위치(=파일 끝)에서 파일 크기 계산
            const size_t fileSize = static_cast<size_t>(file.tellg());
            if (fileSize == 0)
            {
                return std::vector<uint8>{}; // 빈 파일인 경우 빈 벡터 반환
            }

            // 3. 버퍼 할당 후 처음으로 돌아가서 읽기
            std::vector<uint8> buffer(fileSize);
            file.seekg(0, std::ios::beg);
            file.read(reinterpret_cast<char*>(buffer.data()), fileSize);

            // 4. 읽기 도중 오류 확인
            if (!file)
            {
                return std::nullopt; // 읽기 실패
            }

            return buffer;
        }

        /**
         * @brief 지정한 경로의 파일을 읽어 문자열로 반환.
         * @detail 설정 파일 등 텍스트 파일용
         * @param path 읽을 파일의 경로 (std::filesystem::path)
         * @return 파일을 성공적으로 읽으면 파일 내용 전체를 담은 std::string을 포함한 std::optional을 반환. (읽기 실패시 std::nullopt를 반환)
         */
        [[nodiscard]] static std::optional<string> ReadTextFile(const std::filesystem::path& path)
        {
            std::ifstream file(path);   // 텍스트 모드 (binary 플래그 없음)
            if (!file.is_open())
            {
                return std::nullopt;
            }

            // istreambuf_iterator 로 파일 전체를 string으로 읽기
            return string(
                std::istreambuf_iterator<char>(file),
                std::istreambuf_iterator<char>()
            );
        }

        /**
         * @brief 파일 존재 여부 확인
         * @param path 확인할 파일의 경로 (std::filesystem::path)
         * @return 파일이 존재하면 true, 그렇지 않으면 false
         */
        [[nodiscard]] static bool Exists(const std::filesystem::path& path)
        {
            return std::filesystem::exists(path);
        }

        /**
         * @brief 지정한 경로의 파일 크기를 바이트 단위로 반환. 파일이 존재하지 않거나 크기를 가져오는 데 실패하면 std::nullopt를 반환.
         * @param path 크기를 확인할 파일의 경로 (std::filesystem::path)
         * @return 파일 크기를 포함한 std::optional<size_t>를 반환. (실패 시 std::nullopt)
         */
        [[nodiscard]] static std::optional<size_t> GetFileSize(const std::filesystem::path& path)
        {
            std::error_code ec;
            const auto size = std::filesystem::file_size(path, ec);
            if (ec)
            {
                return std::nullopt;
            }

            return static_cast<size_t>(size);
        }
    };
} // namespace TDME