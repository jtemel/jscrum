/**
 * @file journal/journal_impl.hpp
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

#ifndef __JSCRUM__JOURNAL__JOURNAL_HPP__
#error "Do not include this file directly, instead include jscrum/journal/journal.hpp"
#endif

#ifndef __JSCRUM__JOURNAL__JOURNAL_IMPL_HPP__
#define __JSCRUM__JOURNAL__JOURNAL_IMPL_HPP__

#include <sstream>
#include <mutex>

namespace jscrum {

/**
 * This singleton class handles logging to the console.
 *
 * TODO: Log to file aswell.
 */
class journal {
 public:
  /**
   * The possible severities to log to.
   */
  enum severity {
    trace = 0,
    debug,
    info,
    warn,
    error,
    success,

    num_of_severities = 255
  };

  /**
   * Colors for the severities in hex.
   */
  enum colors {
    c_default = 0,
    c_trace = 240,
    c_debug = 247,
    c_info = 15,
    c_warn = 226,
    c_error = 196,
    c_success = 46
  };

  /**
   * Return the instance of the journal.
   */
  static journal &instance();

  /**
   * Return the internal string stream of the journal.
   */
  std::stringstream &stream();

  /**
   * Verify the severity and log the contents in the internal stream to
   * the console under stderr.
   *
   * Internal stream is cleared here.
   */
  void log(severity slvl, const std::string tag);

  /**
   * Only severities greater or equal to the severity set here are logged.
   */
  void set_severity(severity slvl);

  /**
   * Lock access to this class.
   */
  void lock();

  /**
   * Unlock access to this class.
   */
  void unlock();
 
 private:
  journal();

  /**
   * Helper to convert severity enum to a string.
   */
  std::string severity_to_str(severity slvl);

  /**
   * Helper to convert severity enum to it's terminal color hex value.
   */
  colors severity_to_color(severity slvl);
 
  severity _slvl; // default is info
  std::stringstream _ss;
  std::mutex _lock;
};

} // namespace jscrum

#endif //__JSCRUM__JOURNAL__JOURNAL_IMPL_HPP__
