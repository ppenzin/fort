//===--- Fort.h - Fort Tool and ToolChain Implementations ====-*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_FORT_LIB_DRIVER_TOOLCHAINS_Fort_H
#define LLVM_FORT_LIB_DRIVER_TOOLCHAINS_Fort_H

#include "MSVC.h"
#include "fort/Basic/DebugInfoOptions.h"
#include "fort/Driver/Driver.h"
#include "fort/Driver/Tool.h"
#include "fort/Driver/Types.h"
#include "llvm/ADT/Triple.h"
#include "llvm/Option/Option.h"
#include "llvm/Support/raw_ostream.h"

namespace fort {
class ObjCRuntime;
namespace driver {

namespace tools {

/// Fort compiler tool.
class LLVM_LIBRARY_VISIBILITY Fort : public Tool {
public:
  static const char *getBaseInputName(const llvm::opt::ArgList &Args,
                                      const InputInfo &Input);
  static const char *getBaseInputStem(const llvm::opt::ArgList &Args,
                                      const InputInfoList &Inputs);
  static const char *getDependencyFileName(const llvm::opt::ArgList &Args,
                                           const InputInfoList &Inputs);

private:
  void AddPreprocessingOptions(Compilation &C, const JobAction &JA,
                               const Driver &D, const llvm::opt::ArgList &Args,
                               llvm::opt::ArgStringList &CmdArgs,
                               const InputInfo &Output,
                               const InputInfoList &Inputs) const;

  void RenderTargetOptions(const llvm::Triple &EffectiveTriple,
                           const llvm::opt::ArgList &Args, bool KernelOrKext,
                           llvm::opt::ArgStringList &CmdArgs) const;

  void AddAArch64TargetArgs(const llvm::opt::ArgList &Args,
                            llvm::opt::ArgStringList &CmdArgs) const;
  void AddARMTargetArgs(const llvm::Triple &Triple,
                        const llvm::opt::ArgList &Args,
                        llvm::opt::ArgStringList &CmdArgs,
                        bool KernelOrKext) const;
  void AddARM64TargetArgs(const llvm::opt::ArgList &Args,
                          llvm::opt::ArgStringList &CmdArgs) const;
  void AddMIPSTargetArgs(const llvm::opt::ArgList &Args,
                         llvm::opt::ArgStringList &CmdArgs) const;
  void AddPPCTargetArgs(const llvm::opt::ArgList &Args,
                        llvm::opt::ArgStringList &CmdArgs) const;
  void AddR600TargetArgs(const llvm::opt::ArgList &Args,
                         llvm::opt::ArgStringList &CmdArgs) const;
  void AddRISCVTargetArgs(const llvm::opt::ArgList &Args,
                          llvm::opt::ArgStringList &CmdArgs) const;
  void AddSparcTargetArgs(const llvm::opt::ArgList &Args,
                          llvm::opt::ArgStringList &CmdArgs) const;
  void AddSystemZTargetArgs(const llvm::opt::ArgList &Args,
                            llvm::opt::ArgStringList &CmdArgs) const;
  void AddX86TargetArgs(const llvm::opt::ArgList &Args,
                        llvm::opt::ArgStringList &CmdArgs) const;
  void AddHexagonTargetArgs(const llvm::opt::ArgList &Args,
                            llvm::opt::ArgStringList &CmdArgs) const;
  void AddLanaiTargetArgs(const llvm::opt::ArgList &Args,
                          llvm::opt::ArgStringList &CmdArgs) const;
  void AddWebAssemblyTargetArgs(const llvm::opt::ArgList &Args,
                                llvm::opt::ArgStringList &CmdArgs) const;

  enum RewriteKind { RK_None, RK_Fragile, RK_NonFragile };

  ObjCRuntime AddObjCRuntimeArgs(const llvm::opt::ArgList &args,
                                 llvm::opt::ArgStringList &cmdArgs,
                                 RewriteKind rewrite) const;

  void AddFortCLArgs(const llvm::opt::ArgList &Args, types::ID InputType,
                      llvm::opt::ArgStringList &CmdArgs,
                      codegenoptions::DebugInfoKind *DebugInfoKind,
                      bool *EmitCodeView) const;

  visualstudio::Compiler *getCLFallback() const;

  mutable std::unique_ptr<visualstudio::Compiler> CLFallback;

  mutable std::unique_ptr<llvm::raw_fd_ostream> CompilationDatabase = nullptr;
  void DumpCompilationDatabase(Compilation &C, StringRef Filename,
                               StringRef Target,
                               const InputInfo &Output, const InputInfo &Input,
                               const llvm::opt::ArgList &Args) const;

public:
  Fort(const ToolChain &TC);
  ~Fort() override;

  bool hasGoodDiagnostics() const override { return true; }
  bool hasIntegratedAssembler() const override { return true; }
  bool hasIntegratedCPP() const override { return true; }
  bool canEmitIR() const override { return true; }

  void ConstructJob(Compilation &C, const JobAction &JA,
                    const InputInfo &Output, const InputInfoList &Inputs,
                    const llvm::opt::ArgList &TCArgs,
                    const char *LinkingOutput) const override;
};

/// Fort integrated assembler tool.
class LLVM_LIBRARY_VISIBILITY FortAs : public Tool {
public:
  FortAs(const ToolChain &TC)
      : Tool("fort::as", "fort integrated assembler", TC, RF_Full) {}
  void AddMIPSTargetArgs(const llvm::opt::ArgList &Args,
                         llvm::opt::ArgStringList &CmdArgs) const;
  void AddX86TargetArgs(const llvm::opt::ArgList &Args,
                        llvm::opt::ArgStringList &CmdArgs) const;
  bool hasGoodDiagnostics() const override { return true; }
  bool hasIntegratedAssembler() const override { return false; }
  bool hasIntegratedCPP() const override { return false; }

  void ConstructJob(Compilation &C, const JobAction &JA,
                    const InputInfo &Output, const InputInfoList &Inputs,
                    const llvm::opt::ArgList &TCArgs,
                    const char *LinkingOutput) const override;
};

/// Offload bundler tool.
class LLVM_LIBRARY_VISIBILITY OffloadBundler final : public Tool {
public:
  OffloadBundler(const ToolChain &TC)
      : Tool("offload bundler", "fort-offload-bundler", TC) {}

  bool hasIntegratedCPP() const override { return false; }
  void ConstructJob(Compilation &C, const JobAction &JA,
                    const InputInfo &Output, const InputInfoList &Inputs,
                    const llvm::opt::ArgList &TCArgs,
                    const char *LinkingOutput) const override;
  void ConstructJobMultipleOutputs(Compilation &C, const JobAction &JA,
                                   const InputInfoList &Outputs,
                                   const InputInfoList &Inputs,
                                   const llvm::opt::ArgList &TCArgs,
                                   const char *LinkingOutput) const override;
};
} // end namespace tools

} // end namespace driver
} // end namespace fort

#endif // LLVM_FORT_LIB_DRIVER_TOOLCHAINS_FORT_H
