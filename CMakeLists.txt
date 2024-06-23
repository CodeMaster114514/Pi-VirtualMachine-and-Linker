project(Pi-VirtualMachine-And-Linker)

set(CMAKE_BUILD_TYPE DEBUG)

set(CMAKE_CXX_FLAG_DEBUG -g)

include_directories(
	${PROJECT_SOURCE_DIR}/inc
	${PROJECT_SOURCE_DIR}/VirtualMachine/inc
)

add_subdirectory(
	lib
)

add_subdirectory(
	VirtualMachine
)
