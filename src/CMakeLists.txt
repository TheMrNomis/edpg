include_directories(${edpg_SOURCE_DIR}/include)

add_executable(edpg
    main.cpp
)

target_link_libraries(edpg
    opencv_core
    opencv_imgproc
    opencv_objdetect
    opencv_imgcodecs
)
