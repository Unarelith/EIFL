# - C++ Requests, Curl for People
# This module is a libcurl wrapper written in modern C++.
# It provides an easy, intuitive, and efficient interface to
# a host of networking methods.
#
# Finding this module will define the following variables:
#  CPR_FOUND - True if the core library has been found
#  CPR_LIBRARIES - Path to the core library archive
#  CPR_INCLUDE_DIRS - Path to the include directories. Gives access
#                     to cpr.h, which must be included in every
#                     file that uses this interface

find_path(CPR_INCLUDE_DIR NAMES cpr/cpr.h)
find_library(CPR_LIBRARIES NAMES cpr)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CPR DEFAULT_MSG CPR_LIBRARIES CPR_INCLUDE_DIR)

mark_as_advanced(CPR_INCLUDE_DIR CPR_LIBRARIES)

