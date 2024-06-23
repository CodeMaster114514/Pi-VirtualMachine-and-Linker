project(pi)

include_directories(
	${PROJECT_SOURCE_DIR}/inc
	${CMAKE_SOURCE_DIR}/inc
)

link_directories(
	${CMAKE_SOURCE_DIR}/lib/PMF
)

AUX_SOURCE_DIRECTORY(. DIR_SRCS)

set(LIBRARIES libPMF.so)

add_executable(pi ${DIR_SRCS})
target_link_libraries(pi ${LIBRARIES})
