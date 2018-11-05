cmake_minimum_required(VERSION 2.9)

project(SMTPClient C CXX)
set (CMAKE_CXX_STANDARD 11)

# Set project name
set(PROJECT_NAME    "SMTPClient")

# Set directories
set(PROJECT_PATH    "${CMAKE_CURRENT_SOURCE_DIR}")
set(INCLUDE_PATH    "${PROJECT_PATH}/Include")
set(SRC_PATH        "${PROJECT_PATH}/Source")
set(TEST_SRC_PATH   "${PROJECT_PATH}/test/smtpclient_unittest")
set(VCPKG_ROOT_PATH "C:/Users/jdumais/documents/vcpkg/installed/x86-windows")

set(GTEST_INCLUDE_DIR   "${VCPKG_ROOT_PATH}/include")
set(GTEST_LIBRARY   "${VCPKG_ROOT_PATH}/debug/lib/manual-link/gtestd.lib")
set(GTEST_MAIN_LIBRARY   "${VCPKG_ROOT_PATH}/debug/lib/manual-link/gtest_maind.lib")

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

include_directories(AFTER "${INCLUDE_PATH}")
include_directories(${GTEST_INCLUDE_DIR})

add_compile_definitions(SMTPCLIENT_EXPORTS)
add_library(${PROJECT_NAME} ${INCLUDE_PATH}
    ${SRC_PATH}/Attachment.cpp
    ${SRC_PATH}/AttachmentError.cpp
    ${SRC_PATH}/Base64.cpp
    ${SRC_PATH}/CommunicationError.cpp
    ${SRC_PATH}/HTMLMessage.cpp
    ${SRC_PATH}/Message.cpp
    ${SRC_PATH}/MessageAddress.cpp
    ${SRC_PATH}/PlainTextMessage.cpp
    ${SRC_PATH}/SMTPClient.cpp
    ${SRC_PATH}/StringUtils.cpp
    )

enable_testing()
find_package(GTest REQUIRED)
add_executable(tests ${INCLUDE_PATH}
${TEST_SRC_PATH}/main.cpp
${TEST_SRC_PATH}/MessageAddress_unittest.cpp
${TEST_SRC_PATH}/Attachment_unittest.cpp
${TEST_SRC_PATH}/PlainTextMessage_unittest.cpp
${TEST_SRC_PATH}/StringUtils_unittest.cpp
)

target_link_libraries(tests ${PROJECT_NAME} ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})
add_test(AllTestsInMain tests)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_range_for)
