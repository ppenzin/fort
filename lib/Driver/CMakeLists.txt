set(LLVM_LINK_COMPONENTS
  BinaryFormat
  Option
  Support
)

add_fort_library(fortDriver
  DriverOptions.cpp
  Driver.cpp
  ToolChains/AVR.cpp
  ToolChains/Ananas.cpp
  ToolChains/BareMetal.cpp
  ToolChains/Gnu.cpp

  DEPENDS
  FortDriverOptions

  LINK_LIBS
  fortBasic
)

