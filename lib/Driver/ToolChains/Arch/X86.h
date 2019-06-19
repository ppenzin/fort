//===--- X86.h - X86-specific Tool Helpers ----------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_FORT_LIB_DRIVER_TOOLCHAINS_ARCH_X86_H
#define LLVM_FORT_LIB_DRIVER_TOOLCHAINS_ARCH_X86_H

#include "fort/Driver/Driver.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/Triple.h"
#include "llvm/Option/Option.h"
#include <string>
#include <vector>

namespace fort {
namespace driver {
namespace tools {
namespace x86 {

const char *getX86TargetCPU(const llvm::opt::ArgList &Args,
                            const llvm::Triple &Triple);

void getX86TargetFeatures(const Driver &D, const llvm::Triple &Triple,
                          const llvm::opt::ArgList &Args,
                          std::vector<llvm::StringRef> &Features);

} // end namespace x86
} // end namespace target
} // end namespace driver
} // end namespace fort

#endif // LLVM_FORT_LIB_DRIVER_TOOLCHAINS_ARCH_X86_H
