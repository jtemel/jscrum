
add_library(jscrum_journal
  journal_impl.cpp
)

target_link_libraries(jscrum_journal PUBLIC
  jscrum_util
)
