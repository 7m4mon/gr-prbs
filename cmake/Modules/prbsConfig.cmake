INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_PRBS prbs)

FIND_PATH(
    PRBS_INCLUDE_DIRS
    NAMES prbs/api.h
    HINTS $ENV{PRBS_DIR}/include
        ${PC_PRBS_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    PRBS_LIBRARIES
    NAMES gnuradio-prbs
    HINTS $ENV{PRBS_DIR}/lib
        ${PC_PRBS_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/prbsTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(PRBS DEFAULT_MSG PRBS_LIBRARIES PRBS_INCLUDE_DIRS)
MARK_AS_ADVANCED(PRBS_LIBRARIES PRBS_INCLUDE_DIRS)
