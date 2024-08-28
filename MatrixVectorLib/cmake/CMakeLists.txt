cmake_minimum_required(VERSION 2.6)

project( MatrixVectorLib )


SET( LIBRARY_OUTPUT_PATH ../lib )


ADD_DEFINITIONS( -DEXPORT_DLL_API )

IF( WIN32 )
 STRING( REPLACE "/O2" "/Od" CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_CXX_FLAGS_RELWITHDEBINFO} )
 STRING( REPLACE "/O2" "/Od" CMAKE_C_FLAGS_RELWITHDEBINFO ${CMAKE_C_FLAGS_RELWITHDEBINFO} )
 SET( CMAKE_C_FLAGS_RELWITHDEBINFO ${CMAKE_C_FLAGS_RELWITHDEBINFO} CACHE STRING "compiler-flags" FORCE )
 SET( CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_CXX_FLAGS_RELWITHDEBINFO} CACHE STRING "compiler-flags" FORCE )
ENDIF()


include_directories(
	../include
)


SET( INC
	../include/Weight.h
  ../include/Layer.h
)


SET( SRC
	../src/Weight.cpp
	../src/Layer.cpp
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