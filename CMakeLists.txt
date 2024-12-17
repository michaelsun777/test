cmake_minimum_required(VERSION 3.18)

project(testQtCef)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")

# SET(CMAKE_BUILD_TYPE "Release")
# SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON) #相当于-fpic


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)

add_definitions(-D_SILENCE_CXX17_RESULT_OF_DEPRECATION_WARNING=1)
set(PROJECT_ARCH "x86_64")

add_definitions(-DOS_LINUX=1 -DOS_POSIX=1)
add_compile_options(
  "-g"
  "$<$<CONFIG:DEBUG>:-O0>"
  "$<$<CONFIG:RELEASE>:-O3>"
)
add_compile_options(-m64 -march=x86-64)
add_link_options(-m64)


# find_package(Boost REQUIRED COMPONENTS thread chrono)
# if(Boost_FOUND)
#     include_directories(${Boost_INCLUDE_DIR})
# endif()



#set(QT_PATH "/opt/Qt5.14.2/5.14.2/gcc_64/")
#set(CMAKE_PREFIX_PATH ${QT_PATH}/lib/cmake)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5WebEngineWidgets REQUIRED)
## Set the QT_LIBRARIES variable for Qt5, so it can be used below.
# set(QT_LIBRARIES Qt5::Core Qt5::Widgets Qt5::Network)
SET(QT_LIBRARIES ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5OpenGL_LIBRARIES}
        ${Qt5Network_LIBRARIES} ${Qt5Xml_LIBRARIES} ${Qt5Qml_LIBRARIES} ${Qt5WebEngineWidgets_LIBRARIES} )

INCLUDE_DIRECTORIES(${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS} ${Qt5OpenGL_INCLUDE_DIRS} ${Qt5Network_INCLUDE_DIRS}
        ${Qt5Xml_INCLUDE_DIRS} ${Qt5Qml_INCLUDE_DIRS} ${Qt5WebEngineWidgets_INCLUDE_DIRS})


#INCLUDE_DIRECTORIES(/usr/include/spdlog)
INCLUDE_DIRECTORIES(/usr/include/X11)
INCLUDE_DIRECTORIES(3rd/QCefView/include)
INCLUDE_DIRECTORIES(3rd/QCefView)


# SET(CEF_ROOT 3rd/cef/code_127.3.5/) #${CMAKE_CURRENT_SOURCE_DIR}/
# message(STATUS "CEF_ROOT=${CEF_ROOT}")
# INCLUDE_DIRECTORIES(${CEF_ROOT}/include)
# INCLUDE_DIRECTORIES(${CEF_ROOT})


INCLUDE_DIRECTORIES(src/UI)
INCLUDE_DIRECTORIES(src)



aux_source_directory(3rd/httpserver http_SRC)


#link_directories(/opt/Qt5.14.2/5.14.2/gcc_64/lib/)
link_directories(${QT_LIBRARIES})
link_directories(/usr/lib/x86_64-linux-gnu)

link_directories(/usr/local/lib/)
#link_directories(3rd/cef/lib)
link_directories(3rd/QCefView/build/output/Debug/bin/)

aux_source_directory(src/ SRC_SRC)
# aux_source_directory(src/UI SRC_SRC_UI)

add_executable(testQtCef
main.cpp
src/mainwindow.cpp
3rd/QCefView/example/QCefViewTest/CefViewWidget.cpp
3rd/QCefView/example/QCefViewTest/DownloadManager.cpp
)

target_link_libraries(testQtCef PRIVATE
"-Wl,--no-as-needed /home/amplesky/work/testQtCef/testQtCef/3rd/QCefView/lib/Debug/libQCefView.so"
"-Wl,--no-as-needed /home/amplesky/work/testQtCef/testQtCef/3rd/QCefView/lib/Debug/libcef.so"
#  -lusb -ludev -lhidapi-hidraw
# -lboost_system -lboost_thread -lboost_filesystem -lboost_iostreams -lboost_chrono
# -lMvCameraControl -luuid -lcurl -lstdc++fs
${QT_LIBRARIES}
-lX11

#-lcef
#libcef_dll_wrapper.a
#QCefView

#-LXNVCtrl
#-L/usr/lib/x86_64-linux-gnu/libXNVCtrl.so.0
-ldl
pthread

# ${OpenCV_LIBS} 
${Boost_LIBRARIES}


)
