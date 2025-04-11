
set( INCLUDES )
set( SOURCES

    ${INCLUDES}
)

qt_add_library( Qalculator.Core STATIC ${SOURCES} )

target_link_libraries( Qalculator.Core PRIVATE Qt6::Core )
target_include_directories( Qalculator.Core PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>" )
