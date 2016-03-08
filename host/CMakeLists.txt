set (LIB_BASE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")
set (LIB_DIRECTORY "${LIB_BASE_DIRECTORY}lib/")

set (LIB_DRIVERS_DIRECTORY "${LIB_DIRECTORY}drivers/")
set (LIB_DRIVERS_WINDOW_DIRECTORY "${LIB_DRIVERS_DIRECTORY}window/")
file (GLOB LIB_DRIVERS_WINDOW_HEADERS "${LIB_DRIVERS_WINDOW_DIRECTORY}*.hpp")

set (LIB_DRIVERS_IMPLEMENTATION_DIRECTORY "${LIB_DIRECTORY}driv_impl/")
set (LIB_DRIVERS_IMPLEMENTATION_SFML_DIRECTORY "${LIB_DRIVERS_IMPLEMENTATION_DIRECTORY}sfml/")
file (GLOB LIB_DRIVERS_IMPLEMENTATION_SFML_WINDOW_HEADERS "${LIB_DRIVERS_IMPLEMENTATION_SFML_DIRECTORY}*.hpp")
file (GLOB LIB_DRIVERS_IMPLEMENTATION_SFML_WINDOW_SOURCES "${LIB_DRIVERS_IMPLEMENTATION_SFML_DIRECTORY}*.cpp")

file (GLOB LIB_CORE_HEADERS "${LIB_DIRECTORY}core/*.hpp")
file (GLOB LIB_CORE_SOURCES "${LIB_DIRECTORY}core/*.cpp")

file (GLOB LIB_CORE_EVENTS_HEADERS "${LIB_DIRECTORY}core/events/*.hpp")
file (GLOB LIB_CORE_EVENTS_SOURCES "${LIB_DIRECTORY}core/events/*.cpp")

file (GLOB LIB_DRAW_HEADERS "${LIB_DIRECTORY}draw/*.hpp")
file (GLOB LIB_DRAW_SOURCES "${LIB_DIRECTORY}draw/*.cpp")

file (GLOB LIB_DATAP_HEADERS "${LIB_DIRECTORY}datap/*.hpp")
file (GLOB LIB_DATAP_SOURCES "${LIB_DIRECTORY}datap/*.cpp")

file (GLOB LIB_UTILP_HEADERS "${LIB_DIRECTORY}util/*.hpp")
file (GLOB LIB_UTILP_SOURCES "${LIB_DIRECTORY}util/*.cpp")

file (GLOB LIB_INCLUDE_HEADERS "${LIB_DIRECTORY}include/*.hpp")
#file (GLOB LIB_BASE_SOURCES "${LIB_DIRECTORY}include/*.cpp")

#TO DO: A separated lib?
file (GLOB LIB_MENU_HEADERS "${LIB_DIRECTORY}menu/*.hpp")
file (GLOB LIB_MENU_SOURCES "${LIB_DIRECTORY}menu/*.cpp")

#TO DO: A separated lib?
file (GLOB LIB_BOARD_HEADERS "${LIB_DIRECTORY}board/*.hpp")
file (GLOB LIB_BOARD_SOURCES "${LIB_DIRECTORY}board/*.cpp")

file (GLOB_RECURSE LIB_HEADERS "${LIB_DIRECTORY}*.hpp")
file (GLOB_RECURSE LIB_SOURCES "${LIB_DIRECTORY}*.cpp")

#Add SFML directories
link_directories ("${PROJECT_SOURCE_DIR}/SFML/lib/win32/msvc")
include_directories ("${PROJECT_SOURCE_DIR}/SFML/include")
include_directories (${LIB_BASE_DIRECTORY})

#TO DO: Remove zoper from here
file (GLOB ZOPER_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
file (GLOB ZOPER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(CURRENT_TARGET host)

add_executable (${CURRENT_TARGET} ${ZOPER_HEADERS} ${ZOPER_SOURCES} ${LIB_HEADERS} ${LIB_SOURCES})
set(SGH_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
set(SGH_INSTALL_DIRECTORY ${CMAKE_BINARY_DIR}/install)
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
source_group("lib\\draw" FILES ${LIB_DRAW_HEADERS} ${LIB_DRAW_SOURCES})
source_group("lib\\util" FILES ${LIB_UTILP_HEADERS} ${LIB_UTILP_SOURCES})
source_group("lib\\datap" FILES ${LIB_DATAP_HEADERS} ${LIB_DATAP_SOURCES})
source_group("lib\\menu" FILES ${LIB_MENU_HEADERS} ${LIB_MENU_SOURCES})
source_group("lib\\board" FILES ${LIB_BOARD_HEADERS} ${LIB_BOARD_SOURCES})
source_group("lib\\drivers\\window" FILES ${LIB_DRIVERS_WINDOW_HEADERS})

# For now, add SFML driver implementation
source_group("lib\\driv_implementation\\sfml\\window" FILES ${LIB_DRIVERS_IMPLEMENTATION_SFML_WINDOW_HEADERS}  ${LIB_DRIVERS_IMPLEMENTATION_SFML_WINDOW_SOURCES})

target_link_libraries(${CURRENT_TARGET} 
	debug sfml-system-d
	debug sfml-window-d
	debug sfml-graphics-d
	debug sfml-main-d
	optimized sfml-system
	optimized sfml-window
	optimized sfml-graphics
	optimized sfml-main
)
set (SFML_LINK_DLLS_DIR ${PROJECT_SOURCE_DIR}/SFML/shared/win32/msvc)

add_custom_target(copy_zoper_data)
	add_custom_command(TARGET copy_zoper_data PRE_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${PROJECT_SOURCE_DIR}/zoper/data/
		${SGH_OUTPUT_DIRECTORY})

add_custom_target(copy_sfml_dlls)
	add_custom_command(TARGET copy_sfml_dlls PRE_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${SFML_LINK_DLLS_DIR}
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
install (TARGETS host RUNTIME DESTINATION ${SGH_INSTALL_DIRECTORY})
#install(FILES ${SFML_LINK_DLLS_DIR}${CMAKE_BUILD_TYPE}/*.dll DESTINATION ${PROJECT_BINARY_DIR}/bin)
# Copy all assets to resources file
#INSTALL(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/assets/ DESTINATION ${INSTALL_PATH}/assets FILES_MATCHING PATTERN "*.dae"  PATTERN "*.jpg")
