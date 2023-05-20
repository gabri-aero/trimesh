file(GLOB CPP_SOURCES "*.cpp")
file(GLOB HPP_HEADERS "*.hpp")
add_library(TRIMESH ${CPP_SOURCES} ${HPP_HEADERS})