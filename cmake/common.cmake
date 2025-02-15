# Used for the module name on the switch
set(MODULE_NAME ${CMAKE_PROJECT_NAME})
string(LENGTH ${MODULE_NAME} MODULE_NAME_LEN)

# Default compile definitions
add_compile_definitions(
        MODULE_NAME=${CMAKE_PROJECT_NAME}
        MODULE_NAME_LEN=${MODULE_NAME_LEN}
        LOGGER_IP="${LOGGER_IP}"
        LOGGER_PORT=${LOGGER_PORT}
)

# Project sources
include_directories(${PROJECT_SOURCE_DIR}/include/)
include_directories(${LIBNX}/include/)
include_directories(${DEVKITPRO}/portlibs/switch/include/)
# link_directories(${LIBNX}/lib/)
link_directories(${PROJECT_SOURCE_DIR}/libs)
link_directories(${DEVKITPRO}/portlibs/switch/lib)
file(GLOB_RECURSE SOURCES_ASM ${PROJECT_SOURCE_DIR}/src/*.s)
file(GLOB_RECURSE SOURCES_C ${PROJECT_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE SOURCES_CXX ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE SOURCES_SLPATCH ${PROJECT_SOURCE_DIR}/patches/*.slpatch)

# Include nx tools
include(${CMAKE_SOURCE_DIR}/cmake/switch/SwitchTools.cmake)
