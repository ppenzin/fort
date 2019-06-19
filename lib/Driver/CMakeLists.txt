set(LLVM_LINK_COMPONENTS
  BinaryFormat
  Option
  Support
)

add_fort_library(fortDriver
  DriverOptions.cpp
  Driver.cpp
  DEPENDS
  FortDriverOptions
)

