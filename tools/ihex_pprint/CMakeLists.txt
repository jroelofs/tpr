add_executable(ihex_pprint ihex_pprint.cpp)
target_link_libraries(ihex_pprint
    IHex
    LLVMSupport)
