//----------------------------------------------------------------------------//
//                         Teensy programmer library
//----------------------------------------------------------------------------//
// \file
// \brief Intel HEX format record implementation
//
//----------------------------------------------------------------------------//

#include "IHex/Record.h"

#include <llvm/Support/Debug.h>
#include <llvm/Support/raw_ostream.h>

#include <sstream>
#include <iomanip>

using namespace tpr::ihex;

Record &Record::autoChecksum() {
  // TODO: calculate properly
  m_checksum = 0x42;
  return *this;
}

// Hack because llvm 3.5 doesn't have format_hex yet. We'd like to use the one
// in llvm/Support/Format.h, so hack together this one, which has a signature
// that is "close engough" to work.
namespace llvm {
static std::string format_hex(uint64_t num, unsigned digits) {
  std::stringstream ss;
  ss << std::hex << std::setw(digits) << std::setfill('0') << num;
  return ss.str();
}
} // namespace llvm

void Record::print(llvm::raw_ostream &OS, bool color) const {
  using namespace llvm;
  std::stringstream ss;
  if (color) OS.resetColor();

  if (color) OS.changeColor(raw_ostream::YELLOW, false, false);
  OS << ":";
  if (color) OS.resetColor();

  if (color) OS.changeColor(raw_ostream::GREEN, false, false);
  OS << format_hex(m_length, 2);
  if (color) OS.resetColor();

  if (color) OS.changeColor(raw_ostream::BLUE, false, false);
  OS << format_hex(m_address, 4);
  if (color) OS.resetColor();

  if (color) OS.changeColor(raw_ostream::RED, false, false);
  OS << format_hex((unsigned)m_type, 2);
  if (color) OS.resetColor();

  if (color) OS.changeColor(raw_ostream::CYAN, false, false);
  for ( Byte b : m_data )
    OS << format_hex(b, 2);
  if (color) OS.resetColor();

  if (color) OS.changeColor(raw_ostream::YELLOW, false, false);
  OS << format_hex(m_checksum, 2);
  if (color) OS.resetColor();

  OS << "\n";
}

void Record::dump() const {
  print(llvm::outs(), true);
}

