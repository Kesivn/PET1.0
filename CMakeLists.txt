cmake_minimum_required(VERSION 3.20)

# 项目名与语言
project(PET
    VERSION 0.1.0
    LANGUAGES CXX
)

# ==============================
# 全局编译设置
# ==============================

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# VS 下推荐开启多核编译
if (MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ==============================
# PET 核心库
# ==============================

add_library(pet_core
    src/pet/PET.cpp
    src/fingerprint/Fingerprint.cpp
    src/storage/DummyStorageBlock.cpp
 "src/storage/DummyStorageBlock.h" "src/pet/PETNode.h" "src/pet/PETNode.cpp"  "src/monitoring/statistics.h")

target_include_directories(pet_core
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
)




# ==============================
# 测试可执行文件
# ==============================

add_executable(pet_smoke_test
    tests/pet_smoke_test.cpp
 "src/storage/DummyStorageBlock.h" "src/pet/PETNode.h" "src/pet/PETNode.cpp"  "src/monitoring/statistics.h")

target_link_libraries(pet_smoke_test
    PRIVATE pet_core
)

# ==============================
# 可选：启用测试（为后续 gtest 预留）
# ==============================

enable_testing()

add_test(
    NAME PET_SmokeTest
    COMMAND pet_smoke_test
)
