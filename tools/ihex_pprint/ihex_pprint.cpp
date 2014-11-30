#include <tpr/IHex/Reader.h>
#include <tpr/IHex/Record.h>

#include <llvm/Support/CommandLine.h>
#include <llvm/Support/Debug.h>


using namespace tpr;
using namespace tpr::ihex;

static llvm::cl::opt<std::string>
InputFilename(llvm::cl::Positional, llvm::cl::desc("<input hex>"),
              llvm::cl::init("-"));

class PPRecordVisitor {
public:
  void visit(const Record& r) {
    r.dump();
  };
};

int main(int argc, char **argv) {
  llvm::cl::ParseCommandLineOptions(argc, argv, "ihex pretty printer\n");

  RecordList HexFile;
  llvm::SMDiagnostic Err;
  if (!parseIHexFile(InputFilename, HexFile, Err)) {
    Err.print(argv[0], llvm::errs());
    return -1;
  }

  HexFile.visit(PPRecordVisitor());

  return 0;
}
