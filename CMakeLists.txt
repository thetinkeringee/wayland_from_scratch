cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project("Wayland from Scratch"
    VERSION 0.1.0
    LANGUAGES
    C
)


add_executable( wfs )

set_target_properties( wfs 
    PROPERTIES
    C_STANDARD              99 
    C_STANDARD_REQUIRED     TRUE
    C_EXTENSIONS            FALSE
)

target_include_directories( wfs 
    PRIVATE
    include
)

add_subdirectory(src)
