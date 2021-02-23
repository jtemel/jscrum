/**
 * --
 * @file   util/time.hpp
 * @author Jonathon Temelkovski
 * @desc   Provides util functions for getting and setting time.
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

#ifndef __JSCRUM__UTIL__TIME_HPP__
#define __JSCRUM__UTIL__TIME_HPP__

#include <chrono>

namespace jscrum {
namespace util {
namespace time {

/**
 * Return the current time in milliseconds since epoch.
 */
inline unsigned long now_ms() {
  return std::chrono::system_clock::now().time_since_epoch() / 
    std::chrono::milliseconds(1);
}

} // namespace time
} // namespace util
} // namespace jscrum

#endif //__JSCRUM__UTIL__TIME_HPP__
