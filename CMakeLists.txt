cmake_minimum_required (VERSION 2.6)

project (sgh)

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set compiler flags and options. 
# Here it is setting the Visual Studio warning level to 4
if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

message ("cxx Flags: " ${CMAKE_CXX_FLAGS})


# Sub-directories where more CMakeLists.txt exist
#add_subdirectory(extypes)
#add_subdirectory(logger)
#add_subdirectory(loader)
#add_subdirectory(moduler)
#add_subdirectory(filesystem)
#add_subdirectory(configuration)
#add_subdirectory(apprunner)
#add_subdirectory(sghost)

#add_subdirectory(lib)
#add_subdirectory(host)

add_subdirectory(vortex)
add_subdirectory(vrtx_app1)
