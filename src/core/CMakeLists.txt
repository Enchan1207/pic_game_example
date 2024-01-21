#
# ゲームのコアライブラリ
#
cmake_minimum_required(VERSION 3.21)

add_library(core)
target_sources(core PRIVATE
    gametick.c
    renderer.c
)
target_include_directories(core PUBLIC
    ${PROJECT_SOURCE_DIR}/include/core
)
