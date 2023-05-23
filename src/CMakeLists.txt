find_package(Gnuplot REQUIRED)
include_directories(${GNUPLOT_INCLUDE_DIRS})

set(CPP_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/Delaunay.cpp)
set(HPP_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/Delaunay.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PlotUtils.hpp)
add_library(TRIMESH ${CPP_SOURCES} ${HPP_HEADERS})

# Link gnuplot
target_link_libraries(TRIMESH PRIVATE ${GNUPLOT_LIBRARIES})
# Link Boost
target_link_libraries(TRIMESH PRIVATE Boost::iostreams Boost::system)

include_directories(${PROJECT_SOURCE_DIR}/external)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/tests)