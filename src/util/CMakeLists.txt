
add_library(jscrum_util
  fs.cpp
  string.cpp
)

target_link_libraries(jscrum_util PUBLIC
  ${Boost_LIBRARIES}
)
