/**
 * --
 * @file   util/fs.hpp
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

#ifndef __JSCRUM__UTIL__FS_HPP__
#define __JSCRUM__UTIL__FS_HPP__

#include <boost/filesystem.hpp>

#include "jscrum/third-party/json.hpp"

namespace jscrum {
namespace util {
namespace fs {

/**
 * The types of status codes that we can get from a given filesystem operation.
 */
enum error_code {
  success = 0,
  not_found,
  already_exists,
  does_not_exist,
  not_a_file,
  not_a_directory,
  io_error,
  
  system_error = 255
};

/**
 * Find the jscrum directory from the calling location by searching it's
 * parents.
 *
 * Populates jdir with the path found, empty if '/home/' is hit.
 */
error_code find_jscrum_dir(boost::filesystem::path cdir,
                           boost::filesystem::path &jdir);

/**
 * Create a jscrum directory at the given filesystem path.
 */
error_code make_jscrum_dir(const boost::filesystem::path cpath);

/**
 * Read a json file into a nlohmann::json object to be manipulated.
 */
error_code read_json_from_file(const boost::filesystem::path &fp,
                               nlohmann::json &jdata); 

/**
 * Write a nlohmann::json object to a file.
 */
error_code write_json_to_file(const boost::filesystem::path &fp,
                                const nlohmann::json &jdata); 

/**
 * Copy a file from the specificed source location to the specified destination
 * location.
 */
error_code copy_file(const boost::filesystem::path &src,
                     const boost::filesystem::path &dest);

/**
 * Delete a file.
 */
error_code rm_file(const boost::filesystem::path &fp);

/**
 * Delete a directory.
 */
error_code rm_dir(const boost::filesystem::path &fp);
              
/**
 * Open a file in the default editor.
 */
error_code open_file_in_editor(const boost::filesystem::path &fp);

} // namespace fs
} // namespace util
} // namespace jscrum

#endif //__JSCRUM__UTIL__FS_HPP__
