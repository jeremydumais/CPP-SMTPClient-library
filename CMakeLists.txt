cmake_minimum_required(VERSION 2.9)

project(SMTPClient C CXX)

# Set project name
set(PROJECT_NAME    "smtpclient")
set(PROJECT_UNITTEST_NAME   "smtpclient_unittests")

find_program(
    CLANG_TIDY_EXE
    NAMES "clang-tidy"
    DOC "Path to clang-tidy executable"
    )
if(NOT CLANG_TIDY_EXE)
    message(STATUS "clang-tidy not found.")
else()
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-header-filter=.;-line-filter=[{\"name\":\"src/base64.cpp\",\"lines\":[[1000,1000]]},{\"name\":\".h\"},{\"name\":\".cpp\"}];-checks=*,-llvm-header-guard,-google-build-using-namespace,-fuchsia-default-arguments,-modernize-pass-by-value,-fuchsia-overloaded-operator")
endif()

#set(CMAKE_BUILD_TYPE Debug)

# Set directories
set(PROJECT_PATH    "${CMAKE_CURRENT_SOURCE_DIR}")
set(SRC_PATH        "${PROJECT_PATH}/src")
set(TEST_SRC_PATH   "${PROJECT_PATH}/test/smtpclient_unittest")
if (WIN32)
    set(VCPKG_ROOT_PATH "C:/Users/jerem/vcpkg/installed/x86-windows")
    set(GTEST_INCLUDE_DIR   "${VCPKG_ROOT_PATH}/include")
	set(GTEST_LIBRARY   "${VCPKG_ROOT_PATH}/debug/lib/manual-link/gtestd.lib")
	set(GTEST_MAIN_LIBRARY   "${VCPKG_ROOT_PATH}/debug/lib/manual-link/gtest_maind.lib")
	set(PTHREAD		"")
else()
	set(GTEST_LIBRARY	"gtest")
	set(GTEST_MAIN_LIBRARY	"gtest_main")
	set(PTHREAD		"pthread")
endif()

# c++14 required
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-std=c++14 HAS_CXX14_FLAG)
check_cxx_compiler_flag(-std=c++17 HAS_CXX17_FLAG)
check_cxx_compiler_flag(-std=c++2a HAS_CXX20_FLAG)

#if(HAS_CXX20_FLAG)
#    set(CMAKE_CXX_STANDARD 20)
if(HAS_CXX17_FLAG)
    set(CMAKE_CXX_STANDARD 17)
elseif(HAS_CXX14_FLAG)
    set(CMAKE_CXX_STANDARD 14)
else()
    message(FATAL_ERROR "${PROJECT_NAME} requires c++14")
endif()

if(NOT (DEFINED CMAKE_CXX_STANDARD) OR CMAKE_CXX_STANDARD STREQUAL "" OR CMAKE_CXX_STANDARD LESS 14)
    message(FATAL_ERROR "${PROJECT_NAME} requires c++14")
endif()

# Set CMake build-type. If it not supplied by the user, the default built type is "Release".
if(((NOT CMAKE_BUILD_TYPE)
      AND (NOT BUILD_COVERAGE_ANALYSIS))
      OR (CMAKE_BUILD_TYPE STREQUAL "Release"))
          message(STATUS "WARNING: building release version!")
          set(CMAKE_BUILD_TYPE Release)
elseif((CMAKE_BUILD_TYPE STREQUAL "Debug") OR (BUILD_COVERAGE_ANALYSIS))
      message(STATUS "WARNING: building debug version!")
endif(((NOT CMAKE_BUILD_TYPE)
    AND (NOT BUILD_COVERAGE_ANALYSIS))
    OR (CMAKE_BUILD_TYPE STREQUAL "Release"))

#include_directories(AFTER "${INCLUDE_PATH}")
include_directories(${GTEST_INCLUDE_DIR})

add_definitions(-DSMTPCLIENT_EXPORTS)
add_library(${PROJECT_NAME} 
    ${SRC_PATH}/attachment.cpp
    ${SRC_PATH}/attachmenterror.cpp
    ${SRC_PATH}/base64.cpp
    ${SRC_PATH}/communicationerror.cpp
    ${SRC_PATH}/htmlmessage.cpp
    ${SRC_PATH}/message.cpp
    ${SRC_PATH}/messageaddress.cpp
    ${SRC_PATH}/plaintextmessage.cpp
    ${SRC_PATH}/smtpclient.cpp
    ${SRC_PATH}/stringutils.cpp
    )

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	target_compile_definitions(${PROJECT_NAME}
		INTERFACE NOMINMAX # avoid Win macro definition of min/max, use std one
		INTERFACE _SCL_SECURE_NO_WARNINGS # disable security-paranoia warning
		INTERFACE _CRT_SECURE_NO_WARNINGS)
	#target_compile_options(PluginBase
	#  INTERFACE "/W3" # waring level
	#  INTERFACE "/WX") # warning as error
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") # gcc
	# https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
	target_compile_options(${PROJECT_NAME}
        PRIVATE "-Wfatal-errors" # stops on first error
		"-Wall" # enables all the warnings about constructions
		"-Wextra" # Print extra warning messages"
        "-Werror" # Make all warnings into errors.
		"-pedantic" # Issue all the warnings demanded by strict ISO C and ISO C++
		"-pedantic-errors" # Like -pedantic, except that errors are produced rather than warnings http://stackoverflow.com/questions/30255294/how-to-hide-extra-output-from-pragma-message
		"-ftrack-macro-expansion=0"
		"-fno-diagnostics-show-caret"
		)
endif()

#Run clang-tidy on project
if(CLANG_TIDY_EXE)
  set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
endif()

enable_testing()
find_package(GTest REQUIRED)
add_executable(${PROJECT_UNITTEST_NAME} ${INCLUDE_PATH}
${TEST_SRC_PATH}/main.cpp
${TEST_SRC_PATH}/messageaddress_unittest.cpp
${TEST_SRC_PATH}/attachment_unittest.cpp
${TEST_SRC_PATH}/plaintextmessage_unittest.cpp
${TEST_SRC_PATH}/stringutils_unittest.cpp
)

target_link_libraries(${PROJECT_UNITTEST_NAME} ${PROJECT_NAME} ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} ${PTHREAD})
add_test(AllTestsInMain ${PROJECT_UNITTEST_NAME})

install (TARGETS ${PROJECT_NAME} DESTINATION lib)
install(DIRECTORY src/ DESTINATION include/smtpclient
            FILES_MATCHING PATTERN "*.h")

