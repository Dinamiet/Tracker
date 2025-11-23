cmake_minimum_required(VERSION 4.1)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(
	SIM868
	GIT_REPOSITORY
		git@github.com:Dinamiet/SIM868.git
	GIT_TAG
		main
	SOURCE_DIR
		${CMAKE_SOURCE_DIR}/lib/SIM868
)

FetchContent_Declare(
	Observer
	GIT_REPOSITORY
		git@github.com:Dinamiet/Observer.git
	GIT_TAG
		main
	SOURCE_DIR
		${CMAKE_SOURCE_DIR}/lib/Observer
)

FetchContent_Declare(
	Cryptography
	GIT_REPOSITORY
		git@github.com:Dinamiet/Cryptography.git
	GIT_TAG
		main
	SOURCE_DIR
		${CMAKE_SOURCE_DIR}/lib/Cryptography
)

FetchContent_MakeAvailable(
	SIM868
	Observer
	Cryptography
)
