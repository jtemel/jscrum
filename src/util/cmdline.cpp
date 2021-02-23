/**
 * --
 * @file   util/cmdline.cpp
 * @author Jonathon Temelkovski
 * @desc   Provides functionality to parse and execute cmdline options.
 * -- 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * --
 */

#include "jscrum/util/cmdline.hpp"
#include "jscrum/journal/journal.hpp"

namespace jscrum {
namespace util {

cmdline::cmdline()
  : _f_init(false),
    _f_new(false),
    _f_edit(false),
    _f_rm(false),
    _task_num(-1) {

  init_opts();
}

int cmdline::run(int argc, char **argv) {
  using namespace boost::program_options;

  store(parse_command_line(argc, argv, _desc), _vm);

  if (_vm.count("help")) {
    JS_LOG(info, "cmdline", _desc);
    return EXIT_SUCCESS;
  }

  bool valid = true;
  // Enforce restrictions and dependencies
  valid = valid && conflicting_options("init", "new");
  valid = valid && conflicting_options("init", "edit");
  valid = valid && conflicting_options("init", "rm");
  valid = valid && conflicting_options("new", "edit");
  valid = valid && conflicting_options("new", "rm");
  valid = valid && conflicting_options("edit", "rm");

  valid = valid && option_dependency("edit", "task");
  valid = valid && option_dependency("rm", "task");

  if (!valid) {
    return EXIT_FAILURE;
  }

  // Gather the parsed information
  _f_init = _vm["init"].as<bool>();
  _f_new  = _vm["new"].as<bool>();
  _f_edit = _vm["edit"].as<bool>();
  _f_rm   = _vm["rm"].as<bool>();

  if (_vm.count("task")) {
    _task_num  = _vm["task"].as<int>();
  } // we only update this if it exists!

  return EXIT_SUCCESS;
}

bool cmdline::is_init() {
  return _f_init;
}

bool cmdline::is_new() {
  return _f_new;
}

bool cmdline::is_edit() {
  return _f_edit;
}

bool cmdline::is_rm() {
  return _f_rm;
}

int cmdline::task_num() {
  return _task_num;
}

bool cmdline::conflicting_options(const char* opt1, const char* opt2)
{
    if (_vm.count(opt1) && !_vm[opt1].defaulted() 
          && _vm.count(opt2) && !_vm[opt2].defaulted()) {
        JS_LOG(error, "cmdline", "Conflicting options '" 
                          << opt1 << "' and '" << opt2 << "'.");
        return false;
    }
    return true;
}

bool cmdline::option_dependency(const char* for_what,
                                const char* required_option)
{
    if (_vm.count(for_what) && !_vm[for_what].defaulted()) {
      if (_vm.count(required_option) == 0 || _vm[required_option].defaulted()) {
        JS_LOG(error, "cmdline", "Option '" 
                      << for_what << "' requires option '"
                      << required_option << "'.");
        return false;
      }
    }
    return true;
}

void cmdline::init_opts() {
  using namespace boost::program_options;

  _desc.add_options()
    ("help,h", "print help message")
    ("init", bool_switch(&_f_init), "initialize a new story board here.")
    ("task,t",  value(&_task_num), "task number to manipulate")
    ("new",  bool_switch(&_f_new), "add a new task")
    ("edit",  bool_switch(&_f_edit), "edit a new task")
    ("rm",  bool_switch(&_f_rm), "delete a new task");
}

} // namespace util
} // namespace jscrum
