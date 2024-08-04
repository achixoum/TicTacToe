cmake_minimum_required(VERSION 3.27)
project(Projects)

set(CMAKE_CXX_STANDARD 23)

add_compile_options(-IC:/libs/SDL2_ttf-2.22.0/x86_64-w64-mingw32/include/SDL2)
# Ensure the custom modules path is set
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules/ ${CMAKE_MODULE_PATH})

# Set paths to SDL libraries
set(SDL2_PATH "C:/libs/SDL2-2.30.1/x86_64-w64-mingw32")
set(SDL2_IMAGE_PATH "C:/libs/SDL2_image-2.8.2/x86_64-w64-mingw32")
set(SDL2_TTF_PATH "C:/libs/SDL2_ttf-2.22.0/x86_64-w64-mingw32")
set(SDL2_ttf_DIR "C:/libs/SDL2_ttf-2.22.0/cmake")
# Copy image files to build directory
configure_file(images/Tic-tac-toe.bmp ${CMAKE_BINARY_DIR}/images/Tic-Tac-Toe.bmp COPYONLY)
configure_file(images/circle.png ${CMAKE_BINARY_DIR}/images/circle.png COPYONLY)
configure_file(images/X.png ${CMAKE_BINARY_DIR}/images/X.png COPYONLY)
configure_file(images/ResetButton.png ${CMAKE_BINARY_DIR}/images/ResetButton.png COPYONLY)
configure_file(images/PlayAgainButton.png ${CMAKE_BINARY_DIR}/images/PlayAgainButton.png COPYONLY)
configure_file(images/PlayButton.png ${CMAKE_BINARY_DIR}/images/PlayButton.png COPYONLY)
configure_file(images/game-944386_1280.jpg ${CMAKE_BINARY_DIR}/images/game-944386_1280.jpg COPYONLY)
configure_file(images/QuitButton.png ${CMAKE_BINARY_DIR}/images/QuitButton.png COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/fonts/Montserrat-Bold.ttf ${CMAKE_BINARY_DIR}/fonts/Montserrat-Bold.ttf COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/fonts/Luna.ttf ${CMAKE_BINARY_DIR}/fonts/Luna.ttf COPYONLY)

# Find packages
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Manually set the SDL2TTF_LIBRARY if not found automatically
if(NOT SDL2TTF_LIBRARY)
    set(SDL2TTF_LIBRARY "C:/libs/SDL2_ttf-2.22.0/x86_64-w64-mingw32/lib/libSDL2_ttf.dll.a")
endif()

# Debugging
message(STATUS "SDL2_INCLUDE_DIR: ${SDL2_INCLUDE_DIR}")
message(STATUS "SDL2_IMAGE_INCLUDE_DIRS: ${SDL2_IMAGE_INCLUDE_DIRS}")
message(STATUS "SDL2TTF_INCLUDE_DIR: ${SDL2TTF_INCLUDE_DIR}")
message(STATUS "SDL2TTF_LIBRARY: ${SDL2TTF_LIBRARY}")
message(STATUS "SDL2_IMAGE_LIBRARY: ${SDL2_IMAGE_LIBRARY}")

# Include directories
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})

# Add executable
add_executable(Projects main.cpp
        TicTacToe.h
        TicTacToe.cpp
        Symol.h
        Text.h
        Symol.cpp
        Text.cpp
        ResourceManager.h
        ResourceManager.cpp
        Button.h
        Button.cpp
)

# Link libraries
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2TTF_LIBRARY})
