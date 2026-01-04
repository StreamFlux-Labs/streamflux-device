# tests/CMakeLists.txt

include(FetchContent)

# 1. Khai báo tải GoogleTest từ GitHub
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# Tắt tính năng cài đặt GTest vào hệ thống (chỉ dùng cục bộ cho project này)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

# 2. Tải và tích hợp code GTest
FetchContent_MakeAvailable(googletest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests")

# 3. Tạo file chạy test (executable) từ file cpp mẫu
add_executable(unit_tests test_main.cpp)

# 4. Link thư viện GTest vào executable
# gtest_main: Đã có sẵn hàm main(), bạn không cần viết int main() nữa.
target_link_libraries(unit_tests GTest::gtest_main)

# LƯU Ý QUAN TRỌNG:
# Nếu bạn muốn test code trong thư mục src/, bạn cần link thư viện của project chính vào đây.
# Ví dụ nếu ở root bạn có add_library(my_core_lib ...), thì uncomment dòng dưới:
# target_link_libraries(unit_tests my_core_lib)

# 5. Đăng ký test để CTest nhận diện (cho lệnh 'ctest')
include(GoogleTest)
gtest_discover_tests(unit_tests
    DISCOVERY_MODE PRE_TEST
)
