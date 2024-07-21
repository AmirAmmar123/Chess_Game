cmake_minimum_required (VERSION 3.15)

project (Chess)

# New CMake versions map C++20 to /std:c++20 instead of c++latest, so <format>
# and other unstable ABI features aren't supported. Use C++23 for such versions
if (MSVC AND CMAKE_VERSION VERSION_GREATER_EQUAL 3.21)
    set(CMAKE_CXX_STANDARD 23)
else ()
    set(CMAKE_CXX_STANDARD 20)
endif ()

set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options (/W4 /permissive- /Zc:externConstexpr /Zc:inline)
endif ()

add_executable (Chess ""
        include/Piece.h
        include/Piece.h
        include/PieceFactory.h
        include/Coordinate.h
        src/Piece.cpp
        include/Rook.h
        include/Knight.h
        include/Bishop.h
        include/King.h
        include/Pawn.h
        include/Queen.h
        src/Bishop.cpp
        include/Color.h
        src/King.cpp
        src/Knight.cpp
        src/Pawn.cpp
        src/Queen.cpp
        src/Rook.cpp
        include/PolyMatrix.h
        include/Blank.h
        src/Blank.cpp
        src/PolyMatrix.cpp
        include/Encode.h
        include/Controller.h
        src/Controller.cpp
        include/MetaData.h
)


add_subdirectory (include)
add_subdirectory (src)



