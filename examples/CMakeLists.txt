file(GLOB FILES "Case*.cpp")

find_package(Gnuplot REQUIRED)
include_directories(${GNUPLOT_INCLUDE_DIRS})

foreach(FILE ${FILES})
    get_filename_component(FILE_NAME ${FILE} NAME_WE)
    add_executable(${FILE_NAME} ${FILE})
    # Link Trimesh
    target_link_libraries(${FILE_NAME} PRIVATE TRIMESH)
    # Link gnuplot
    target_link_libraries(${FILE_NAME} ${GNUPLOT_LIBRARIES})
    # Link Boost
    target_link_libraries(${FILE_NAME} PRIVATE Boost::iostreams Boost::system)

    message("${FILE_NAME} added as an executable")
endforeach()

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/external)