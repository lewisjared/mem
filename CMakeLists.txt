project(mem)

cmake_minimum_required(VERSION 2.6)

set (SOURCE_FILES	
	src/mem.c
)

set (INCLUDE_FILES
    include/mem.h
)

# Ensure that eclipse can parse GCCs output
IF(CMAKE_COMPILER_IS_GNUCC)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fmessage-length=0")
ENDIF(CMAKE_COMPILER_IS_GNUCC)
IF(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

include_directories(./include)
add_library(mem STATIC ${SOURCE_FILES})
add_library(memShared SHARED ${SOURCE_FILES})

install (TARGETS mem DESTINATION lib)
install (TARGETS memShared DESTINATION lib)
install (FILES ${INCLUDE_FILES} DESTINATION include)

add_subdirectory(test)