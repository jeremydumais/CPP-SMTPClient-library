cmake_minimum_required(VERSION 3.10)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

project(SMTPClient C CXX)

# Set project name
set(PROJECT_NAME    "smtpclient")
set(PROJECT_UNITTEST_NAME   "smtpclient_unittests")

find_package(OpenSSL REQUIRED)

find_program(
    CLANG_TIDY_EXE
    NAMES "clang-tidy"
    DOC "Path to clang-tidy executable"
    )
if(NOT CLANG_TIDY_EXE)
    message(STATUS "clang-tidy not found.")
else()
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-header-filter=.;
    -line-filter=[{\"name\":\"src/base64.cpp\",\"lines\":[[1000,1000]]},{\"name\":\".h\"},{\"name\":\".cpp\"}];
    -checks=*,
    -llvm-header-guard,
    -google-build-using-namespace,
    -fuchsia-default-arguments,
    -modernize-pass-by-value,
    -fuchsia-overloaded-operator,
    -cppcoreguidelines-pro-bounds-pointer-arithmetic,
    -cppcoreguidelines-owning-memory,
    -modernize-use-trailing-return-type,
    -fuchsia-default-arguments-calls")
endif()

# Set directories
set(PROJECT_PATH    "${CMAKE_CURRENT_SOURCE_DIR}")
set(SRC_PATH        "${PROJECT_PATH}/src")
set(TEST_SRC_PATH   "${PROJECT_PATH}/test/smtpclient_unittest")
if (WIN32)
    set(PTHREAD		"")
    option(VCPKG_APPLOCAL_DEPS "Automatically copy dependencies into the output directory for executables." ON)
else()
    set(PTHREAD		"pthread")
endif()

# c++14 required
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-std=c++14 HAS_CXX14_FLAG)
check_cxx_compiler_flag(-std=c++17 HAS_CXX17_FLAG)
check_cxx_compiler_flag(-std=c++2a HAS_CXX20_FLAG)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC") # the quotes are needed here, maybe because "MSVC" seems to be a keyword
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19)
        message(FATAL_ERROR "Visual Studio 2015 or newer is required.")
    endif()
else()
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

set(PROJECT_SOURCE_FILES ${SRC_PATH}/attachment.cpp
    ${SRC_PATH}/base64.cpp
    ${SRC_PATH}/credential.cpp
    ${SRC_PATH}/htmlmessage.cpp
    ${SRC_PATH}/message.cpp
    ${SRC_PATH}/messageaddress.cpp
    ${SRC_PATH}/plaintextmessage.cpp
    ${SRC_PATH}/smtpclientbase.cpp
    ${SRC_PATH}/smtpclient.cpp
    ${SRC_PATH}/securesmtpclientbase.cpp
    ${SRC_PATH}/opportunisticsecuresmtpclient.cpp
    ${SRC_PATH}/forcedsecuresmtpclient.cpp
    ${SRC_PATH}/serveroptionsanalyzer.cpp
    ${SRC_PATH}/stringutils.cpp
    ${SRC_PATH}/errorresolver.cpp
    ${SRC_PATH}/cpp/attachment.cpp
    ${SRC_PATH}/cpp/credential.cpp
    ${SRC_PATH}/cpp/forcedsecuresmtpclient.cpp
    ${SRC_PATH}/cpp/htmlmessage.cpp
    ${SRC_PATH}/cpp/plaintextmessage.cpp
    ${SRC_PATH}/cpp/message.cpp
    ${SRC_PATH}/cpp/messageaddress.cpp
    ${SRC_PATH}/cpp/opportunisticsecuresmtpclient.cpp
    ${SRC_PATH}/cpp/smtpclient.cpp)

