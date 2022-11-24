add_compile_options(-fexceptions)

add_llvm_library(LLVMRemoveMain MODULE
  RemoveMain.cpp

  DEPENDS
  intrinsics_gen  
  PLUGIN_TOOL
  opt
  )


