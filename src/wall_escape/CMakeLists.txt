#
# 避けゲー
#
cmake_minimum_required(VERSION 3.21)

add_executable(wall_escape)
target_sources(wall_escape PRIVATE
    config.c
    isrs.c
    main.c
)
target_include_directories(wall_escape PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(wall_escape PRIVATE
    hardware
    core
)

# リンカオプションの設定, 書込み・デバッグターゲットの追加
if(${BUILD_FOR_PIC})
    target_configure_for_pic(wall_escape)
endif()
