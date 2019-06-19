//===--- Haiku.h - Haiku ToolChain Implementations --------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_FORT_LIB_DRIVER_TOOLCHAINS_HAIKU_H
#define LLVM_FORT_LIB_DRIVER_TOOLCHAINS_HAIKU_H

#include "Gnu.h"
#include "fort/Driver/Driver.h"
#include "fort/Driver/ToolChain.h"

namespace fort {
namespace driver {
namespace toolchains {

class LLVM_LIBRARY_VISIBILITY Haiku : public Generic_ELF {
public:
  Haiku(const Driver &D, const llvm::Triple &Triple,
          const llvm::opt::ArgList &Args);

  bool isPIEDefault() const override {
    return getTriple().getArch() == llvm::Triple::x86_64;
  }

  void addLibCxxIncludePaths(
      const llvm::opt::ArgList &DriverArgs,
      llvm::opt::ArgStringList &CC1Args) const override;
  void addLibStdCxxIncludePaths(
      const llvm::opt::ArgList &DriverArgs,
      llvm::opt::ArgStringList &CC1Args) const override;
};

} // end namespace toolchains
} // end namespace driver
} // end namespace fort

#endif // LLVM_FORT_LIB_DRIVER_TOOLCHAINS_HAIKU_H
