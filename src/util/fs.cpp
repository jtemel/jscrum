/**
 * --
 * @file   util/fs.cpp
 * @author Jonathon Temelkovski
 * @desc   Provides various utility functions for interacting with
 *         the fs.
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

#include <iostream> // REMOVE

#include <unistd.h>
#include <sys/wait.h>
#include <fstream>

#include "jscrum/util/fs.hpp"

namespace jscrum {
namespace util {
namespace fs {

error_code find_jscrum_dir(boost::filesystem::path cdir,
                     boost::filesystem::path &fdir) {
  while (cdir.string() != "/") {
    auto temp_path = cdir / ".jscrum";
    if (boost::filesystem::exists(temp_path)
        && boost::filesystem::is_directory(temp_path)) {
      fdir = temp_path;
      return error_code::success;
    }
    cdir = cdir.branch_path();
  }
  return error_code::not_found;
}

error_code make_jscrum_dir(const boost::filesystem::path cpath) {
  if (boost::filesystem::exists(cpath / ".jscrum")) {
    return error_code::already_exists;
  }
  return boost::filesystem::create_directory(cpath / ".jscrum") 
    ? error_code::success 
    : error_code::system_error;
}

error_code read_json_from_file(const boost::filesystem::path &fp,
                               nlohmann::json &jdata) {
  if (!boost::filesystem::exists(fp)) {
    return error_code::does_not_exist;
  } else if (!boost::filesystem::is_regular_file(fp)) {
    return error_code::not_a_file;
  }

  std::ifstream file(fp.string());
  if (!file.is_open()) {
    return error_code::io_error;
  }

  file >> jdata;
  file.close();
  return error_code::success;
}


error_code write_json_to_file(const boost::filesystem::path &fp,
                          const nlohmann::json &jdata) {
  std::ofstream file(fp.string());
  if (!file.is_open()) {
    return error_code::io_error;
  }

  file << jdata.dump(2);
  file.close();
  return error_code::success;
}
              
error_code copy_file(const boost::filesystem::path &src,
               const boost::filesystem::path &dest) {
  if (!boost::filesystem::is_regular_file(src)) {
    return error_code::not_a_file;
  }

  boost::filesystem::copy_file(
    src,
    dest,
    boost::filesystem::copy_option::overwrite_if_exists);
  return error_code::success;
}

error_code rm_file(const boost::filesystem::path &fp) {
  if (!boost::filesystem::exists(fp)) {
    return error_code::does_not_exist;
  } else if (!boost::filesystem::is_regular_file(fp)) {
    return error_code::not_a_file;
  }
  return boost::filesystem::remove(fp)
    ? error_code::success
    : error_code::system_error;
}

error_code rm_dir(const boost::filesystem::path &fp) {
  if (!boost::filesystem::exists(fp)) {
    return error_code::does_not_exist;
  } else if (!boost::filesystem::is_directory(fp)) {
    return error_code::not_a_directory;
  }
  return boost::filesystem::remove_all(fp)
    ? error_code::success
    : error_code::system_error;
}

error_code open_file_in_editor(const boost::filesystem::path &fp) {
  pid_t pid = fork();
  
  if (pid < 0) {
    return error_code::system_error;
  } else if (pid == 0) {
    execl("/bin/vim", "vim", fp.string().c_str(), NULL);
    exit(error_code::system_error);
  } else {
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
      auto exit_status = WEXITSTATUS(status);
      return exit_status == error_code::success
        ? error_code::success
        : error_code::system_error;
    }
    return error_code::system_error;
  }
}

} // namespace fs
} // namespace util
} // namespace jscrum
