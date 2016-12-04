# Lineage:
# https://github.com/forexample/ios-dynamic-framework

cmake_minimum_required(VERSION 3.0)
project(Bar VERSION 1.2.3)

add_library(bar SHARED bar.cpp bar.hpp)

include(GenerateExportHeader)
generate_export_header(bar)

target_include_directories(
    bar PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
)

set_target_properties(
    bar
    PROPERTIES

    # Hidden
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
    XCODE_ATTRIBUTE_GCC_INLINES_ARE_PRIVATE_EXTERN YES
    XCODE_ATTRIBUTE_GCC_SYMBOLS_PRIVATE_EXTERN YES

    # Strip
    XCODE_ATTRIBUTE_COPY_PHASE_STRIP "YES"
    XCODE_ATTRIBUTE_STRIP_INSTALLED_PRODUCT "YES"
    XCODE_ATTRIBUTE_STRIP_STYLE "non-global"
    XCODE_ATTRIBUTE_STRIPFLAGS "-x -u -r"
    XCODE_ATTRIBUTE_DEAD_CODE_STRIPPING "YES"
    XCODE_ATTRIBUTE_DEPLOYMENT_POSTPROCESSING "YES"

    # This line will trigger a linker assertion: "need to handle arm64 -r reloc"
    XCODE_ATTRIBUTE_GENERATE_MASTER_OBJECT_FILE "YES" # "Perform Single-Object Prelink"    
    )

set(config_install_dir "lib/cmake/${PROJECT_NAME}")
set(include_install_dir "include")

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(targets_export_name "${PROJECT_NAME}Targets")
set(namespace "${PROJECT_NAME}::")

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${version_config}" COMPATIBILITY SameMajorVersion
)

configure_file("cmake/Config.cmake.in" "${project_config}" @ONLY)

install(
    TARGETS bar
    EXPORT "${targets_export_name}"
    LIBRARY DESTINATION "lib"
    ARCHIVE DESTINATION "lib"
    RUNTIME DESTINATION "bin"
    INCLUDES DESTINATION "${include_install_dir}"
)

install(FILES "bar.hpp" DESTINATION "include/bar")

install(
    FILES "${project_config}" "${version_config}"
    DESTINATION "${config_install_dir}"
)

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/bar_export.h"
    DESTINATION "${include_install_dir}"
)

install(
    EXPORT "${targets_export_name}"
    NAMESPACE "${namespace}"
    DESTINATION "${config_install_dir}"
)
