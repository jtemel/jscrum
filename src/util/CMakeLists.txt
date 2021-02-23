
add_library(jscrum_util
  fs.cpp
)

target_link_libraries(jscrum_util PUBLIC
  ${Boost_LIBRARIES}
)
