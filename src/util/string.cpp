/**
 * @file util/string.cpp
 *
 * @author Jonathon Temelkovski
 **
 * [2020] NiceNote 
 * All Rights Reserved.
 * 
 * NOTICE:  All information contained herein is, and remains
 * the property of NiceNote and its suppliers, if any.
 * The intellectual and technical concepts contained
 * herein are proprietary to NiceNote and its suppliers and may be
 * covered by U.S. and Foreign Patents, patents in process, 
 * and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from NiceNote.
 */

#include <chrono>
#include <iomanip>
#include <iostream>

#include "jscrum/util/string.hpp"

namespace jscrum {
namespace util {
namespace str {

/**
 * Returns the timestamp of now in HH:MM:SS:mmmmmmm.
 */
std::string timestamp() {
  const auto now = std::chrono::system_clock::now();
  const auto now_t = std::chrono::system_clock::to_time_t(now);
  const auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
      now.time_since_epoch()) % 10000000; // keep ms at reasonable length
  std::stringstream ss;
  ss << std::put_time(std::localtime(&now_t), "%T")
     << ':' << std::setfill('0') << std::setw(3) << now_ms.count();
  return ss.str();
}

/**
 * Return the substring after the last '.' or "" if not found.
 */
std::string get_extension(const std::string &str) {
  auto index = str.find_last_of(".");
  return index == std::string::npos ? "" : str.substr(index + 1);
}

/**
 * Return indentation count of the line.
 *
 * Indent is equal to " "*space_count.
 */
uint32_t count_indent(const std::string &str, const uint32_t space_count) {
  const auto count = str.find_first_not_of(" ");
  return count == std::string::npos ? 0U : (count - (count % space_count)) / space_count;
}

/**
 * Strip all leading spaces from the string.
 */
std::string &ltrim(std::string &str, const std::string token) {
  str.erase(0, str.find_first_not_of(token));
  return str;
}

/**
 * Strip all trailing spaces from the string.
 */
std::string &rtrim(std::string &str, const std::string token) {
  str.erase(str.find_last_not_of(token) + 1);
  return str;
}

/**
 * Strip all leading and trailing spaces from the string.
 */
std::string &trim(std::string &str, const std::string token) { 
  return ltrim(rtrim(str, " "), " ");
}

} // namespace str
} // namespace util
} // namespace jscrum
