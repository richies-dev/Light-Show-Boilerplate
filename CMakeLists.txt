# Projects Settings
cmake_minimum_required (VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# target_compile_options(main PRIVATE -Wall)

project (lightshow-bp)

if(UNIX AND NOT APPLE)
    add_compile_definitions(LINUX)
endif()

#64 bits
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
   set(ARCHITECTURE "64")
#32 bits
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
   set(ARCHITECTURE "86")
endif()


if(CMAKE_BUILD_TYPE MATCHES Debug)
    set("BUILD_TYPE" "Debug")
elseif(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
    set("BUILD_TYPE" "Release")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set("BUILD_TYPE" "Release")
endif()

file(GLOB SOURCE_FILES
    "src/*.h"
    "src/*.cpp"
)

add_executable(main ${SOURCE_FILES})


# SDL2
find_package(SDL2 REQUIRED)
include_directories(main ${SDL2_INCLUDE_DIRS})
string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
target_link_libraries(main PRIVATE ${SDL2_LIBRARIES})
message("${SDL2_INCLUDE_DIRS}")
# SDL_Mixer
find_package(SDL2_mixer REQUIRED)
include_directories(main ${SDL_MIXER_INCLUDE_DIR})
# string(STRIP "${SDL_MIXER_LIBRARY}" SDL_MIXER_LIBRARY)
target_link_libraries(main PRIVATE ${SDL_MIXER_LIBRARY})

# SDL_Image
find_package(SDL2_image REQUIRED)
include_directories(main ${SDL2IMAGE_INCLUDE_DIRS})
# string(STRIP "${SDL_MIXER_LIBRARY}" SDL_MIXER_LIBRARY)
target_link_libraries(main PRIVATE ${SDL2IMAGE_LIBRARIES})

# glew
add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE libglew_static)

# glm
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glm)

# GameNetworkingSockets
find_package(GNS REQUIRED)
include_directories(main ${GNS_INCLUDE_DIRS})
target_link_libraries(main PRIVATE ${GNS_LIBRARIES})

# bullet
include_directories(main lib/bullet/src)
target_link_libraries(main PRIVATE BulletDynamics)
target_link_libraries(main PRIVATE BulletCollision)
target_link_libraries(main PRIVATE LinearMath)
# BulletDynamics.lib;BulletCollision.lib;

#some Bullet specific definitions need to be used, to be compatible
if (USE_DOUBLE_PRECISION)
add_definitions( -DBT_USE_DOUBLE_PRECISION)
set( BULLET_DOUBLE_DEF "-DBT_USE_DOUBLE_PRECISION")
endif (USE_DOUBLE_PRECISION)

add_subdirectory(lib/bullet EXCLUDE_FROM_ALL)


#copy assets to build dir
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

if(WIN32)
    add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different 
            "${SDL2_LIBRARIES_PATH}/SDL2.dll"
            $<TARGET_FILE_DIR:main>
    )
        
    add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory 
            "${SDL2IMAGE_LIBRARIES_PATH}"
            $<TARGET_FILE_DIR:main>
    )

    add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory 
            "${SDL_MIXER_LIBRARY_PATH}"
            $<TARGET_FILE_DIR:main>
    )

    add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different 
            "${GNS_LIBRARIES_PATH}/GameNetworkingSockets.dll"
            $<TARGET_FILE_DIR:main>
    )

    if(BUILD_TYPE MATCHES "Release")

        add_custom_command(
            TARGET main POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different 
                "C:/sdk/protobuf/Release/protobuf-amd${ARCHITECTURE}/bin/libprotobuf.dll"
                $<TARGET_FILE_DIR:main>
        )

    elseif(BUILD_TYPE MATCHES "Debug")

        add_custom_command(
            TARGET main POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different 
                "C:/sdk/protobuf/Debug/protobuf-amd${ARCHITECTURE}/bin/libprotobufd.dll"
                $<TARGET_FILE_DIR:main>
        )
    
    endif()

    if(ARCHITECTURE EQUAL 86)

        add_custom_command(
            TARGET main POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different 
                "C:/Program Files (x86)/OpenSSL-Win32/bin/libcrypto-1_1.dll"
                $<TARGET_FILE_DIR:main>
        )

    elseif(ARCHITECTURE EQUAL 64)

        add_custom_command(
            TARGET main POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different 
                "C:/Program Files/OpenSSL-Win64/bin/libcrypto-1_1-x64.dll"
                $<TARGET_FILE_DIR:main>
        )

    endif()
endif()