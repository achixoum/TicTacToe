cmake_minimum_required(VERSION 3.30)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH .)
set(SDL2_image_DIR "C:/libs/SDL2_image-2.8.8/cmake")
set(SDL2_ttf_DIR "C:/libs/SDL2_ttf-2.24.0/cmake")
set(SDL2_TTF_PATH "C:/libs/SDL2_ttf-2.24.0/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
configure_file(images/Tic-tac-toe.bmp ${CMAKE_BINARY_DIR}/images/Tic-Tac-Toe.bmp COPYONLY)
configure_file(images/O.png ${CMAKE_BINARY_DIR}/images/O.png COPYONLY)
configure_file(images/X.png ${CMAKE_BINARY_DIR}/images/X.png COPYONLY)
configure_file(images/ResetButton.png ${CMAKE_BINARY_DIR}/images/ResetButton.png COPYONLY)
configure_file(images/PlayAgainButton.png ${CMAKE_BINARY_DIR}/images/PlayAgainButton.png COPYONLY)
configure_file(images/PlayButton.png ${CMAKE_BINARY_DIR}/images/PlayButton.png COPYONLY)
configure_file(images/game-944386_1280.jpg ${CMAKE_BINARY_DIR}/images/game-944386_1280.jpg COPYONLY)
configure_file(images/QuitButton.png ${CMAKE_BINARY_DIR}/images/QuitButton.png COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/fonts/Montserrat-Bold.ttf ${CMAKE_BINARY_DIR}/fonts/Montserrat-Bold.ttf COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/fonts/Luna.ttf ${CMAKE_BINARY_DIR}/fonts/Luna.ttf COPYONLY)
configure_file(images/Obutton.png ${CMAKE_BINARY_DIR}/images/Obutton.png COPYONLY)
configure_file(images/Xbutton.png ${CMAKE_BINARY_DIR}/images/Xbutton.png COPYONLY)


include_directories("C:/libs/SDL2_image-2.8.8/x86_64-w64-mingw32/include/SDL2")
include_directories("C:/libs/SDL2_ttf-2.24.0/x86_64-w64-mingw32/include/SDL2")

add_executable(TicTacToe main.cpp
        TicTacToe.h
        TicTacToe.cpp
        Symbol.h
        Text.h
        Symbol.cpp
        Text.cpp
        ResourceManager.h
        ResourceManager.cpp
        Button.h
        Button.cpp)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} C:/libs/SDL2_image-2.8.8/x86_64-w64-mingw32/lib/libSDL2_image.a
        C:/libs/SDL2_ttf-2.24.0/x86_64-w64-mingw32/lib/libSDL2_ttf.dll.a -lmingw32 -lSDL2main -lSDL2 -mwindows)

