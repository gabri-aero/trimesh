enable_testing()

file(GLOB FILES "Test*.cpp")

include(GoogleTest)

foreach(FILE ${FILES})
    get_filename_component(FILE_NAME ${FILE} NAME_WE)
    add_executable(${FILE_NAME} ${FILE})
    target_link_libraries(${FILE_NAME} PRIVATE TRIMESH  GTest::gtest_main)
    message("${FILE_NAME} added as an executable")
    gtest_discover_tests(${FILE_NAME})
endforeach()


include_directories(${CMAKE_SOURCE_DIR}/src)