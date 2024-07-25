project(zap2dds)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} "")
target_link_libraries(${PROJECT_NAME} PRIVATE SaveDDS libzap)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
        stb_image_write.cpp
        stb_image_write.h
)
