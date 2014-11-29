add_library(IHex
    Reader.cpp
    Record.cpp
    RecordSet.cpp
    )

target_link_libraries(IHex LLVMSupport)
