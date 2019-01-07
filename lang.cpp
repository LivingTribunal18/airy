// modification 1, parsing with separator ";" and operators
#include <iostream>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <vector>
#include<bits/stdc++.h>
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
string keywords[] = {"close", "if", "else", "elseif"};


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


  code_list.pop_back();
  code_list.pop_back();

/*  <=== Operability Check of Parser === >
 for(int i = 0; i < code_list.size(); i++){
   cout << code_list[i] << endl;
  }
*/

  vector<string> transfer;

  for(int i = 0; i < code_list.size(); i++){
      if (code_list[i] == ":") {
          transfer.push_back("Operator");
      }else if (code_list[i] == ";" || code_list[i] == "!" || code_list[i] == "close") {
          break;
      }
          for (int j = 0; j < code_list[i].length(); j++) {
             if (code_list[i] >= "0" && code_list[i] <= "9999"){
               transfer.push_back("Literal");
               break;
            }else {
               break;
            }
          }
      if (code_list[i] != ":") {
          transfer.push_back("Identifier");
      }
  }

transfer.pop_back();

  /* <=== Operability Check of Translator ===>
   for(int i = 0; i < transfer.size(); i++){
      cout << transfer[i] << endl;
    }
*/

code.close();

return 0;
}
