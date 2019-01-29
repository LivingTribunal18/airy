#include <iostream>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <bits/stdc++.h>


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



  ofstream vm_code("2.txt");

  if (!vm_code.is_open()){
      cout << "Cannot write in file \n";
      return 2;
  }

vector<vector<string> > vm_comands;
vector<string> vm_tmp;

vm_tmp.push_back("Identifier");
vm_tmp.push_back("Operator");
vm_tmp.push_back("Literal");
vm_comands.push_back(vm_tmp);

int counter = 0;
string tok = "Literal"; string tok1 = "Identifier";

for(int i = 0; i < code_tokens.size(); i++){
   for(int j = 0; j < vm_comands.size(); j++){
      if (code_tokens[i] == vm_comands[j]) {
         counter++;
      }
      if (counter >= vm_comands.size()) {
           int it = find(code_tokens[i].begin(), code_tokens[i].end(), tok) - code_tokens[i].begin();
           int it1 = find(code_tokens[i].begin(), code_tokens[i].end(), tok1) - code_tokens[i].begin();
           vm_code << "PUSH " << code_list[i][it] << "\n";
           vm_code << "STORE " << code_list[i][it1] << "\n";
      }
   }
}
  vm_code << "HALT \n";


  vm_code.close();
  fclose (code);
  return 0;
}
