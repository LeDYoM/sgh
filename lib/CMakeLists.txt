set (LIB_DIRECTORY "./")

set (LIB_DRIVERS_DIRECTORY "${LIB_DIRECTORY}drivers/")
set (LIB_DRIVERS_WINDOW_DIRECTORY "${LIB_DRIVERS_DIRECTORY}window/")
set (LIB_DRIVERS_RENDER_DIRECTORY "${LIB_DRIVERS_DIRECTORY}render/")
file (GLOB LIB_DRIVERS_WINDOW_HEADERS "${LIB_DRIVERS_WINDOW_DIRECTORY}*.hpp")
file (GLOB LIB_DRIVERS_RENDER_HEADERS "${LIB_DRIVERS_RENDER_DIRECTORY}*.hpp")

set (LIB_DRIVERS_IMPLEMENTATION_DIRECTORY "${LIB_DIRECTORY}driv_impl/")
set (LIB_DRIVERS_IMPLEMENTATION_SFML_DIRECTORY "${LIB_DRIVERS_IMPLEMENTATION_DIRECTORY}sfml/")
file (GLOB LIB_DRIVERS_IMPLEMENTATION_SFML_HEADERS "${LIB_DRIVERS_IMPLEMENTATION_SFML_DIRECTORY}*.hpp")
file (GLOB LIB_DRIVERS_IMPLEMENTATION_SFML_SOURCES "${LIB_DRIVERS_IMPLEMENTATION_SFML_DIRECTORY}*.cpp")

file (GLOB LIB_CORE_HEADERS "${LIB_DIRECTORY}core/*.hpp")
file (GLOB LIB_CORE_SOURCES "${LIB_DIRECTORY}core/*.cpp")

file (GLOB LIB_DRAW_HEADERS "${LIB_DIRECTORY}draw/*.hpp")
file (GLOB LIB_DRAW_SOURCES "${LIB_DIRECTORY}draw/*.cpp")

file (GLOB LIB_MANAGERS_HEADERS "${LIB_DIRECTORY}core/managers/*.hpp")
file (GLOB LIB_MANAGERS_SOURCES "${LIB_DIRECTORY}core/managers/*.cpp")


file (GLOB LIB_INCLUDE_HEADERS "${LIB_DIRECTORY}include/*.hpp")
#file (GLOB LIB_BASE_SOURCES "${LIB_DIRECTORY}include/*.cpp")

#TO DO: A separated lib?
file (GLOB LIB_BOARD_HEADERS "${LIB_DIRECTORY}board/*.hpp")
file (GLOB LIB_BOARD_SOURCES "${LIB_DIRECTORY}board/*.cpp")

file (GLOB_RECURSE LIB_HEADERS "${LIB_DIRECTORY}*.hpp")
file (GLOB_RECURSE LIB_SOURCES "${LIB_DIRECTORY}*.cpp")


##############################################################################################

set(CURRENT_TARGET sgh)
add_library(${CURRENT_TARGET} STATIC ${LIB_HEADERS} ${LIB_SOURCES})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set (SFML_ROOT "${CMAKE_SOURCE_DIR}/SFML")

#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${CURRENT_TARGET} ${SFML_LIBRARIES})
endif()

#include myself
include_directories ("../")

#Add SFML directories
#link_directories ("${PROJECT_SOURCE_DIR}/SFML/lib/win32/msvc")
#include_directories ("${PROJECT_SOURCE_DIR}/SFML/include")
#include_directories (${LIB_BASE_DIRECTORY})

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

# Define source groups for lib
#source_group("lib\\Header Files" FILES ${LIB_HEADERS})
#source_group("lib\\Source Files" FILES ${LIB_SOURCES})
source_group("lib\\include" FILES ${LIB_INCLUDE_HEADERS})
source_group("lib\\core" FILES ${LIB_CORE_HEADERS} ${LIB_CORE_SOURCES})
source_group("lib\\core\\events" FILES ${LIB_CORE_EVENTS_HEADERS} ${LIB_CORE_EVENTS_SOURCES})
source_group("lib\\core\\managers" FILES ${LIB_MANAGERS_HEADERS} ${LIB_MANAGERS_SOURCES})
source_group("lib\\draw" FILES ${LIB_DRAW_HEADERS} ${LIB_DRAW_SOURCES})
source_group("lib\\board" FILES ${LIB_BOARD_HEADERS} ${LIB_BOARD_SOURCES})
source_group("lib\\drivers\\window" FILES ${LIB_DRIVERS_WINDOW_HEADERS})
source_group("lib\\drivers\\render" FILES ${LIB_DRIVERS_RENDER_HEADERS})

# For now, add SFML driver implementation
source_group("lib\\driv_implementation\\sfml" FILES ${LIB_DRIVERS_IMPLEMENTATION_SFML_HEADERS}  ${LIB_DRIVERS_IMPLEMENTATION_SFML_SOURCES})

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

#set (SFML_LINK_DLLS_DIR ${PROJECT_SOURCE_DIR}/SFML/shared/win32/msvc)

add_custom_target(copy_zoper_data)
	add_custom_command(TARGET copy_zoper_data PRE_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${PROJECT_SOURCE_DIR}/zoper/data/
		${SGH_OUTPUT_DIRECTORY})

add_custom_target(copy_sfml_dlls)
	add_custom_command(TARGET copy_sfml_dlls PRE_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${SFML_ROOT}/bin"
		${SGH_OUTPUT_DIRECTORY})

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
#install (TARGETS ${CURRENT_TARGET} RUNTIME DESTINATION ${SGH_INSTALL_DIRECTORY})
install (TARGETS ${CURRENT_TARGET} ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/install)
#install(FILES ${SFML_LINK_DLLS_DIR}${CMAKE_BUILD_TYPE}/*.dll DESTINATION ${PROJECT_BINARY_DIR}/bin)
# Copy all assets to resources file
#INSTALL(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/assets/ DESTINATION ${INSTALL_PATH}/assets FILES_MATCHING PATTERN "*.dae"  PATTERN "*.jpg")
