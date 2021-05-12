cmake_minimum_required(VERSION 3.5.0 FATAL_ERROR)

set(headers
)

set(implementation
	Translate.cpp
)

add_executable(translate_cpp
    ${implementation}
    ${headers}
)

install(TARGETS
  translate_cpp
  DESTINATION lib)
