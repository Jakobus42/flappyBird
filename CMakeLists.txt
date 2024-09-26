cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

# Enable exporting of compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the runtime output directory to the bin folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Option to control whether shared libraries are built or not
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Include FetchContent for SFML
include(FetchContent)

# Fetch SFML repository without EXCLUDE_FROM_ALL
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    SYSTEM)

# Make SFML available to the build without excluding it from all
FetchContent_MakeAvailable(SFML)

# Add the executable and its sources
add_executable(flappyBird 
    src/main.cpp 
    src/entity/Bird.cpp 
    src/entity/AEntity.cpp 
    src/entity/Pipe.cpp 
    src/entity/Floor.cpp 
    src/game/GameManager.cpp 
    src/game/Config.cpp 
    src/entity/Background.cpp
)

# Link SFML to the target
target_link_libraries(flappyBird PRIVATE sfml-graphics)

# Set C++17 standard
target_compile_features(flappyBird PRIVATE cxx_std_17)

# Find and link nlohmann_json
find_package(nlohmann_json 3.2.0 REQUIRED)
target_link_libraries(flappyBird PRIVATE nlohmann_json::nlohmann_json)

# Windows-specific custom command to copy OpenAL DLL
if(WIN32)
    add_custom_command(
        TARGET flappyBird
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
            ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll 
            $<TARGET_FILE_DIR:flappyBird>
        VERBATIM
    )
endif()
