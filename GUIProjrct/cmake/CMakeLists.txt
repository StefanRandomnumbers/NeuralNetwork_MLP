cmake_minimum_required(VERSION 2.8.12)

STRING( REPLACE "/O2" "/Od" CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_CXX_FLAGS_RELWITHDEBINFO} )
 STRING( REPLACE "/O2" "/Od" CMAKE_C_FLAGS_RELWITHDEBINFO ${CMAKE_C_FLAGS_RELWITHDEBINFO} )

project(GUIProject)

find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Gui)
find_package(Qt5Concurrent)
find_package(Qt5Charts)

# Output directory settings
set(output_dir ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${output_dir})
set(CMAKE_AUTOMOC ON)

if (MSVC)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()




include_directories(
	../include
	${CMAKE_CURRENT_BINARY_DIR}
)



QT5_WRAP_UI( UI_H
	../gui/mainwindow.ui
  ../gui/NNSettingsDialog.ui
)

add_executable( GUIProject
	../src/main.cpp
	../include/errorchart.h
	../src/errorchart.cpp
	../include/Layer.h
	../src/Layer.cpp
	../src/mainwindow.cpp
	../include/mainwindow.h
	../src/NeuralNetwork.cpp
	../include/NeuralNetwork.h
	../src/sinworker.cpp
	../include/sinworker.h
	../include/Weight.h
	../src/Weight.cpp
	../include/xorworker.h
	../src/xorworker.cpp
  ../include/NNSettingsDialog.h
	../src/NNSettingsDialog.cpp
  ${UI_H}
)

target_link_libraries( GUIProject
	Qt5::Core
	Qt5::Widgets
	Qt5::Gui
  	Qt5::Concurrent
	Qt5::Charts
)