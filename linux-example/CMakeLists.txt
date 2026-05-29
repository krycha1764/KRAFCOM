cmake_minimum_required(VERSION 3.23)

project(KRAFCOM-linux-example)

add_executable(linux-example)
target_sources(linux-example
	PRIVATE
		main.c
)

target_link_libraries(linux-example
	PRIVATE
		KRAFCOM
)
