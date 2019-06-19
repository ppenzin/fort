//===--- AArch64.h - AArch64-specific (not ARM) Tool Helpers ----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_FORT_LIB_DRIVER_TOOLCHAINS_ARCH_AARCH64_H
#define LLVM_FORT_LIB_DRIVER_TOOLCHAINS_ARCH_AARCH64_H

#include "fort/Driver/Driver.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Option/Option.h"
#include <string>
#include <vector>

namespace fort {
namespace driver {
namespace tools {
namespace aarch64 {

void getAArch64TargetFeatures(const Driver &D, const llvm::Triple &Triple,
                              const llvm::opt::ArgList &Args,
                              std::vector<llvm::StringRef> &Features);

std::string getAArch64TargetCPU(const llvm::opt::ArgList &Args,
                                const llvm::Triple &Triple, llvm::opt::Arg *&A);

} // end namespace aarch64
} // end namespace target
} // end namespace driver
} // end namespace fort

#endif // LLVM_FORT_LIB_DRIVER_TOOLCHAINS_ARCH_AARCH64_H
