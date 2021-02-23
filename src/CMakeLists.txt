
add_subdirectory(util)

add_executable(jscrum
  jscrum.cpp
  jscrum_controller.cpp
)

target_link_libraries(jscrum
  jscrum_util
  ${Boost_LIBRARIES}
)

install(TARGETS jscrum DESTINATION ${INSTALL_DIR})
