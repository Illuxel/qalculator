cmake_minimum_required( VERSION 3.16 )

project( qalculator VERSION 0.5.0 LANGUAGES CXX )

find_package( Qt6 COMPONENTS Core Gui Quick Qml REQUIRED )

qt_standard_project_setup( REQUIRES 6.5 )
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

add_subdirectory( src/app )
