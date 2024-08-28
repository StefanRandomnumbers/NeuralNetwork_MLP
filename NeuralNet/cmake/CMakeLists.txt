cmake_minimum_required(VERSION 2.6)

project( NeuralNetwork )

find_package(Qt5Core)
find_package(Qt5Widgets)

SET( LIBRARY_OUTPUT_PATH ../lib )



ADD_DEFINITIONS( -DEXPORT_DLL_API )

# Output directory settings
set(output_dir ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${output_dir})
set(CMAKE_AUTOMOC ON)

IF( WIN32 )
 STRING( REPLACE "/O2" "/Od" CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_CXX_FLAGS_RELWITHDEBINFO} )
 STRING( REPLACE "/O2" "/Od" CMAKE_C_FLAGS_RELWITHDEBINFO ${CMAKE_C_FLAGS_RELWITHDEBINFO} )
 SET( CMAKE_C_FLAGS_RELWITHDEBINFO ${CMAKE_C_FLAGS_RELWITHDEBINFO} CACHE STRING "compiler-flags" FORCE )
 SET( CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_CXX_FLAGS_RELWITHDEBINFO} CACHE STRING "compiler-flags" FORCE )
ENDIF()



include_directories(
	../include
	${CMAKE_CURRENT_BINARY_DIR}
)


SET( INC
	../include/NeuralNetwork.h
  ../include/Layer.h
  ../include/Weight.h
)


SET( SRC
	../src/NeuralNetwork.cpp
  ../src/Layer.cpp
  ../src/Weight.cpp
)


add_library( ${PROJECT_NAME} STATIC
	${SRC}
	${INC}
)


add_executable( ${PROJECT_NAME}_TEST
	${SRC}
	${INC}
	../src/main.cpp
)

target_link_libraries( ${PROJECT_NAME}
	Qt5::Core
	Qt5::Widgets
)
target_link_libraries( ${PROJECT_NAME}_TEST
	Qt5::Core
	Qt5::Widgets
)


set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${PROJECT_NAME}_TEST PROPERTIES LINKER_LANGUAGE CXX)