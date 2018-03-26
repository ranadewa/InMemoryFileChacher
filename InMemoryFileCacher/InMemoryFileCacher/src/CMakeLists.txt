cmake_minimum_required (VERSION 2.6)
project (cache)

# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

find_package (Threads)

add_executable(cache 
				Main.cpp
				ItemFileWrapper.cpp
				ItemFileReader.cpp
				ItemFileWriter.cpp
				FileHandler.cpp
				ExternalMemory.cpp
				DirtyCacheHandler.cpp
				LRUCache.cpp
			   )

target_link_libraries (cache ${CMAKE_THREAD_LIBS_INIT})