if (WIN32)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)
    include(generate_product_version)
    generate_product_version(
        VersionFilesOutputVariable
        NAME "CPP-SMTPClient-library"
        ICON "${PATH_TO_APPLICATION_ICON}"
        VERSION_MAJOR 1
        VERSION_MINOR 1
        VERSION_PATCH 7
        VERSION_REVISION ${BUILD_REVISION}
        )
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    #If OPENSSL_ROOT_DIR was not provided search for the environment variable
    if (NOT DEFINED OPENSSL_ROOT_DIR)
        message(STATUS "No OPENSSL_ROOT_DIR variable provided so searching for the OPENSSL_ROOT_DIR environment variable...")
        if (NOT DEFINED ENV{OPENSSL_ROOT_DIR})
            message(STATUS "No OPENSSL_ROOT_DIR environment variable found.")
        else()
            message(STATUS "Found OPENSSL_ROOT_DIR=$ENV{OPENSSL_ROOT_DIR} as an environment variable.")
        endif()
        set(OPENSSL_ROOT_DIR $ENV{OPENSSL_ROOT_DIR})
    endif()
    if (NOT DEFINED OPENSSL_INCLUDE_DIRECTORY)
        set(OPENSSL_INCLUDE_DIRECTORY ${OPENSSL_ROOT_DIR}/include)
    endif()
    message(STATUS "Will use OpenSSL include directory ${OPENSSL_INCLUDE_DIRECTORY}")
    include_directories(${OPENSSL_INCLUDE_DIRECTORY})
    if (NOT DEFINED OPENSSL_LIBRARY_DIRECTORY)
        set(OPENSSL_LIBRARY_DIRECTORY ${OPENSSL_ROOT_DIR}/lib)
    endif()
    message(STATUS "Will use OpenSSL lib directory ${OPENSSL_LIBRARY_DIRECTORY}")
    link_directories(${OPENSSL_LIBRARY_DIRECTORY})
    message(STATUS "Will use OpenSSL libraries files ${OPENSSL_CRYPTO_LIBRARY} ${OPENSSL_SSL_LIBRARY}")
    add_library(${PROJECT_NAME} SHARED
        ${PROJECT_SOURCE_FILES} ${VersionFilesOutputVariable})
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_compile_options(/EHsc)
    target_compile_options(${PROJECT_NAME} PRIVATE /W3 /WX)
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE SMTPCLIENT_EXPORTS
        INTERFACE NOMINMAX # avoid Win macro definition of min/max, use std one
        INTERFACE _SCL_SECURE_NO_WARNINGS) # disable security-paranoia warning
    target_link_libraries(${PROJECT_NAME} Ws2_32 ${OPENSSL_CRYPTO_LIBRARY} ${OPENSSL_SSL_LIBRARY} crypt32 cryptui)
else()
    #For other compiler create the library as a static library
    add_library(${PROJECT_NAME}
        ${PROJECT_SOURCE_FILES})
    target_include_directories(${PROJECT_NAME} PUBLIC ${OPENSSL_INCLUDE_DIR})
    get_filename_component(ssl_libdir ${OPENSSL_SSL_LIBRARY} DIRECTORY)
    target_link_directories(${PROJECT_NAME} PUBLIC ${ssl_libdir})
    target_link_libraries(${PROJECT_NAME} ssl crypto)
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") #gcc
        # https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
        target_compile_options(${PROJECT_NAME}
            PRIVATE "-Wfatal-errors" # stops on first error
            "-Wall" # enables all the warnings about constructions
            "-Wextra" # Print extra warning messages"
            "-pedantic" # Issue all the warnings demanded by strict ISO C and ISO C++
            "-Wshadow" # Warn the user if a variable declaration shadows one from a parent context
            "-Wnon-virtual-dtor" # Warn the user if a class with virtual functions has a non-virtual destructor. This helps catch hard to track down memory errors
            "-Wold-style-cast" # Warn for c-style casts
            "-Wcast-align" # Warn for potential performance problem casts
            "-Wunused" # warn on anything being unused
            "-Woverloaded-virtual" # warn if you overload (not override) a virtual function
            "-Wpedantic" # (all versions of GCC, Clang >= 3.2) warn if non-standard C++ is used
            "-Wconversion" # warn on type conversions that may lose data
            "-Wsign-conversion" # (Clang all versions, GCC >= 4.3) warn on sign conversions
            "-Wmisleading-indentation" # (only in GCC >= 6.0) warn if indentation implies blocks where blocks do not exist
            "-Wduplicated-cond" # (only in GCC >= 6.0) warn if if / else chain has duplicated conditions
            "-Wduplicated-branches" # (only in GCC >= 7.0) warn if if / else branches have duplicated code
            "-Wlogical-op" # (only in GCC) warn about logical operations being used where bitwise were probably wanted
            "-Wnull-dereference" # (only in GCC >= 6.0) warn if a null dereference is detected
            "-Wuseless-cast" # (only in GCC >= 4.8) warn if you perform a cast to the same type
            "-Wdouble-promotion" # (GCC >= 4.6, Clang >= 3.8) warn if float is implicit promoted to double
            "-Wformat=2" # warn on security issues around functions that format output (ie printf)
            "-fPIC"
            )
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        target_compile_options(${PROJECT_NAME}
            PRIVATE "-Wfatal-errors" # stops on first error
            "-Wall" # enables all the warnings about constructions
            "-Wextra" # Print extra warning messages"
            "-Werror" # Make all warnings into errors.
            "-Wno-unused-lambda-capture" # FIX: It is necessary when building on MSVC
            "-pedantic" # Issue all the warnings demanded by strict ISO C and ISO C++
            "-pedantic-errors" # Like -pedantic, except that errors are produced rather than warnings http://stackoverflow.com/questions/30255294/how-to-hide-extra-output-from-pragma-message
            "-fPIC"
            )
    endif()
