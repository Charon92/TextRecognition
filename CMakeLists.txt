cmake_minimum_required(VERSION 3.20)
project(TextRecognition)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCE_FILES "src/*.cpp")
file(GLOB HEADER_FILES "include/*.h")

find_package(OpenCV REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(TESSERACT REQUIRED tesseract)
pkg_search_module(LEPTONICA REQUIRED lept)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${TESSERACT_INCLUDE_DIRS})
include_directories(${LEPTONICA_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})
add_library(${PROJECT_NAME}Static STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME} PUBLIC ${OpenCV_LIBS} ${TESSERACT_LIBRARIES} ${LEPTONICA_LIBRARIES})

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION "/"
        )
