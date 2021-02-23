/**
 * --
 * @file   jscrum_controller.hpp
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

#ifndef __JSCRUM__JSCRUM_CONTROLLER_HPP__
#define __JSCRUM__JSCRUM_CONTROLLER_HPP__

#include <boost/filesystem.hpp>

namespace jscrum {

class jscrum_controller {
 public:
   /**
    * Create a new jscrum controller and search for the current jdir.
    */
   jscrum_controller();

   /**
    * Create a new jdir at the calling directory.
    *
    * Returns the status of the operation.
    */
   bool init_jdir();

   /**
    * Create a new task and prompt the user to populate the given fields.
    *
    * Returns the status of the operation.
    */
   bool new_task();

   /**
    * Edit an existing task.
    *
    * Returns the status of the operation.
    */
   bool edit_task(int task_num);

   /**
    * Delete an existing task.
    *
    * Returns the status of the operation.
    */
   bool delete_task(int task_num);

   /**
    * Display the entire board to console.
    *
    * Returns the status of the operation.
    */
   bool display_board();

 private:
   /**
    * Find the current jdir in the calling or parent directories.
    *
    * Returns the status of the operation.
    */
   bool find_jdir();

   boost::filesystem::path _cdir; // the calling directory
   boost::filesystem::path _jdir; // the current jdir, empty if not found.
};

} // namespace jscrum

#endif //__JSCRUM__JSCRUM_CONTROLLER_HPP__
