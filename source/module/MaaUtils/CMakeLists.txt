file(GLOB_RECURSE maa_module_utils_src *.cppm)
file(GLOB_RECURSE maa_utils_src *.cpp)
file(GLOB_RECURSE maa_utils_header ${MAA_MODULE_PRIVATE_INC}/Utils/*)

add_library(MaaUtilsModule SHARED)
target_sources(
    MaaUtilsModule
    PUBLIC FILE_SET CXX_MODULES FILES ${maa_module_utils_src}
    PRIVATE ${${maa_utils_src}})
target_include_directories(MaaUtilsModule PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${MAA_MODULE_PRIVATE_INC}
                                                  ${MAA_PUBLIC_INC})
target_link_libraries(MaaUtilsModule PRIVATE HeaderOnlyLibraries Boost::system ${OpenCV_LIBS})
target_compile_definitions(MaaUtilsModule PRIVATE MAA_UTILS_EXPORTS)

# install( TARGETS MaaUtilsModule EXPORT MaaFrameworkTargets RUNTIME DESTINATION bin LIBRARY DESTINATION bin # ARCHIVE
# DESTINATION lib )

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${maa_module_utils_src} ${maa_utils_src})
