//===--- AllDiagnostics.h - Aggregate Diagnostic headers --------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief Includes all the separate Diagnostic headers & some related helpers.
///
//===----------------------------------------------------------------------===//

#ifndef LLVM_FORT_ALL_DIAGNOSTICS_H
#define LLVM_FORT_ALL_DIAGNOSTICS_H

#include "fort/Driver/DriverDiagnostic.h"
#include "fort/Frontend/FrontendDiagnostic.h"
#include "fort/Parse/LexDiagnostic.h"
#include "fort/Parse/ParseDiagnostic.h"
#include "fort/Sema/SemaDiagnostic.h"

namespace fort {
template <size_t SizeOfStr, typename FieldType> class StringSizerHelper {
  char FIELD_TOO_SMALL[SizeOfStr <= FieldType(~0U) ? 1 : -1];

public:
  enum { Size = SizeOfStr };
};
} // end namespace fort

#define STR_SIZE(str, fieldTy)                                                 \
  fort::StringSizerHelper<sizeof(str) - 1, fieldTy>::Size

#endif
