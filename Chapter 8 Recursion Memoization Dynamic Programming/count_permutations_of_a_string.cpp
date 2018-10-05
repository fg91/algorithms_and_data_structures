#include <iostream>
using namespace std;

void permutation(string str, string prefix){
  if(str.length()==0){
    cout<<prefix<<endl;
  }
  else{
    for(int i=0; i<str.length(); i++){ 
      string remaining = str.substr(0,i) + str.substr(i+1);
      permutation(remaining, prefix + str.at(i));
    }
  }
}

void permutation(string str){
  permutation(str, ""); 
}

int main () {
  // Total runtime smaller than O(n^2 * n!)
  permutation("fabiograetz");
  return 0;
}
