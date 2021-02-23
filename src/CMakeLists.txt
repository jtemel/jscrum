
add_subdirectory(journal)
add_subdirectory(util)

add_executable(jscrum
  jscrum.cpp
  jscrum_controller.cpp
)

target_link_libraries(jscrum
  jscrum_util
  jscrum_journal
  ${Boost_LIBRARIES}
)

install(TARGETS jscrum DESTINATION ${INSTALL_DIR})
