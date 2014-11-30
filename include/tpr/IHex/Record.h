//----------------------------------------------------------------------------//
//                         Teensy programmer library
//----------------------------------------------------------------------------//
// \file
// \brief Intel HEX format record
//
//----------------------------------------------------------------------------//

#ifndef TPR_IHEX_RECORD_H
#define TPR_IHEX_RECORD_H

#include <cinttypes>
#include <memory>
#include <vector>

namespace llvm {
  class raw_ostream;
}

namespace tpr {
namespace ihex {

class Record {
public:
  enum Type {
    Data            = 0x00,
    EndOfFile       = 0x01,
    ExtSegAddr      = 0x02,
    StartSegAddr    = 0x03,
    ExtLinearAddr   = 0x04,
    StartLinearAddr = 0x05,
    LAST_TYPE = StartLinearAddr
  };

  typedef uint16_t Address;
  typedef uint8_t  Byte;
  typedef uint16_t Checksum;
  typedef uint8_t  Length;

  Record(Length l) : m_length(l), m_data(l) {}
  Record &address(Address a) { m_address = a; return *this; }
  Record &type(Type t) { m_type = t; return *this; }
  Record &data(unsigned idx, Byte b) { m_data[idx] = b; return *this; }
  Record &checksum(Checksum c) { m_checksum = c; return *this; }
  Record &autoChecksum();

  Length length() const { return m_length; }
  Address address() const { return m_address; }
  Type type() const { return m_type; }
  Byte data(unsigned idx) const { return m_data[idx]; }
  Checksum checksum() const { return m_checksum; }

  void print(llvm::raw_ostream &, bool color = false) const;
  void dump() const;

private:
  Length m_length;
  Address m_address;
  Type m_type;
  std::vector<Byte> m_data;
  Checksum m_checksum;
};

class RecordList {
  typedef std::vector<Record> container;
public:
  void push_back(const Record&);

  template<typename Visitor>
  void visit(Visitor &v) const {
    for (const Record& r : m_records)
      v.visit(r);
  }

  template<typename Visitor>
  void visit(Visitor &&v) const {
    Visitor own = std::move(v);
    visit(own);
  }
private:
  std::vector<Record> m_records;
};

} // namespace ihex
} // namespace tpr

#endif
