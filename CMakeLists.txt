cmake_minimum_required(VERSION 3.27.2)
set(CMAKE_CXX_STANDARD 20)


project(jsonparser)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_SOURCE_DIR})


file(GLOB jsonparserfiles
     "*.h" 
	 "*.cpp"
)

add_executable(${PROJECT_NAME} ${jsonparserfiles})

#using codecvt library which isssues deprecation warning
target_compile_definitions(${PROJECT_NAME} PRIVATE _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)