set (INCLUDE_DIRECTORY "include")

file (GLOB SOURCES "*.cpp")
file (GLOB HEADERS "*.hpp")
file (GLOB PUBLIC_HEADERS "${INCLUDE_DIRECTORY}/*.hpp")

##############################################################################################

set(CURRENT_TARGET sghcommon)
add_library(${CURRENT_TARGET} SHARED ${PUBLIC_HEADERS} ${HEADERS} ${SOURCES})

# Define source groups
source_group("include" FILES ${PUBLIC_HEADERS})
source_group("Header Files" FILES ${HEADERS})
source_group("Source Files" FILES ${SOURCES})

# Adds logic to INSTALL.vcproj to copy host.exe to destination directory
#install (TARGETS ${CURRENT_TARGET} ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/install)
#install(FILES ${SFML_LINK_DLLS_DIR}${CMAKE_BUILD_TYPE}/*.dll DESTINATION ${PROJECT_BINARY_DIR}/bin)
# Copy all assets to resources file
#INSTALL(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/assets/ DESTINATION ${INSTALL_PATH}/assets FILES_MATCHING PATTERN "*.dae"  PATTERN "*.jpg")
