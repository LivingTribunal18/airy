#include <iostream>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <algorithm>


using namespace std;

vector<vector<string> > code_list;
vector<vector<string> > code_tokens;
vector<string> tmp_list;
vector<string> tmp_tokens;
vector<string> s;

char operators[] = {':'};
bool isOperator(char word){
  for (int i = 0; i < sizeof(operators)/sizeof(char); i++) {
    if (word == operators[i]){
      return true;
    }
  }
  return false;
}

char separators[] = {';'};
bool isSeparator(char list){
  for (int i = 0; i < sizeof(separators)/sizeof(char); i++) {
    if (list == separators[i]){
      return true;
    }
  }
  return false;
}

string keywords[] = {"if", "else", "elseif"};
bool isKeyword(string word){
  for(int i = 0; i < sizeof(keywords)/sizeof(char); i++) {
    if (word == keywords[i]){
      return true;
    }
  }
  return false;
}

bool isLiteral(string word){
  int isDigit = 0;
  int j = 0;
  while((j < word.length()) && (isDigit == 0)){
    isDigit = isdigit(word[j]);
    j++;
  }
  return isDigit;
}

void push(string word){
  if(word != ""){
    tmp_list.push_back(word);
    if(isKeyword(word)){
      tmp_tokens.push_back("Keyword");
     }else if(isLiteral(word)){
       tmp_tokens.push_back("Literal");
    }else{
      tmp_tokens.push_back("Identifier");
    }
  }
}

int main(){
  FILE *code;
  if((code = fopen("1.txt", "r")) == NULL) {
    printf ("Cannot open file.\n");
    return 1;
  }

  char ch;
  string word = "";
  while((ch = getc(code)) != EOF){
    if(ch == ' '){
      push(word);
      word = "";
    }else if(isOperator(ch)){
      push(word);
      word = ch;
      tmp_list.push_back(word);
      tmp_tokens.push_back("Operator");
      word = "";
    }else if(isSeparator(ch)){
      push(word);
      code_list.push_back(tmp_list);
      code_tokens.push_back(tmp_tokens);
      word = "";
      tmp_list.clear(); tmp_tokens.clear();
    }else if(ch != '\n'){
      word += ch;
    }
  }


vector<vector<string> > vm_comands;
vector<string> vm_tmp;

vm_tmp.push_back("Identifier");
vm_tmp.push_back("Operator");
vm_tmp.push_back("Literal");
vm_comands.push_back(vm_tmp);

int counter = 0;

for(int i = 0; i < code_tokens.size(); i++){
  for(int j = 0; j < vm_comands.size(); j++){
   if (code_tokens[i] == vm_comands[j]) {
       counter++;
   }
    if (counter == vm_comands.size()) {
       for (int i = 0; i < vm_comands.size(); i++) {
         for (int j = 0; j < vm_comands[i].size(); j++) {
           for (int k = 0; k < code_list.size(); k++) {
             for (int l = 0; l < code_list[k].size(); l++) {
                if (vm_comands[i][j] == "Operator" && code_list[k][l] == ":") {
                    s.push_back("PUSH " + code_list[k][l+1]);
                    s.push_back("STORE " + code_list[k][l-1]);
                }
              }
            }
          }
        }
      }
    }
  }
s.push_back("HALT");

for (int i = 0; i < s.size(); i++) {
  cout << s[i];
  cout << "\n";
}

  
  fclose (code);
  return 0;
}
