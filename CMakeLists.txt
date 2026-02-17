cmake_minimum_required(VERSION 3.10)
project(Zelemi)

include_directories(src/libs src/com config)

file(GLOB SOURCES 
    src/libs/error_handle.c 
    src/load.c 
    src/main.c 
    src/trim.c 
    src/zelemi.c 
    src/com/adr.c 
    src/com/clr.c 
    src/com/c_run_commands.c 
    src/com/end.c 
    src/com/hlp.c 
    src/com/lic.c 
    src/com/run.c
)

add_executable(zelemi ${SOURCES})

link_directories(/usr/local/lib)
target_link_libraries(zelemi pgetopt)
set_target_properties(zelemi PROPERTIES
    INSTALL_RPATH /usr/local/lib
)

install(TARGETS zelemi DESTINATION /usr/bin)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -E remove $<TARGET_FILE:zelemi>
    COMMENT "Uninstalling zelemi"
)