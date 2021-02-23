/**
 * --
 * @file   json_creator.hpp
 * @author Jonathon Temelkovski
 * @desc   Provides empty json templates for baords, sprints and tasks.
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

#ifndef __JSCRUM__JSON_CREATOR_HPP__
#define __JSCRUM__JSON_CREATOR_HPP__

#include "jscrum/util/time.hpp"
#include "jscrum/third-party/json.hpp"

namespace jscrum {

/**
 * Create an empty story board (with only the created time populated).
 */
inline nlohmann::json get_empty_board() {
  nholmann::json json;

  json["name"] = "";
  json["desc"] = "";
  json["created_time"] = util::time::now_ms();
  json["total_tasks"] = 0;
  json["highest_task_num"] = 0;

  return json;
}

} // namespace jscrum

#endif //__JSCRUM__JSON_CREATOR_HPP__
