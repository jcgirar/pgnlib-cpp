file(GLOB SOURCES *.cpp)
find_package(Boost 1.44 COMPONENTS thread REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
add_library(pgnparser SHARED ${SOURCES})
target_link_libraries(pgnparser ${Boost_LIBRARIES})

