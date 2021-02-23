/**
 * --
 * @file   jscrum_controller.cpp
 * @author Jonathon Temelkovski
 * @desc   Main interaction class for controlling operations of the jscrum.
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

#include <iostream>

#include "jscrum/jscrum_controller.hpp"

#include "jscrum/journal/journal.hpp"
#include "jscrum/util/json_creator.hpp"
#include "jscrum/util/fs.hpp"

namespace jscrum {

jscrum_controller::jscrum_controller()
  : _cdir(boost::filesystem::current_path()), _jdir() {

    // Locate the jscrum directory
    if (util::fs::find_jscrum_dir(_cdir, _jdir)
          == util::fs::error_code::success) {
      JS_LOG(debug, "jcontroller", ".jscrum: " << _jdir.string());
    } else {
      JS_LOG(debug, "jcontroller", ".jscrum not found.");
    }
}

bool jscrum_controller::init_jdir() {
  util::fs::error_code status = util::fs::make_jscrum_dir(_cdir);

  switch (status) {
    case util::fs::error_code::success:
      break;
    case util::fs::error_code::already_exists:
      JS_LOG(error, "jcontroller", "Story board already exists in this dir!");
      return false;
    case util::fs::error_code::system_error:
      JS_LOG(error, "jcontroller", "System error; cannot create jscrum dir!");
      return false;
    default:
      JS_LOG(error, "jcontroller", "Unkown error; cannot create jscrum dir!");
      return false;
  }
  _cdir /= ".jscrum/config"; // update current path

  // Write the empty board to the config file
  auto empty_board = get_empty_board();
  status = util::fs::write_json_to_file(_cdir, empty_board);
  if (status != util::fs::error_code::success) {
    JS_LOG(error, "jcontroller", "Failed to write the json to file.");
    return false;
  }

  // Open the config file for the user to edit the information about the
  // board
  status = util::fs::open_file_in_editor(_cdir);
  if (status != util::fs::error_code::success) {
    JS_LOG(error, "jcontroller", "Failed to open the file in the editor.");
    return false;
  }

  JS_LOG(success, "jcontroller", "New jscrum board successfully created.");
  return true;
}

bool jscrum_controller::new_task() {
  if (_jdir.empty()) {
    JS_LOG(error, "jcontroller", "No story board found, please initialize one.");
    return false;
  }

  nlohmann::json board;
  auto status = util::fs::read_json_from_file(_jdir / "config", board);

  unsigned long task_num = board["highest_task_num"];
  std::string task_file = "t" + std::to_string(++task_num);

  // Create an empty task and write it to it's file
  auto empty_task = get_empty_task();
  status = util::fs::write_json_to_file(_jdir / task_file, empty_task);
  if (status != util::fs::error_code::success) {
    JS_LOG(error, "jcontroller", "Failed to write the json to file.");
    return false;
  }

  // Open the file in the editor for the user to edit it's information
  status = util::fs::open_file_in_editor(_jdir / task_file);
  if (status != util::fs::error_code::success) {
    JS_LOG(error, "jcontroller", "Failed to open the file in the editor.");
    return false;
  }

  // Update the config file to reflect the new task in the task number count
  board["highest_task_num"] = task_num;
  status = util::fs::write_json_to_file(_jdir / "config", board);
  if (status != util::fs::error_code::success) {
    JS_LOG(error, "jcontroller", "Failed to write the json to file.");
    return false;
  }

  JS_LOG(success, "jscontroller", "Created task " << task_num);
  return true;
}

bool jscrum_controller::edit_task(int task_num) {
  if (_jdir.empty()) {
    JS_LOG(error, "jcontroller", "No story board found, please initialize one.");
    return false;
  } else if (task_num < 0) {
    JS_LOG(error, "jcontroller", "Task number cannot be negative!");
    return false;
  }

  nlohmann::json board;
  auto status = util::fs::read_json_from_file(_jdir / "config", board);
  std::string task_file = "t" + std::to_string(task_num);

  // Verify the task number is valid
  if (task_num > board["highest_task_num"]
        || !boost::filesystem::exists(_jdir/task_file)) {
    JS_LOG(error, "jcontroller", "Cannot edit a task that does not exist!");
    return false;
  }

  // Open the file in the editor for the user to edit it
  status = util::fs::open_file_in_editor(_jdir / task_file);
  if (status != util::fs::error_code::success) {
    JS_LOG(error, "jcontroller", "Failed to open file in the editor");
    return false;
  }

  JS_LOG(success, "jscontroller", "Edited task " << task_num);
  return true;
}

bool jscrum_controller::delete_task(int task_num) {
  if (_jdir.empty()) {
    JS_LOG(error, "jcontroller", "No story board found, please initialize one.");
    return false;
  } else if (task_num < 0) {
    JS_LOG(error, "jcontroller", "Task number cannot be negative!");
    return false;
  }

  nlohmann::json board;
  auto status = util::fs::read_json_from_file(_jdir / "config", board);
  std::string task_file = "t" + std::to_string(task_num);

  // Verify the task number is valid
  if (task_num > board["highest_task_num"]
        || !boost::filesystem::exists(_jdir/task_file)) {
    JS_LOG(error, "jcontroller", "Cannot delete a task that does not exist!");
    return false;
  }

  // Delete the file.
  status = util::fs::rm_file(_jdir / task_file);
  if (status != util::fs::error_code::success) {
    JS_LOG(error, "jcontroller", "Failed to delete the task");
    return false;
  }

  JS_LOG(success, "jscontroller", "Deleted task " << task_num);
  return true;
}


bool jscrum_controller::display_board() {
  // Todo
  return true;
}

} // namespace jscrum
