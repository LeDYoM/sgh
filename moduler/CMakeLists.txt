file (GLOB MODULER_SOURCES "*.cpp")
file (GLOB MODULER_HEADERS "*.hpp")
 
file (GLOB MODULER_INCLUDES "include/*.hpp")
 
source_group("Sources" FILES ${MODULER_SOURCES})
source_group("Headers" FILES ${MODULER_HEADERS})
source_group("Includes" FILES ${MODULER_INCLUDES})
 
include_directories (.)
 
add_library(moduler SHARED ${MODULER_SOURCES} ${MODULER_HEADERS} ${MODULER_INCLUDES})
install (TARGETS moduler RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)