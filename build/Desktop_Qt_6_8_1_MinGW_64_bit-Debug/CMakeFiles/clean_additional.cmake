# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Analizator_autogen"
  "CMakeFiles\\Analizator_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Analizator_autogen.dir\\ParseCache.txt"
  )
endif()
