/**
 * @file journal/journal_impl.cpp
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

#include <iostream>
#include <unistd.h>

#include "jscrum/util/string.hpp"

// NOTE:
// We need to define this here to avoid the error message of a direct include
// of the journal implementation. This is the only exception. We undefine it
// immediately after.
#define __JSCRUM__JOURNAL__JOURNAL_HPP__
#include "jscrum/journal/journal_impl.hpp"
#undef __JSCRUM__JOURNAL__JOURNAL_HPP__

namespace jscrum {
namespace journal {

/**
 * Return the instance of the journal.
 */
journal &journal::instance() {
  static journal j;
  return j;
}

/**
 * Return the internal string stream of the journal.
 */
std::stringstream &journal::stream() {
  return _ss;
}

/**
 * Verify the severity and log the contents in the internal stream to
 * the console under stderr.
 *
 * Internal stream is cleared here.
 */
void journal::log(severity slvl, const std::string tag) {
  static const auto console = isatty(2);

  if (slvl >= _slvl) {
    if (console) { // logging to console
      std::cerr << "\e[38;5;" << severity_to_color(slvl) << "m";
    }
      
    std::cerr << "[" << jscrum::util::str::timestamp() << "] "
      << severity_to_str(slvl) << " [" << tag << "] "
      << _ss.str() << std::endl;

    if (console) { // logging to console
      std::cerr << "\e[0m";
    }
  }
  _ss.str("");
}

/**
 * Only severities greater or equal to the severity set here are logged.
 */
void journal::set_severity(severity slvl) {
  _slvl = slvl;
}

/**
 * Lock access to this class.
 */
void journal::lock() {
  _lock.lock();
}

/**
 * Unlock access to this class.
 */
void journal::unlock() {
  _lock.unlock();
}

journal::journal() : _slvl(info), _ss(), _lock()  {
}

/**
 * Helper to convert severity enum to a string.
 */
std::string journal::severity_to_str(severity slvl) {
  switch(slvl) {
    case trace:   return "[  trace]";
    case debug:   return "[  debug]";
    case info:    return "[   info]";
    case warn:    return "[   warn]";
    case error:   return "[  error]";
    case success: return "[success]";
    default:      return "[       ]";
  }
}

/**
 * Helper to convert severity enum to it's terminal color hex value.
 */
journal::colors journal::severity_to_color(severity slvl) {
  switch(slvl) {
    case trace:   return c_trace;
    case debug:   return c_debug;
    case info:    return c_info;
    case warn:    return c_warn;
    case error:   return c_error;
    case success: return c_success;
    default:      return c_default;
  }
}

} // namespace journal
} // namespace jscrum
