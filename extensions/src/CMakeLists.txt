# SPDX-License-Identifier: Unlicense

target_sources( ${PROJECT_NAME}
    PRIVATE
        Example.h
        Example.cpp
        GDExtensionTemplate.h
        GDExtensionTemplate.cpp
        RegisterExtension.cpp
        Voronoi.cpp
        Voronoi.hpp
)

target_include_directories( ${PROJECT_NAME}
    PRIVATE
        "src"
)
