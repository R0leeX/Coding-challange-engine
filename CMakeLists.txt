cmake_minimum_required (VERSION 2.6)
project (CodingChallenge)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
    CodeLoader.cpp
    CodeLoader.h
    FileLoader.cpp
    FileLoader.h
    LevelHandler.h
    Levels.h
    main.cpp
    solution.cpp
    constants.h)

add_executable(CodingChallenge ${SOURCE_FILES})

target_link_libraries(CodingChallenge 
    boost_filesystem
    boost_regex
    boost_system
    ${CMAKE_DL_LIBS}
)
