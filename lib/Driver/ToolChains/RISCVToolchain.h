//===--- RISCVToolchain.h - RISCV ToolChain Implementations -----*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_FORT_LIB_DRIVER_TOOLCHAINS_RISCVTOOLCHAIN_H
#define LLVM_FORT_LIB_DRIVER_TOOLCHAINS_RISCVTOOLCHAIN_H

#include "Gnu.h"
#include "fort/Driver/ToolChain.h"

namespace fort {
namespace driver {
namespace toolchains {

class LLVM_LIBRARY_VISIBILITY RISCVToolChain : public Generic_ELF {
public:
  RISCVToolChain(const Driver &D, const llvm::Triple &Triple,
                 const llvm::opt::ArgList &Args);

  bool IsIntegratedAssemblerDefault() const override { return true; }
  void addFortTargetOptions(const llvm::opt::ArgList &DriverArgs,
                             llvm::opt::ArgStringList &CC1Args,
                             Action::OffloadKind) const override;
  void
  AddFortSystemIncludeArgs(const llvm::opt::ArgList &DriverArgs,
                            llvm::opt::ArgStringList &CC1Args) const override;
  void
  addLibStdCxxIncludePaths(const llvm::opt::ArgList &DriverArgs,
                           llvm::opt::ArgStringList &CC1Args) const override;

protected:
  Tool *buildLinker() const override;

private:
  std::string computeSysRoot() const;
};

} // end namespace toolchains

namespace tools {
namespace RISCV {
class LLVM_LIBRARY_VISIBILITY Linker : public GnuTool {
public:
  Linker(const ToolChain &TC) : GnuTool("RISCV::Linker", "ld", TC) {}
  bool hasIntegratedCPP() const override { return false; }
  bool isLinkJob() const override { return true; }
  void ConstructJob(Compilation &C, const JobAction &JA,
                    const InputInfo &Output, const InputInfoList &Inputs,
                    const llvm::opt::ArgList &TCArgs,
                    const char *LinkingOutput) const override;
};
} // end namespace RISCV
} // end namespace tools

} // end namespace driver
} // end namespace fort

#endif // LLVM_FORT_LIB_DRIVER_TOOLCHAINS_RISCVTOOLCHAIN_H
