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

static cl::opt<string> testFunc("func", cl::desc("input Target Function Name To Run Fuzzer"), cl::value_desc("target function"), cl::Required);


namespace {
struct TEST : public ModulePass {

  static char ID;
  TEST() : ModulePass(ID) {}

  bool runOnModule(Module &M) override {
	

	string filePath = "test.c";

	ofstream writeFile(filePath.data());
	if( writeFile.is_open()){
	  writeFile << "int LLVMFuzzerTestOneInput(const uint32_t *Data, size_t Size) {\n";
	}
	Function* funcToRemoved;

	for(auto& F : M) {
	  const char *fname = F.getName().data();
	  
	  if(strcmp(fname, "main") == 0){
		funcToRemoved = &F;
		continue;
	  }
	  if(strcmp(fname, testFunc.c_str()) != 0){
		
		continue;
	  }

	  FunctionType* func_type = F.getFunctionType();
	  writeFile << "  int* iData = Data;\n";
	  writeFile << "  if(Size == " << func_type->getNumParams() * 4 << ") {\n";
	  writeFile << "    " << fname << "(";

	  if (func_type->getNumParams() > 0)
		if(func_type->getParamType(0)->getTypeID() == 13)
		  writeFile << "*iData";
		
	  for(int i = 1; i < func_type->getNumParams(); i++) {
		if(func_type->getParamType(i)->getTypeID() == 13)
		  writeFile << ", *(iData+" << i;
	  }

	  writeFile << ");\n  }\n";
 


    //errs() << "Func Name : " << F.getName() << "\n";
    //errs() << "Params Num : " << func_type->getNumParams() << "\n";

	//for(int i = 0; i<func_type->getNumParams(); i++)
	//{
	//  errs() << "Params : " << func_type->getParamType(i)->getTypeID() << "  ";

	//  if (func_type->getParamType(i)->getTypeID() == 15 )
	//	errs() << func_type->getParamType(i)->getPointerElementType()->getTypeID();
	// 
	//  errs() << "\n" ;
	//}

	}

	funcToRemoved->eraseFromParent();
	writeFile << "}\n";
    return 0;
  }
};
} // namespace

char TEST::ID = 0;
static RegisterPass<TEST> X("test", "test Pass");
