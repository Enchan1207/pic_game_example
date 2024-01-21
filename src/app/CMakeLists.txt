#
# アプリケーションソース
#
cmake_minimum_required(VERSION 3.21)

# 避けゲー
add_executable(wall_escape)
target_sources(wall_escape PRIVATE
    collision.c
    config.c
    isrs.c
    main.c
    wall.c
)
target_include_directories(wall_escape PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(wall_escape PRIVATE
    hardware
    core
)
if(${BUILD_FOR_PIC})
    target_configure_for_pic(wall_escape)
endif()

# フラッピーバード
add_executable(flappy_bird)
target_sources(flappy_bird PRIVATE
    collision.c
    config.c
    isrs.c
    main.c
    wall.c
)
target_include_directories(flappy_bird PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(flappy_bird PRIVATE
    hardware
    core
)
target_compile_definitions(flappy_bird PRIVATE
    FLAPPY_BIRD=1
)
if(${BUILD_FOR_PIC})
    target_configure_for_pic(flappy_bird)
endif()
