cmake_minimum_required(VERSION 3.10)
project(Zelemi)

include_directories(src/lib src/string)

file(GLOB SOURCES src/*.c src/string/*.c)

add_executable(zelemi ${SOURCES})

install(TARGETS zelemi DESTINATION bin)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -E remove $<TARGET_FILE:zelemi>
)

install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} --build . --target uninstall)")
