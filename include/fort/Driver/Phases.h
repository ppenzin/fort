//===--- Phases.h - Transformations on Driver Types -------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_FORT_DRIVER_PHASES_H
#define LLVM_FORT_DRIVER_PHASES_H

namespace fort {
namespace driver {
namespace phases {
  /// ID - Ordered values for successive stages in the
  /// compilation process which interact with user options.
  enum ID {
    Preprocess,
    Precompile,
    Compile,
    Backend,
    Assemble,
    Link
  };

  enum {
    MaxNumberOfPhases = Link + 1
  };

  const char *getPhaseName(ID Id);

} // end namespace phases
} // end namespace driver
} // end namespace fort

#endif
