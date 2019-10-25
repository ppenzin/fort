//===--- LLVM.h - Import various common LLVM datatypes ----------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file forward declares and imports various common LLVM datatypes that
// fort wants to use unqualified.
//
//===----------------------------------------------------------------------===//

#ifndef FORT_BASIC_LLVM_H__
#define FORT_BASIC_LLVM_H__

// Do not proliferate #includes here, require clients to #include their
// dependencies.
// Casting.h has complex templates that cannot be easily forward declared.
#include "llvm/Support/Casting.h"
// None.h includes an enumerator that is desired & cannot be forward declared
// without a definition of NoneType.
#include "llvm/ADT/None.h"

namespace llvm {
// ADT's.
class APInt;
class APFloat;
class StringRef;
class Twine;
class VersionTuple;
template <typename T> class ArrayRef;
template <typename T> class MutableArrayRef;
template <unsigned InternalLen> class SmallString;
template <typename T, unsigned N> class SmallVector;
template <typename T> class SmallVectorImpl;
template <typename T> class Optional;

// Reference counting
template <typename T> class IntrusiveRefCntPtr;

class raw_ostream;
class raw_pwrite_stream;
// TODO: DenseMap, ...
} // namespace llvm

namespace fort {
// Casting operators.
using llvm::cast;
using llvm::cast_or_null;
using llvm::dyn_cast;
using llvm::dyn_cast_or_null;
using llvm::isa;

// ADT's.
using llvm::APFloat;
using llvm::APInt;
using llvm::ArrayRef;
using llvm::MutableArrayRef;
using llvm::None;
using llvm::Optional;
using llvm::SmallString;
using llvm::SmallVector;
using llvm::SmallVectorImpl;
using llvm::StringRef;
using llvm::Twine;
using llvm::VersionTuple;

// Reference counting
using llvm::IntrusiveRefCntPtr;

using llvm::raw_ostream;
using llvm::raw_pwrite_stream;
} // end namespace fort.

#endif
