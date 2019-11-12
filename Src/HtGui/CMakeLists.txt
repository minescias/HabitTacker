cmake_minimum_required(VERSION 3.5)

project(HtGui LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

############################# QtCreator

# przydatne, jeśli uruchamiam projekt z qt creatora. Wtedy wynik trafia od
# razu do odpowiedniego folderu. Zrobiłbym to jakąś zmienną ale QT jest
# chyba zbyt toporny w tej kwestii

#if (QtCreator)
#  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../bin)
#	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../bin)
#	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../bin)
#endif()

include_directories(${CMAKE_SOURCE_DIR}/..)

###########################

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# https://blog.kitware.com/cmake-finding-qt5-the-right-way/
set(Qt5Core_DIR /home/dawid/Qt/5.13.1/gcc_64/lib/cmake/Qt5Core)
set(Qt5Quick_DIR /home/dawid/Qt/5.13.1/gcc_64/lib/cmake/Qt5Quick)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

set(HTGui_src
	main.cpp
	RecentDatabasesModel.cpp)

set(HTGui_res
	qml.qrc)

if(ANDROID)
	add_library(HtGui SHARED ${HTGui_src} ${HTGui_res})
else()
	add_executable(HtGui ${HTGui_src} ${HTGui_res})
endif()

target_compile_definitions(${PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME}
  PRIVATE Qt5::Core Qt5::Quick)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# These variables must use CACHE, otherwise QtCreator won't see them.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android" CACHE INTERNAL "")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so CACHE INTERNAL "")
#    endif()
#endif()
