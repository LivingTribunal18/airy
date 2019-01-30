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



  ofstream vm_code("2.txt", ios::binary);

  if (!vm_code.is_open()){
      cout << "Cannot write in file \n";
      return 2;
  }

vector<vector<string> > vm_comands;
vector<string> vm_tmp;

vm_tmp.push_back("Identifier"); vm_tmp.push_back("Operator");
vm_tmp.push_back("Literal");    vm_comands.push_back(vm_tmp);

int push_byte = 0x03;
int store_byte = 0x02;
int halt = 0x00;

vector<int> counter(5, 0);

for(int i = 0; i < code_tokens.size(); i++){
   for(int j = 0; j < vm_comands.size(); j++){
      if (code_tokens[i] == vm_comands[j]) {
         counter[0]++;
      }
      if (counter[0] >= 1) {
           int lit_it = find(code_tokens[i].begin(), code_tokens[i].end(), "Literal") - code_tokens[i].begin();
           int id_it = find(code_tokens[i].begin(), code_tokens[i].end(), "Identifier") - code_tokens[i].begin();
           vm_code.write((char*)&push_byte, sizeof(push_byte));
           vm_code.write((char*)&code_list[i][lit_it], sizeof(code_list[i][lit_it]));
           vm_code.write((char*)&store_byte, sizeof(store_byte));
           vm_code.write((char*)&code_list[i][id_it], sizeof(code_list[i][id_it]));
      }
   }
}

vm_code.write((char*)&halt, sizeof(halt));




  vm_code.close();
  fclose (code);
  return 0;
}
