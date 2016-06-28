#set (LIB_DIRECTORY "${LIB_BASE_DIRECTORY}/")

#file (GLOB_RECURSE LIB_HEADERS "${LIB_DIRECTORY}*.hpp")
#file (GLOB_RECURSE LIB_SOURCES "${LIB_DIRECTORY}*.cpp")

#Add SFML directories
#link_directories ("${PROJECT_SOURCE_DIR}/SFML/lib/win32/msvc")
#include_directories ("${PROJECT_SOURCE_DIR}/SFML/include")
#include_directories (${LIB_BASE_DIRECTORY})

#include_directories ("${LIB_DIRECTORY}")

#Temp. That should not be here
include_directories ("${PROJECT_SOURCE_DIR}/SFML/include")
link_directories ("${PROJECT_SOURCE_DIR}/SFML/lib")
#End temp.

include_directories ("${PROJECT_SOURCE_DIR}")
#add_subdirectory (lib)

file (GLOB ZOPER_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
file (GLOB ZOPER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(CURRENT_TARGET host)

add_executable (${CURRENT_TARGET} ${ZOPER_HEADERS} ${ZOPER_SOURCES} 
#${LIB_HEADERS} ${LIB_SOURCES}
)
target_link_libraries(${CURRENT_TARGET} sgh)

set(SGH_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
set(SGH_INSTALL_DIRECTORY ${CMAKE_BINARY_DIR}/install/)
set_target_properties(${CURRENT_TARGET}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${SGH_OUTPUT_DIRECTORY}"
    ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${SGH_OUTPUT_DIRECTORY}"
    ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${SGH_OUTPUT_DIRECTORY}"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${SGH_OUTPUT_DIRECTORY}"
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${SGH_OUTPUT_DIRECTORY}"
    LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${SGH_OUTPUT_DIRECTORY}"
    LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${SGH_OUTPUT_DIRECTORY}"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${SGH_OUTPUT_DIRECTORY}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${SGH_OUTPUT_DIRECTORY}"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${SGH_OUTPUT_DIRECTORY}"
	RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${SGH_OUTPUT_DIRECTORY}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${SGH_OUTPUT_DIRECTORY}"
	OUTPUT_NAME_DEBUG "${CURRENT_TARGET}d"
)

#target_link_libraries(${CURRENT_TARGET} 
#	debug sfml-system-d
#	debug sfml-window-d
#	debug sfml-graphics-d
#	debug sfml-main-d
#	optimized sfml-system
#	optimized sfml-window
#	optimized sfml-graphics
#	optimized sfml-main
#)

if (MSVC)
	file( WRITE "${CMAKE_CURRENT_BINARY_DIR}/${CURRENT_TARGET}.vcxproj.user" 
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>     \
    <Project ToolsVersion=\"4.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">
    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\">
        <LocalDebuggerWorkingDirectory>$(OutDir)</LocalDebuggerWorkingDirectory>
        <DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>
    </PropertyGroup>
    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\">
        <LocalDebuggerWorkingDirectory>$(OutDir)</LocalDebuggerWorkingDirectory>
        <DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>
    </PropertyGroup>
    </Project>")
endif()
		
# Adds logic to INSTALL.vcproj to copy host.exe to destination directory
install (TARGETS host RUNTIME DESTINATION ${SGH_INSTALL_DIRECTORY})
#install(FILES ${SFML_LINK_DLLS_DIR}${CMAKE_BUILD_TYPE}/*.dll DESTINATION ${PROJECT_BINARY_DIR}/bin)
# Copy all assets to resources file
#INSTALL(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/assets/ DESTINATION ${INSTALL_PATH}/assets FILES_MATCHING PATTERN "*.dae"  PATTERN "*.jpg")
