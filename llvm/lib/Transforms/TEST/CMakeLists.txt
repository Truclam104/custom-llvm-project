add_compile_options(-fexceptions)

add_llvm_library(LLVMTEST MODULE
  TEST.cpp

  DEPENDS
  intrinsics_gen  
  PLUGIN_TOOL
  opt
  )


