//===--- RISCV.h - RISCV-specific Tool Helpers ------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_FORT_LIB_DRIVER_TOOLCHAINS_ARCH_RISCV_H
#define LLVM_FORT_LIB_DRIVER_TOOLCHAINS_ARCH_RISCV_H

#include "fort/Driver/Driver.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Option/Option.h"
#include <string>
#include <vector>

namespace fort {
namespace driver {
namespace tools {
namespace riscv {
void getRISCVTargetFeatures(const Driver &D, const llvm::opt::ArgList &Args,
                            std::vector<llvm::StringRef> &Features);
StringRef getRISCVABI(const llvm::opt::ArgList &Args,
                      const llvm::Triple &Triple);
} // end namespace riscv
} // namespace tools
} // end namespace driver
} // end namespace fort

#endif // LLVM_FORT_LIB_DRIVER_TOOLCHAINS_ARCH_RISCV_H
