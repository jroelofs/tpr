//----------------------------------------------------------------------------//
//                         Teensy programmer library
//----------------------------------------------------------------------------//
// \file
// \brief Intel HEX format record implementation
//
//----------------------------------------------------------------------------//

#include <stdio.h>

#include "IHex/Record.h"

using namespace tpr::ihex;

void Record::dump() const {
  printf(":%02x", (int)m_length);
  printf("%04x", (int)m_address);
  printf("%02x", (int)m_type);
  for (unsigned i=0; i<m_length; ++i) {
    printf("%02x", m_data[i]);
  }
  printf("%02x", (int)m_checksum);
  printf("\n");
}

