add_library(IHex
    Reader.cpp
    Record.cpp
    )

target_link_libraries(IHex
    LLVMSupport
    )
