//----------------------------------------------------------------------------//
//                         Teensy programmer library
//----------------------------------------------------------------------------//
// \file
// \brief Intel HEX format reader
//
//----------------------------------------------------------------------------//

#ifndef TPR_IHEX_READER_H
#define TPR_IHEX_READER_H

#include "Record.h"

#include <llvm/ADT/StringRef.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/SourceMgr.h>

#include <vector>

namespace tpr {
namespace ihex {

bool parseIHex(llvm::MemoryBuffer *, RecordList &, llvm::SMDiagnostic &);
bool parseIHexFile(llvm::StringRef, RecordList &, llvm::SMDiagnostic &);

} // namespace ihex
} // namespace tpr

#endif
