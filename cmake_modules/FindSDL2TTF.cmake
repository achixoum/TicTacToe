# FindSDL2_ttf.cmake

find_path(SDL2TTF_INCLUDE_DIR SDL_ttf.h
        HINTS
        ${SDL2_TTF_PATH}/include/SDL2
)

find_library(SDL2TTF_LIBRARY NAMES SDL2_ttf libSDL2_ttf libSDL2_ttf.a libSDL2_ttf.dll.a
        HINTS
        ${SDL2_TTF_PATH}/lib
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL2_ttf DEFAULT_MSG
        SDL2TTF_INCLUDE_DIR SDL2TTF_LIBRARY
)

mark_as_advanced(SDL2TTF_INCLUDE_DIR SDL2TTF_LIBRARY)
