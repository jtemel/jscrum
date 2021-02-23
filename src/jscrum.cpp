
#include "jscrum/journal/journal.hpp"
#include "jscrum/jscrum_controller.hpp"
#include "jscrum/util/cmdline.hpp"

int main(int argc, char *argv[]) {
  JS_SEVERITY(trace);

  jscrum::util::cmdline cmd;

  if (cmd.run(argc, argv) == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }

  jscrum::jscrum_controller jc;
  if (cmd.is_init()) {
    jc.init_jdir();
  } else if (cmd.is_new()) {
    jc.new_task();
  } else if (cmd.is_edit()) {
    jc.edit_task(cmd.task_num());
  } else if (cmd.is_rm()) {
    jc.delete_task(cmd.task_num());
  } else {
    jc.display_board();
  }
  
  return EXIT_SUCCESS;
}
