file (GLOB MAIN_SGHOST_HEADERS "*.hpp")
file (GLOB MAIN_SGHOST_SOURCES "*.cpp")

set(CURRENT_TARGET sghost)

include_directories ("${PROJECT_SOURCE_DIR}/")

add_executable (${CURRENT_TARGET} ${MAIN_SGHOST_HEADERS} ${MAIN_SGHOST_SOURCES})

target_link_libraries (${CURRENT_TARGET} extypes)
target_link_libraries (${CURRENT_TARGET} logger)
target_link_libraries (${CURRENT_TARGET} loader)


set(SGH_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

set_target_properties(${CURRENT_TARGET}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${SGH_OUTPUT_DIRECTORY}"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${SGH_OUTPUT_DIRECTORY}"
	RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${SGH_OUTPUT_DIRECTORY}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${SGH_OUTPUT_DIRECTORY}"
	OUTPUT_NAME_DEBUG "${CURRENT_TARGET}d"
)


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
		
install (TARGETS ${CURRENT_TARGET} RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)
