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

#include <vector>

namespace tpr {
namespace ihex {

typedef std::vector<Record> RecordList;

bool ParseRecords(FILE* f, RecordList &records);
void PrintRecords(const RecordList &records);



} // namespace ihex
} // namespace tpr

#endif
