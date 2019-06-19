//===--- Contiki.h - Contiki ToolChain Implementations ----------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_FORT_LIB_DRIVER_TOOLCHAINS_CONTIKI_H
#define LLVM_FORT_LIB_DRIVER_TOOLCHAINS_CONTIKI_H

#include "Gnu.h"
#include "fort/Driver/ToolChain.h"

namespace fort {
namespace driver {
namespace toolchains {

class LLVM_LIBRARY_VISIBILITY Contiki : public Generic_ELF {
public:
  Contiki(const Driver &D, const llvm::Triple &Triple,
          const llvm::opt::ArgList &Args);

  // No support for finding a C++ standard library yet.
  void addLibCxxIncludePaths(
      const llvm::opt::ArgList &DriverArgs,
      llvm::opt::ArgStringList &CC1Args) const override {}
  void addLibStdCxxIncludePaths(
      const llvm::opt::ArgList &DriverArgs,
      llvm::opt::ArgStringList &CC1Args) const override {}

  SanitizerMask getSupportedSanitizers() const override;
};

} // end namespace toolchains
} // end namespace driver
} // end namespace fort

#endif // LLVM_FORT_LIB_DRIVER_TOOLCHAINS_CONTIKI_H
