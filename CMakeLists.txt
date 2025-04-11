cmake_minimum_required( VERSION 3.16 )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

project( qalculator LANGUAGES CXX )

find_package( Qt6 REQUIRED COMPONENTS Widgets Gui Quick Qml )
qt_standard_project_setup( REQUIRES 6.5 I18N_SOURCE_LANGUAGE en )

add_subdirectory( src/app )
add_subdirectory( src/style )
add_subdirectory( src/calculator )
