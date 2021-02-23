/**
 * --
 * @file   util/cmdline.hpp
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

#ifndef __JSCRUM__UTIL__CMDLINE_HPP__
#define __JSCRUM__UTIL__CMDLINE_HPP__

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

namespace jscrum {
namespace util {

class cmdline {
 public:
  cmdline();

  /**
   * Parse the commandline.
   *
   * Returns EXIT_SUCCESS on success, EXIT_FAILURE on error.
   */
  int run(int argc, char **argv);

  /**
   * Getters.
   */
  bool is_init();
  bool is_new();
  bool is_edit();
  bool is_rm();
  int task_num();

 private:
  /**
   * Enfore dependencies and conflicting options.
   */
  bool conflicting_options(const char* opt1, const char* opt2);

  bool option_dependency(const char* for_what, const char* required_option);
  
  /**
   * Initialize options for boost.
   */
  void init_opts();

  // Options: Only one can be true at a given time!
  bool _f_init;
  bool _f_new;
  bool _f_edit;
  bool _f_rm;

  int _task_num; // Verify this is non-negative!

  boost::program_options::options_description _desc;
  boost::program_options::variables_map _vm;
};

} // namespace util
} // namespace jscrum

#endif //__JSCRUM__UTIL__CMDLINE_HPP__
