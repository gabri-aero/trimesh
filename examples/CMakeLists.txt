file(GLOB FILES "Case*.cpp")

foreach(FILE ${FILES})
    get_filename_component(FILE_NAME ${FILE} NAME_WE)
    add_executable(${FILE_NAME} ${FILE})
    target_link_libraries(${FILE_NAME} PRIVATE TRIMESH)
    target_include_directories(${FILE_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
endforeach()