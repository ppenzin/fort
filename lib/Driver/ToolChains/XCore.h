//===--- XCore.h - XCore ToolChain Implementations --------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_FORT_LIB_DRIVER_TOOLCHAINS_XCORE_H
#define LLVM_FORT_LIB_DRIVER_TOOLCHAINS_XCORE_H

#include "fort/Driver/Tool.h"
#include "fort/Driver/ToolChain.h"

namespace fort {
namespace driver {
namespace tools {

namespace XCore {
// For XCore, we do not need to instantiate tools for PreProcess, PreCompile and
// Compile.
// We simply use "fort -cc1" for those actions.
class LLVM_LIBRARY_VISIBILITY Assembler : public Tool {
public:
  Assembler(const ToolChain &TC) : Tool("XCore::Assembler", "XCore-as", TC) {}

  bool hasIntegratedCPP() const override { return false; }
  void ConstructJob(Compilation &C, const JobAction &JA,
                    const InputInfo &Output, const InputInfoList &Inputs,
                    const llvm::opt::ArgList &TCArgs,
                    const char *LinkingOutput) const override;
};

class LLVM_LIBRARY_VISIBILITY Linker : public Tool {
public:
  Linker(const ToolChain &TC) : Tool("XCore::Linker", "XCore-ld", TC) {}

  bool hasIntegratedCPP() const override { return false; }
  bool isLinkJob() const override { return true; }
  void ConstructJob(Compilation &C, const JobAction &JA,
                    const InputInfo &Output, const InputInfoList &Inputs,
                    const llvm::opt::ArgList &TCArgs,
                    const char *LinkingOutput) const override;
};
} // end namespace XCore.
} // end namespace tools

namespace toolchains {

class LLVM_LIBRARY_VISIBILITY XCoreToolChain : public ToolChain {
public:
  XCoreToolChain(const Driver &D, const llvm::Triple &Triple,
                 const llvm::opt::ArgList &Args);

protected:
  Tool *buildAssembler() const override;
  Tool *buildLinker() const override;

public:
  bool isPICDefault() const override;
  bool isPIEDefault() const override;
  bool isPICDefaultForced() const override;
  bool SupportsProfiling() const override;
  bool hasBlocksRuntime() const override;
  void
  AddFortSystemIncludeArgs(const llvm::opt::ArgList &DriverArgs,
                            llvm::opt::ArgStringList &CC1Args) const override;
  void addFortTargetOptions(const llvm::opt::ArgList &DriverArgs,
                             llvm::opt::ArgStringList &CC1Args,
                             Action::OffloadKind DeviceOffloadKind) const override;
  void AddFortCXXStdlibIncludeArgs(
      const llvm::opt::ArgList &DriverArgs,
      llvm::opt::ArgStringList &CC1Args) const override;
  void AddCXXStdlibLibArgs(const llvm::opt::ArgList &Args,
                           llvm::opt::ArgStringList &CmdArgs) const override;
};

} // end namespace toolchains
} // end namespace driver
} // end namespace fort

#endif // LLVM_FORT_LIB_DRIVER_TOOLCHAINS_XCORE_H
