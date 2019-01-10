#include <iostream>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <stdlib.h>
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

int main(){
  FILE *code;
  if((code=fopen("1.txt", "r")) == NULL) {
    printf ("Cannot open file.\n");
    return 1;
  }
  vector<vector<string> > code_list;
  vector<vector<string> > code_tokens;
  vector<string> tmp_list;
  vector<string> tmp_tokens;
  string word = "";

  char ch;
  while((ch=getc(code)) != EOF){
    if(ch == ' '){
      if(word != ""){
        tmp_list.push_back(word);
        if(isKeyword(word)){
          tmp_tokens.push_back("Keyword");
        // }else if(isLiteral(word)){
        //   tmp_tokens.push_back("Literal");
        }
        word = "";
      }
    }else if(isOperator(ch)){
      if(word != ""){
        tmp_list.push_back(word);
      }
      word = ch;
      tmp_list.push_back(word);
      tmp_tokens.push_back("Operator")
      word = "";
    }else if(isSeparator(ch)){
      if(word != ""){
        tmp.push_back(word);
      }
      code_list.push_back(tmp);
      tmp.clear(); word = "";
    }else if(ch != '\n'){
      word += ch;
    }
  }

  for(int i = 0; i<code_list.size(); i++){
    for(int j =0; j<code_list[i].size(); j++){
      cout << code_list[i][j] << ' ';
    }
    cout << endl;
  }

  fclose (code);
  return 0;
}
