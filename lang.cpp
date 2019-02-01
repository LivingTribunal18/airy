#include <iostream>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <bits/stdc++.h>
#include <ctype.h>


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

int asci = 0;
void ascii(string letter){
  if(letter == "a") {asci = 0x61;}
  else if(letter == "b") {asci = 0x62;}
  else if(letter == "c") {asci = 0x63;}
  else if(letter == "d") {asci = 0x64;}
  else if(letter == "e") {asci = 0x65;}
  else if(letter == "f") {asci = 0x66;}
  else if(letter == "g") {asci = 0x67;}
  else if(letter == "h") {asci = 0x68;}
  else if(letter == "i") {asci = 0x69;}
  else if(letter == "j") {asci = 0x6A;}
  else if(letter == "k") {asci = 0x6B;}
  else if(letter == "l") {asci = 0x6C;}
  else if(letter == "m") {asci = 0x6D;}
  else if(letter == "n") {asci = 0x6E;}
  else if(letter == "o") {asci = 0x6F;}
  else if(letter == "p") {asci = 0x70;}
  else if(letter == "q") {asci = 0x71;}
  else if(letter == "r") {asci = 0x72;}
  else if(letter == "s") {asci = 0x73;}
  else if(letter == "t") {asci = 0x74;}
  else if(letter == "u") {asci = 0x75;}
  else if(letter == "v") {asci = 0x76;}
  else if(letter == "w") {asci = 0x77;}
  else if(letter == "x") {asci = 0x78;}
  else if(letter == "y") {asci = 0x79;}
  else if(letter == "z") {asci = 0x7A;}
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

string tok = "Literal", tok1 = "Identifier";


for(int i = 0; i < code_tokens.size(); i++){
   for(int j = 0; j < vm_comands.size(); j++){
      if (code_tokens[i] == vm_comands[j]) {
         counter[0]++;
      }
      if (counter[0] >= 1) {
           int lit_it = find(code_tokens[i].begin(), code_tokens[i].end(), tok) - code_tokens[i].begin();
           int id_it = find(code_tokens[i].begin(), code_tokens[i].end(), tok1) - code_tokens[i].begin();
           vm_code.write((char*)&push_byte, sizeof(push_byte));
           int stoi = atoi(code_list[i][lit_it].c_str());
           vm_code.write((char*)&stoi, sizeof(stoi));
           stoi = 0;
           vm_code.write((char*)&store_byte, sizeof(store_byte));
           ascii(code_list[i][id_it]);
           vm_code.write((char*)&asci, sizeof(asci));
      }
   }
}

vm_code.write((char*)&halt, sizeof(halt));

  vm_code.close();
  fclose (code);
  return 0;
}
