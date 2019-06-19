//===--- PPC.h - PPC-specific Tool Helpers ----------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_FORT_LIB_DRIVER_TOOLCHAINS_ARCH_PPC_H
#define LLVM_FORT_LIB_DRIVER_TOOLCHAINS_ARCH_PPC_H

#include "fort/Driver/Driver.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Option/Option.h"
#include <string>
#include <vector>

namespace fort {
namespace driver {
namespace tools {
namespace ppc {

bool hasPPCAbiArg(const llvm::opt::ArgList &Args, const char *Value);

enum class FloatABI {
  Invalid,
  Soft,
  Hard,
};

enum class ReadGOTPtrMode {
  Bss,
  SecurePlt,
};

FloatABI getPPCFloatABI(const Driver &D, const llvm::opt::ArgList &Args);

std::string getPPCTargetCPU(const llvm::opt::ArgList &Args);
const char *getPPCAsmModeForCPU(StringRef Name);
ReadGOTPtrMode getPPCReadGOTPtrMode(const Driver &D, const llvm::Triple &Triple,
                                    const llvm::opt::ArgList &Args);

void getPPCTargetFeatures(const Driver &D, const llvm::Triple &Triple,
                          const llvm::opt::ArgList &Args,
                          std::vector<llvm::StringRef> &Features);

} // end namespace ppc
} // end namespace target
} // end namespace driver
} // end namespace fort

#endif // LLVM_FORT_LIB_DRIVER_TOOLCHAINS_ARCH_PPC_H