endif()

#Run clang-tidy on project
if(CLANG_TIDY_EXE AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
endif()

if (BUILD_TESTING)
    enable_testing()

    # Download and unpack googletest at configure time
    configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
    if(result)
        message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif()
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
    if(result)
        message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif()

    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add googletest directly to our build. This defines
    # the gtest and gtest_main targets.
    add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)
    include(GoogleTest)

    add_executable(${PROJECT_UNITTEST_NAME} ${INCLUDE_PATH}
        ${TEST_SRC_PATH}/main.cpp
        ${TEST_SRC_PATH}/messageaddress_unittest.cpp
        ${TEST_SRC_PATH}/message_unittest.cpp
        ${TEST_SRC_PATH}/message_cpp_unittest.cpp
        ${TEST_SRC_PATH}/attachment_unittest.cpp
        ${TEST_SRC_PATH}/credential_unittest.cpp
        ${TEST_SRC_PATH}/htmlmessage_cpp_unittest.cpp
        ${TEST_SRC_PATH}/plaintextmessage_unittest.cpp
        ${TEST_SRC_PATH}/plaintextmessage_cpp_unittest.cpp
        ${TEST_SRC_PATH}/stringutils_unittest.cpp
        ${TEST_SRC_PATH}/opportunisticsecuresmtpclient_unittest.cpp
        ${TEST_SRC_PATH}/smtpclientbase_unittest.cpp
        ${TEST_SRC_PATH}/smtpclient_unittest.cpp
        ${TEST_SRC_PATH}/serveroptionsanalyzer_unittest.cpp
        ${TEST_SRC_PATH}/errorresolver_unittest.cpp)

    target_link_libraries(${PROJECT_UNITTEST_NAME} ${PROJECT_NAME} gtest gtest_main ${PTHREAD})
    gtest_discover_tests(${PROJECT_UNITTEST_NAME})
endif()

install (TARGETS ${PROJECT_NAME} DESTINATION lib)
install(DIRECTORY src/ DESTINATION include/smtpclient
    FILES_MATCHING PATTERN "*.h")

# Uninstall target
CONFIGURE_FILE(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/CMakeUninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/CMakeUninstall.cmake"
    IMMEDIATE @ONLY)
ADD_CUSTOM_TARGET(uninstall
    "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake/CMakeUninstall.cmake")

if(EXISTS ${PROJECT_PATH}/simpleclient AND IS_DIRECTORY ${PROJECT_PATH}/simpleclient)
    add_subdirectory(${PROJECT_PATH}/simpleclient)
endif()

if(BUILD_EXAMPLE)
    add_executable(emails-example src/cpp/example/send-mail.cpp)
    target_include_directories(emails-example PUBLIC ${CMAKE_SOURCE_DIR}/src)
    target_link_libraries(emails-example smtpclient ssl crypto stdc++)
endif()
