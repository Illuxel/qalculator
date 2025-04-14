if( ANDROID )
    set( JAVA_SOURCES
        android/AndroidManifest.xml
        android/build.gradle
        android/gradle.properties
        android/gradlew
        android/gradlew.bat
        android/src/net/qalculator/AndroidTest.java
    )

    target_sources( Qalculator.App PUBLIC ${JAVA_SOURCES} )

    set_target_properties( Qalculator.App PROPERTIES
        QT_ANDROID_PACKAGE_NAME "Qalculator.App"
        QT_ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android"
    )
endif()

if( WIN32 )
endif()
