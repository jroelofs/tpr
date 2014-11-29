#include <tpr/IHex/Reader.h>
#include <tpr/IHex/Record.h>

using namespace tpr;
using namespace tpr::ihex;

int main() {
  Record r = Record(2).address(0).type(Record::Data).data(0,0xca).data(1,0xfe).autoChecksum();
  r.dump();
}
