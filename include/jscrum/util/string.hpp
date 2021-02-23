/**
 * @file util/string.hpp
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

#ifndef __JSCRUM__UTIL__STRING_HPP__
#define __JSCRUM__UTIL__STRING_HPP__

#include <cstdint>
#include <string>

namespace jscrum {
namespace util {
namespace str {

/**
 * Returns the timestamp of now in HH:MM:SS:mmmmmmm.
 */
std::string timestamp();

/**
 * Return the substring after the last '.' or "" if not found.
 */
std::string get_extension(const std::string &str);

/**
 * Return indentation count of the line.
 *
 * Indent is equal to " "*space_count.
 */
uint32_t count_indent(const std::string &str, const uint32_t space_count = 2U);

/**
 * Strip all leading spaces from the string.
 */
std::string &ltrim(std::string &str, const std::string token = " ");

/**
 * Strip all trailing spaces from the string.
 */
std::string &rtrim(std::string &str, const std::string token = " ");

/**
 * Strip all leading and trailing spaces from the string.
 */
std::string &trim(std::string &str, const std::string token = " ");

} // namespace str
} // namespace util
} // namespace jscrum

#endif //__JSCRUM__UTIL__STRING_HPP__
