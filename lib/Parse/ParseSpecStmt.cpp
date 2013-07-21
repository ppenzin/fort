//===-- ParseSpecStmt.cpp - Parse Specification Statements ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "flang/Parse/Parser.h"
#include "flang/Parse/ParseDiagnostic.h"
#include "flang/AST/Decl.h"
#include "flang/AST/Expr.h"
#include "flang/AST/Stmt.h"
#include "flang/Basic/TokenKinds.h"
#include "flang/Sema/DeclSpec.h"
#include "flang/Sema/Sema.h"

namespace flang {

/// ParseDIMENSIONStmt - Parse the DIMENSION statement.
///
///   [R535]:
///     dimension-stmt :=
///         DIMENSION [::] array-name ( array-spec ) #
///         # [ , array-name ( array-spec ) ] ...
Parser::StmtResult Parser::ParseDIMENSIONStmt() {
  // Check if this is an assignment.
  if (PeekAhead().is(tok::equal))
    return StmtResult();

  auto Loc = ConsumeToken();
  ConsumeIfPresent(tok::coloncolon);

  SmallVector<Stmt*, 8> StmtList;
  SmallVector<ArraySpec*, 4> Dimensions;
  while (true) {
    auto IDLoc = Tok.getLocation();
    auto II = Tok.getIdentifierInfo();
    if(!ExpectAndConsume(tok::identifier)) {
      if(!SkipUntil(tok::comma, tok::identifier, true, true)) break;
      if(ConsumeIfPresent(tok::comma)) continue;
      else {
        IDLoc = Tok.getLocation();
        II = Tok.getIdentifierInfo();
        ConsumeToken();
      }
    }

    // FIXME: improve error recovery
    Dimensions.clear();
    if(ParseArraySpec(Dimensions)) return StmtError();

    auto Stmt = Actions.ActOnDIMENSION(Context, Loc, IDLoc, II,
                                       Dimensions, nullptr);
    if(Stmt.isUsable()) StmtList.push_back(Stmt.take());

    if(Tok.isAtStartOfStatement()) break;
    if(!ExpectAndConsume(tok::comma)) {
      if(!SkipUntil(tok::comma)) break;
    }
  }

  return Actions.ActOnCompoundStmt(Context, Loc, StmtList, StmtLabel);
}

/// ParseEQUIVALENCEStmt - Parse the EQUIVALENCE statement.
///
///   [R554]:
///     equivalence-stmt :=
///         EQUIVALENCE equivalence-set-list
Parser::StmtResult Parser::ParseEQUIVALENCEStmt() {
  return StmtResult();
}

/// ParsePARAMETERStmt - Parse the PARAMETER statement.
///
///   [R548]:
///     parameter-stmt :=
///         PARAMETER ( named-constant-def-list )
Parser::StmtResult Parser::ParsePARAMETERStmt() {
  // Check if this is an assignment.
  if (PeekAhead().is(tok::equal))
    return StmtResult();

  auto Loc = ConsumeToken();

  SmallVector<Stmt*, 8> StmtList;

  if(!ExpectAndConsume(tok::l_paren)) {
    if(!SkipUntil(tok::l_paren))
      return StmtError();
  }

  while(true) {
    auto IDLoc = Tok.getLocation();
    auto II = Tok.getIdentifierInfo();
    if(!ExpectAndConsume(tok::identifier)) {
      if(!SkipUntil(tok::comma)) break;
      else continue;
    }

    auto EqualLoc = Tok.getLocation();
    if(!ExpectAndConsume(tok::equal)) {
      if(!SkipUntil(tok::comma)) break;
      else continue;
    }

    ExprResult ConstExpr = ParseExpression();
    if(ConstExpr.isUsable()) {
      auto Stmt = Actions.ActOnPARAMETER(Context, Loc, EqualLoc,
                                         IDLoc, II,
                                         ConstExpr, nullptr);
      if(Stmt.isUsable())
        StmtList.push_back(Stmt.take());
    }

    if(ConsumeIfPresent(tok::comma))
      continue;
    if(isTokenIdentifier() && !Tok.isAtStartOfStatement()) {
      ExpectAndConsume(tok::comma);
      continue;
    }
    break;
  }

  if(!ExpectAndConsume(tok::r_paren))
    SkipUntilNextStatement();

  return Actions.ActOnCompoundStmt(Context, Loc, StmtList, StmtLabel);
}

/// ParseIMPLICITStmt - Parse the IMPLICIT statement.
///
///   [R560]:
///     implicit-stmt :=
///         IMPLICIT implicit-spec-list
///      or IMPLICIT NONE
Parser::StmtResult Parser::ParseIMPLICITStmt() {
  // Check if this is an assignment.
  if (PeekAhead().is(tok::equal))
    return StmtResult();

  auto Loc = ConsumeToken();

  if (ConsumeIfPresent(tok::kw_NONE)) {
    auto Result = Actions.ActOnIMPLICIT(Context, Loc, StmtLabel);
    ExpectStatementEnd();
    return Result;
  }

  SmallVector<Stmt*, 8> StmtList;

  while(true) {
    // FIXME: REAL(A) (A)
    // FIXME: improved error recovery
    DeclSpec DS;
    if (ParseDeclarationTypeSpec(DS))
      return StmtError();

    if(!ExpectAndConsume(tok::l_paren)) {
      if(!SkipUntil(tok::l_paren))
        break;
    }

    bool InnerError = false;
    while(true) {
      auto FirstLoc = Tok.getLocation();
      auto First = Tok.getIdentifierInfo();
      if(!ExpectAndConsume(tok::identifier, diag::err_expected_letter)) {
        if(!SkipUntil(tok::comma)) {
          InnerError = true;
          break;
        }
        continue;
      }
      if(First->getName().size() > 1) {
        Diag.Report(FirstLoc, diag::err_expected_letter);
      }

      const IdentifierInfo *Second = nullptr;
      if (ConsumeIfPresent(tok::minus)) {
        auto SecondLoc = Tok.getLocation();
        Second = Tok.getIdentifierInfo();
        if(!ExpectAndConsume(tok::identifier, diag::err_expected_letter)) {
          if(!SkipUntil(tok::comma)) {
            InnerError = true;
            break;
          }
          continue;
        }
        if(Second->getName().size() > 1) {
          Diag.Report(SecondLoc, diag::err_expected_letter);
        }
      }

      auto Stmt = Actions.ActOnIMPLICIT(Context, Loc, DS,
                                        std::make_pair(First, Second), nullptr);
      if(Stmt.isUsable())
        StmtList.push_back(Stmt.take());

      if(ConsumeIfPresent(tok::comma))
        continue;
      break;
    }

    if(InnerError && Tok.isAtStartOfStatement())
      break;
    if(!ExpectAndConsume(tok::r_paren)) {
      if(!SkipUntil(tok::r_paren))
        break;
    }

    if(Tok.isAtStartOfStatement()) break;
    if(!ExpectAndConsume(tok::comma)) {
      if(!SkipUntil(tok::comma))
        break;
    }
  }

  ExpectStatementEnd();
  return Actions.ActOnCompoundStmt(Context, Loc, StmtList, StmtLabel);
}

/// ParseEXTERNALStmt - Parse the EXTERNAL statement.
///
///   [R1210]:
///     external-stmt :=
///         EXTERNAL [::] external-name-list
Parser::StmtResult Parser::ParseEXTERNALStmt() {
  return ParseINTRINSICStmt(/*IsActuallyExternal=*/ true);
}

/// ParseINTRINSICStmt - Parse the INTRINSIC statement.
///
///   [R1216]:
///     intrinsic-stmt :=
///         INTRINSIC [::] intrinsic-procedure-name-list
Parser::StmtResult Parser::ParseINTRINSICStmt(bool IsActuallyExternal) {
  // Check if this is an assignment.
  if (PeekAhead().is(tok::equal))
    return StmtResult();

  auto Loc = ConsumeToken();
  ConsumeIfPresent(tok::coloncolon);

  SmallVector<Stmt *,8> StmtList;

  while(true) {
    auto IDLoc = Tok.getLocation();
    auto II = Tok.getIdentifierInfo();
    if(!ExpectAndConsume(tok::identifier)) {
      if(!SkipUntil(tok::comma, tok::identifier, true, true)) break;
      if(ConsumeIfPresent(tok::comma)) continue;
      else {
        IDLoc = Tok.getLocation();
        II = Tok.getIdentifierInfo();
        ConsumeToken();
      }
    }

    auto Stmt = IsActuallyExternal?
                  Actions.ActOnEXTERNAL(Context, Loc, IDLoc,
                                        II, nullptr):
                  Actions.ActOnINTRINSIC(Context, Loc, IDLoc,
                                         II, nullptr);
    if(Stmt.isUsable())
      StmtList.push_back(Stmt.take());

    if(Tok.isAtStartOfStatement()) break;
    if(!ExpectAndConsume(tok::comma)) {
      if(!SkipUntil(tok::comma)) break;
    }
  }

  return Actions.ActOnCompoundStmt(Context, Loc, StmtList, StmtLabel);
}


}