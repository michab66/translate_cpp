cmake_minimum_required(VERSION 3.5.0 FATAL_ERROR)

set(headers
    ConvertNumberToWord.h
)

set(implementation
    ConvertNumberToWord.cpp
	Translate.cpp
)

add_executable(translate_cpp STATIC
    ${implementation}
    ${headers}
)

target_include_directories(translate_cpp INTERFACE ..)

install(TARGETS
  translate_cpp
  DESTINATION lib)
