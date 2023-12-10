# Finds the GMP C++ library

# Designed to included in the CMAKE_MODULE_PATH and called using find_package
# Inspired by https://dominikberner.ch/cmake-find-library/
include(GNUInstallDirs)

find_library(
        GMP_SHARED_LIBRARY
        GMP
        NAMES libgmpxx.so
        PATH_SUFFIXES lib lib64
)

find_library(
        GMP_STATIC_LIBRARY
        GMP
        NAMES libgmpxx.a
        PATH_SUFFIXES lib lib64
)

find_path(GMP_INCLUDE_DIR
        GMP
        NAMES GMP gmpxx.h
        PATH_SUFFIXES include
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(GMP DEFAULT_MSG
        GMP_SHARED_LIBRARY
        GMP_STATIC_LIBRARY
        GMP_INCLUDE_DIR)

mark_as_advanced(GMP_LIBRARY GMP_INCLUDE_DIR)

if (GMP_FOUND AND NOT TARGET GMP::SHARED)
    add_library(GMP::SHARED SHARED IMPORTED)
    target_include_directories(GMP::SHARED INTERFACE ${GMP_INCLUDE_DIR})
    target_link_libraries(GMP::SHARED INTERFACE ${GMP_SHARED_LIBRARY})
    set_target_properties(
            GMP::SHARED
            PROPERTIES
            IMPORTED_LOCATION ${GMP_SHARED_LIBRARY}
    )
endif ()

if (GMP_FOUND AND NOT TARGET GMP::STATIC)
    add_library(GMP::STATIC STATIC IMPORTED)
    target_include_directories(GMP::STATIC INTERFACE ${GMP_INCLUDE_DIR})
    target_link_libraries(GMP::STATIC INTERFACE ${GMP_STATIC_LIBRARY})
    set_target_properties(
            GMP::STATIC
            PROPERTIES
            IMPORTED_LOCATION ${GMP_STATIC_LIBRARY}
    )
endif ()
