//===--- Util.h - Common Driver Utilities -----------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_FORT_DRIVER_UTIL_H
#define LLVM_FORT_DRIVER_UTIL_H

#include "fort/Basic/LLVM.h"
#include "llvm/ADT/DenseMap.h"

namespace fort {
class DiagnosticsEngine;

namespace driver {
  class Action;
  class JobAction;

  /// ArgStringMap - Type used to map a JobAction to its result file.
  typedef llvm::DenseMap<const JobAction*, const char*> ArgStringMap;

  /// ActionList - Type used for lists of actions.
  typedef SmallVector<Action*, 3> ActionList;

} // end namespace driver
} // end namespace fort

#endif
