#
# ハードウェアライブラリ
#
cmake_minimum_required(VERSION 3.21)

add_library(hardware)
target_sources(hardware PRIVATE
    button.c
    display.c
)
target_include_directories(hardware PUBLIC
    ${PROJECT_SOURCE_DIR}/include/hardware
)
