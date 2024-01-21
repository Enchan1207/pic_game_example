#
# pic_game_example
#
cmake_minimum_required(VERSION 3.21)

# XC8ツールチェーンのダウンロードと有効化
include(FetchContent)
FetchContent_Declare(
    xc8_toolchain
    GIT_REPOSITORY https://github.com/Enchan1207/cmake-xc8
    GIT_TAG v1
)
FetchContent_Populate(xc8_toolchain)
set(CMAKE_TOOLCHAIN_FILE "${xc8_toolchain_SOURCE_DIR}/cmake/xc8_toolchain.cmake")

# ターゲットマイコンと周波数の設定
set(PIC_MCU "16F1936")
set(PIC_FCPU 4000000)

# プロジェクト設定
project(pic_game_example
    VERSION 1.0.0
    DESCRIPTION "Simple games"
    LANGUAGES C
)

# ソースディレクトリ
add_subdirectory(src)
