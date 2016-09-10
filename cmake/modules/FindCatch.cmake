set(BUNDLE_PATH "${DEPENDENCY_DIR}/catch")
set(BUNDLE_URL "https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp")

if (NOT EXISTS "${BUNDLE_PATH}")
    file(DOWNLOAD "${BUNDLE_URL}" "${BUNDLE_PATH}/catch.hpp")
endif()

set(Catch_INCLUDE_DIR "${BUNDLE_PATH}")