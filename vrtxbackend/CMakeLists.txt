file (GLOB _SOURCES "*.cpp")
file (GLOB _HEADERS "*.hpp")
 
file (GLOB _INCLUDES "include/*.hpp")

set (CURRENT_TARGET vrtxbackend) 
set(CMAKE_DEBUG_POSTFIX  "d") 

source_group("Sources" FILES ${_SOURCES})
source_group("Headers" FILES ${_HEADERS})
source_group("Includes" FILES ${_INCLUDES})

add_library(${CURRENT_TARGET} SHARED ${_SOURCES} ${_HEADERS} ${_INCLUDES})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set (SFML_ROOT "${CMAKE_SOURCE_DIR}/SFML")

#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics
 #network audio
 )
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${CURRENT_TARGET} ${SFML_LIBRARIES})
endif()

set(_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

set_target_properties(${CURRENT_TARGET}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${_OUTPUT_DIRECTORY}"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${_OUTPUT_DIRECTORY}"
	RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${_OUTPUT_DIRECTORY}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${_OUTPUT_DIRECTORY}"
)

install (TARGETS ${CURRENT_TARGET} RUNTIME DESTINATION ${_OUTPUT_DIRECTORY})
