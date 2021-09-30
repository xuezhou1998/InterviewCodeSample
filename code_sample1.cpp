vector<int> resInstr(string addrMod, int op, int modNumb){
  int result=0;
  int opcode=op/1000;
  int operand=op % 1000;
  int err=-1;
  int baseAddr=modules[modNumb];
  int unDef=-1;



  if (addrMod=="I"){
    if (op<10000){
      result=op;
    }
    else{
      err=4;
      result=9999;
    }
  }



  else if (addrMod=="E"){
    int newOperand=0;
    if (operand<usecount){
      result=opcode*1000;
      if (symbolTab.count(symLst[operand])<=0){
        result+=0;
        err=6;
        unDef=operand;
        std::vector<string>::iterator position =
        std::find(used_Lst.begin(), used_Lst.end(), symLst[operand]);
        if (position != used_Lst.end()){
          used_Lst.erase(position);
        }
      }
      else{
        newOperand=symbolTab[symLst[operand]];

        result+=newOperand;
        std::vector<string>::iterator position = std::find(used_Lst.begin(), used_Lst.end(), symLst[operand]);
        if (position != used_Lst.end()){
          used_Lst.erase(position);
        }
        symbolErr[symLst[operand]]-=1;
      }
    }
    else {
      err=2;
      result=op;
    }
  }



  else if (addrMod=="R"){
    if (modulesLen[modNumb]>operand){
      result=opcode*1000;
      result+=operand+baseAddr;
    }
    else{
      result=opcode*1000;
      result+=baseAddr;
      err=1;
    }
  }



  else if (addrMod=="A"){
    if (operand<512){
      result=opcode*1000;
      result+=operand;
    }
    else if (operand>=512){
      err=0;
      result=opcode*1000;
      result+=0;
    }
  }



  if (opcode>=10 && err==-1){
      err=5;
      result=9999;
    }
  vector<int> resV={result,err,operand,opcode,unDef};
  return resV;
}