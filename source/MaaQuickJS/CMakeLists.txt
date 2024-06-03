add_compile_options("/sdl-;/wd4146;/wd4820;/wd4100;/wd4267;/wd4018;/wd4242;/wd4244;/wd5250;/wd4295")
add_compile_options("/wd4245;/wd5045;/wd5045;/wd4457;/wd4388;/wd4200;/wd4256;/wd4068;/wd4115;/wd4456")
add_compile_options(
    "/wd4389;/wd4706;/wd4389;/wd4152;/wd4996;/wd4702;/wd4132;/wd4061;/wd4101;/wd4334;/wd4701;/wd4189;/wd4576")

add_subdirectory(quickjs)

add_executable(MaaQuickJS test.cpp)
target_link_libraries(MaaQuickJS qjs)
