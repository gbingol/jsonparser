cmake_minimum_required(VERSION 3.27.2)
set(CMAKE_CXX_STANDARD 20)


project(jsonparser)

file(GLOB jsonparserfiles
     "*.h" 
	 "*.cpp"
)

add_executable(${PROJECT_NAME} ${jsonparserfiles})