file (GLOB MAIN_SGHOST_HEADERS "*.hpp")
file (GLOB MAIN_SGHOST_SOURCES "*.cpp")

set(CURRENT_TARGET sghost)

add_executable (${CURRENT_TARGET} ${MAIN_SGHOST_HEADERS} ${MAIN_SGHOST_SOURCES})
set(CMAKE_DEBUG_POSTFIX  "d")

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
