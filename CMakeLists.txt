cmake_minimum_required(VERSION 3.26.0)

project(DARKS_ENGINE VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENTIONS off)

file(
  GLOB_RECURSE
  SOURCES
  CONFIGURE_DEPENDS
  "${PROJECT_SOURCE_DIR}/src/*.cpp"
)



add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES} "src/Pong.cpp" "include/Pong.h")


set(SDL2_DIR "D:/SDL/SDL2-2.26.4/cmake")
find_package(SDL2 REQUIRED)


target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${PROJECT_SOURCE_DIR}/include
    )


target_link_libraries(
    ${PROJECT_NAME}
    ${SDL2_LIBRARIES}
    ) 