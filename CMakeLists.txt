cmake_minimum_required(VERSION 3.16)
project(SongProcessor VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(PkgConfig REQUIRED)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

# Create the main library
add_library(song_processor_lib
    src/audio/audio_loader.cpp
    src/audio/audio_writer.cpp
    src/signal/filter.cpp
    src/signal/fft.cpp
    src/signal/spectrum_analyzer.cpp
    src/effects/reverb.cpp
    src/effects/echo.cpp
    src/effects/compressor.cpp
    src/utils/audio_utils.cpp
    src/utils/math_utils.cpp
)

# Create the main executable
add_executable(song_processor main.cpp)
target_link_libraries(song_processor song_processor_lib)

# Set compiler flags
target_compile_options(song_processor_lib PRIVATE -Wall -Wextra -O2)
target_compile_options(song_processor PRIVATE -Wall -Wextra -O2)

# Installation
install(TARGETS song_processor_lib song_processor
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/ DESTINATION include) 