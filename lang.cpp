// modification 1, parsing with separator ";" and operators
#include <iostream>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <vector>
#include <fstream>

using namespace std;

char operators[] = {':'};
bool isOperator(char word){
  for (int i = 0; i < sizeof(operators)/sizeof(char); i++) {
    if (word == operators[i]){
      return true;
    }
  }
  return false;
}
char separators[] = {';', '!'};
bool isSeparator(char list){
  for (int i = 0; i < sizeof(separators)/sizeof(char); i++) {
    if (list == separators[i]){
      return true;
    }
  }
  return false;
}


int main(){
  ifstream code("1.txt");
  vector<string> code_list;
  string word = "";

  char ch;
  while (!code.eof()) {
      code >> ch;
      if((isOperator(ch)) || (isSeparator(ch))){
        code_list.push_back(word);
        word = ch;
        code_list.push_back(word);
        word = "";
      }else{
        word += ch;
      }
  }
  //if(word != ""){
    //code_list.push_back(word);
  //}

  code_list.pop_back();
  code_list.pop_back();

//  for(int i = 0; i < code_list.size(); i++){
  //  cout << code_list[i] << endl;
  //}// operability check

  vector<string> transfer;

  string id = "Identifier";
  string lit = "Literal";
  string op = "Operator";

    for(int i = 0; i < code_list.size(); i++){
      cout << code_list[i] << endl;
      if (code_list[i] == operators[0]) {
          transfer[i].push_back(op);
      }else if (code_list[i] != operators[0]) {
        for (int j = 0; j < code_list[i].length(); j++) {
            if ((code_list[i][j] >= 0) && (code_list[i][j] <= 10)) {
              transfer[i].push_back(lit);
            }
        }
      }else {
        transfer[i].push_back(id);
      }

    }


code.close();

return 0;
}
