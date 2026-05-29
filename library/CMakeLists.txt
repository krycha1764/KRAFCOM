cmake_minimum_required(VERSION 3.23)

project(KRAFCOM)

add_subdirectory(tiny-AES-c)

add_library(KRAFCOM STATIC)

target_link_libraries(KRAFCOM
	PRIVATE
		tiny-aes
)

target_sources(KRAFCOM
	PRIVATE
		KRAFCOM.c
		crc32.c
		crc32.h
	PUBLIC
	FILE_SET HEADERS
	BASE_DIRS
		.
	FILES
		KRAFCOM.h
		KRAFCOM_USER.h
)
