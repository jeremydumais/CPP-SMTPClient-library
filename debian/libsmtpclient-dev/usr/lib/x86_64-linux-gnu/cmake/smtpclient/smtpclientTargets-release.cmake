#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "smtpclient::smtpclient" for configuration "Release"
set_property(TARGET smtpclient::smtpclient APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(smtpclient::smtpclient PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/x86_64-linux-gnu/libsmtpclient.so.1.1.13"
  IMPORTED_SONAME_RELEASE "libsmtpclient.so.1"
  )

list(APPEND _cmake_import_check_targets smtpclient::smtpclient )
list(APPEND _cmake_import_check_files_for_smtpclient::smtpclient "${_IMPORT_PREFIX}/lib/x86_64-linux-gnu/libsmtpclient.so.1.1.13" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
