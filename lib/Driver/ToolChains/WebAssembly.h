//===--- WebAssembly.h - WebAssembly ToolChain Implementations --*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_FORT_LIB_DRIVER_TOOLCHAINS_WEBASSEMBLY_H
#define LLVM_FORT_LIB_DRIVER_TOOLCHAINS_WEBASSEMBLY_H

#include "Gnu.h"
#include "fort/Driver/Tool.h"
#include "fort/Driver/ToolChain.h"

namespace fort {
namespace driver {
namespace tools {
namespace wasm {

class LLVM_LIBRARY_VISIBILITY Linker : public GnuTool {
public:
  explicit Linker(const ToolChain &TC);
  bool isLinkJob() const override;
  bool hasIntegratedCPP() const override;
  void ConstructJob(Compilation &C, const JobAction &JA,
                    const InputInfo &Output, const InputInfoList &Inputs,
                    const llvm::opt::ArgList &TCArgs,
                    const char *LinkingOutput) const override;
};

} // end namespace wasm
} // end namespace tools

namespace toolchains {

class LLVM_LIBRARY_VISIBILITY WebAssembly final : public ToolChain {
public:
  WebAssembly(const Driver &D, const llvm::Triple &Triple,
              const llvm::opt::ArgList &Args);

private:
  bool IsMathErrnoDefault() const override;
  bool IsObjCNonFragileABIDefault() const override;
  bool UseObjCMixedDispatch() const override;
  bool isPICDefault() const override;
  bool isPIEDefault() const override;
  bool isPICDefaultForced() const override;
  bool IsIntegratedAssemblerDefault() const override;
  bool hasBlocksRuntime() const override;
  bool SupportsProfiling() const override;
  bool HasNativeLLVMSupport() const override;
  void
  addFortTargetOptions(const llvm::opt::ArgList &DriverArgs,
                        llvm::opt::ArgStringList &CC1Args,
                        Action::OffloadKind DeviceOffloadKind) const override;
  RuntimeLibType GetDefaultRuntimeLibType() const override;
  CXXStdlibType GetCXXStdlibType(const llvm::opt::ArgList &Args) const override;
  void
  AddFortSystemIncludeArgs(const llvm::opt::ArgList &DriverArgs,
                            llvm::opt::ArgStringList &CC1Args) const override;
  void AddFortCXXStdlibIncludeArgs(
      const llvm::opt::ArgList &DriverArgs,
      llvm::opt::ArgStringList &CC1Args) const override;
  void AddCXXStdlibLibArgs(const llvm::opt::ArgList &Args,
                           llvm::opt::ArgStringList &CmdArgs) const override;
  std::string getThreadModel() const override;

  const char *getDefaultLinker() const override { return "wasm-ld"; }

  Tool *buildLinker() const override;
};

} // end namespace toolchains
} // end namespace driver
} // end namespace fort

#endif // LLVM_FORT_LIB_DRIVER_TOOLCHAINS_WEBASSEMBLY_H
