#include "llvm/IR/Dominators.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/PassManager.h"

#include "llvm/Pass.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/raw_ostream.h"

#include <fstream>
#include <iostream>


using namespace llvm;
using namespace std;


namespace {
struct RemoveMain : public ModulePass {

  static char ID;
  RemoveMain() : ModulePass(ID) {}

  bool runOnModule(Module &M) override {
	


	Function* funcToRemoved;

	for(auto& F : M) {
	  const char *fname = F.getName().data();
	  if(strcmp(fname, "main") == 0){
		funcToRemoved = &F;
		continue;
	  }
	}

	funcToRemoved->eraseFromParent();
    return 0;
  }
};
} // namespace

char RemoveMain::ID = 0;
static RegisterPass<RemoveMain> X("removeMain", "remove main Pass");
