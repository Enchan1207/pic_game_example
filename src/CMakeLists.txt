#
# アプリケーションソース
#
cmake_minimum_required(VERSION 3.21)

add_executable(app)
target_sources(app PRIVATE
    config.c
    gametick.c
    isrs.c
    main.c
    renderer.c
)
target_include_directories(app PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(app PRIVATE
    hardware
)

# リンカオプションの設定, 書込み・デバッグターゲットの追加
if(${BUILD_FOR_PIC})
    target_configure_for_pic(app)
endif()
