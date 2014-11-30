//----------------------------------------------------------------------------//
//                         Teensy programmer library
//----------------------------------------------------------------------------//
// \file
// \brief Intel HEX format record implementation
//
//----------------------------------------------------------------------------//

#include "IHex/Reader.h"

#include <llvm/ADT/StringRef.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/LineIterator.h>
#include <llvm/Support/Debug.h>

#include <iomanip>
#include <sstream>

using namespace llvm;
using namespace tpr::ihex;

namespace tpr {
namespace ihex {

static bool parseError(line_iterator &li, SMDiagnostic &Err, StringRef Msg) {
  llvm::errs() << Msg << "\n";
  return false;
}

bool parseIHex(MemoryBuffer *Buffer, RecordList &Records,
               SMDiagnostic &Err) {
  for (line_iterator li = line_iterator(*Buffer); !li.is_at_end(); ++li) {
    std::stringstream line(li->str());

    if (li->size() < 11)
      return parseError(li, Err, "Line must be at least 11 characters long");

    char colon;
    line >> colon;
    if (colon != ':')
      return parseError(li, Err, "Line must start with ':'");

    llvm::errs() << line.str() << "\n";

    uint8_t length;
    line >> std::hex >> std::setw(2) >> length;

    llvm::errs() << "len is: " << std::to_string(length) << "\n";

    unsigned totalLength = 1 + 2 + 4 + 2 + (unsigned)length + 2;
    if (li->size() != totalLength)
      return parseError(li, Err, "Line length must be exactly " +
                        std::to_string(totalLength) + " characters long. Line is " +
                        std::to_string(li->size()) + " characters long.");

    Record record(length);

    uint16_t address;
    line >> std::hex >> address;
    record.address(address);
    llvm::errs() << line.str() << "\n";

    uint8_t type;
    line >> std::hex >> type;
    if (type > Record::LAST_TYPE)
      return parseError(li, Err, "Invalid record type '" + std::to_string(type) + "'");

    for (unsigned i = 0; i < length; ++i) {
      Record::Byte byte;
      line >> std::hex >> byte;
      record.data(i, byte);
    }
    llvm::errs() << line.str() << "\n";

    Record::Checksum checksum;
    line >> std::hex >> checksum;
    record.autoChecksum();
    llvm::errs() << line.str() << "\n";

    llvm::errs() << "source line: " << *li << "\n"
                 << "record: ";
    record.dump();
    llvm::errs() << "\n";

    if (record.checksum() != checksum)
      return parseError(li, Err, "Checksum " + std::to_string(checksum) +
                        " doesn't match calculated value: " +
                        std::to_string(record.checksum()));


    Records.push_back(record);
  }
  return true;
}

bool parseIHexFile(StringRef Filename, RecordList &Records,
                   SMDiagnostic &Err) {
  ErrorOr<std::unique_ptr<MemoryBuffer>> FileOrErr =
    MemoryBuffer::getFileOrSTDIN(Filename);
  if (std::error_code EC = FileOrErr.getError()) {
    Err = SMDiagnostic(Filename, SourceMgr::DK_Error,
                       "Could not open input file: " + EC.message());
    return false;
  }

  return parseIHex(FileOrErr.get().get(), Records, Err);
}

} // namespace ihex
} // namespace tpr


