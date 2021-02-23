/**
 * @file journal/journal.hpp
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
#define __JSCRUM__JOURNAL__JOURNAL_HPP__

#include "jscrum/journal/journal_impl.hpp"

namespace jscrum {

#define JS_SEVERITY(lvl) \
  jscrum::journal::instance().lock(); \
  jscrum::journal::instance().set_severity(jscrum::journal::severity::lvl); \
  jscrum::journal::instance().unlock();

#define JS_LOG(lvl, tag, str) \
  do { \
    jscrum::journal::instance().lock(); \
    jscrum::journal::instance().stream() << str; \
    jscrum::journal::instance().log(jscrum::journal::severity::lvl, tag); \
    jscrum::journal::instance().unlock(); \
  } while (false)

} // namesapce jscrum

#endif //__JSCRUM__JOURNAL__JOURNAL_HPP__
