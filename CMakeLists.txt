cmake_minimum_required(VERSION 3.10)
project(Zelemi)

# Set C standard and prevent compilation if not supported
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(src/libs src/com config)

file(GLOB SOURCES 
    src/err.c 
    src/load.c 
    src/main.c 
    src/zelemi.c 
    src/com/adr.c 
    src/com/clr.c 
    src/com/end.c 
    src/com/hlp.c 
    src/com/lic.c 
    src/com/chk.c 
    src/com/run.c
    src/com/nmb.c
    src/com/ldf.c
    src/com/c_run_commands.c 
    src/com/adr-reg/reg_x86_64.c
    
)

add_executable(zelemi ${SOURCES})

link_directories(/usr/local/lib)
target_link_libraries(zelemi pgetopt)
target_link_libraries(zelemi pstring)
set_target_properties(zelemi PROPERTIES
    INSTALL_RPATH /usr/local/lib
)

install(TARGETS zelemi DESTINATION /usr/bin)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -E remove /usr/bin/zelemi
    COMMENT "Uninstalling zelemi"
)

message(STATUS "To uninstall zelemi, run: make uninstall")
