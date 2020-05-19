/*==================================
Algorithm-and-Data-Structure-Analysis
Student: Vandit Jyotindra Gajjar
id: a1779153
Semester: 1
Year: 2020
Assignment : 3
===================================*/
//Importing libraries.
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
using namespace std;

//Definign class Hashtable and make it public as well. 
class Hashtable{

  public:
	//Initializing string array to store values 
    string table[26];
	
	//Constructor - Hashtable
	Hashtable(){
      int i = 0;
	  while(i<26){
		  table[i] = "never used";
		  i++;
	  }
    }
	
	//Get the last char as hash key
    char getKey(string str){
      return str.back();
    }
	
	//Convert character to int and setting into range 0 to 25.
    int getIndex(char ch){
      int tmpIndex = (int)ch-97;
	  return tmpIndex;
    }
	
	//Defining the function locateKey
    string locateKey(string key){
      int index = getIndex(getKey(key));
	  string empty = "";
	  
	  //If the key is found in array, we return it. 
      if(table[index] == key){
        return table[index];
      }
	  
	  //Else, we check for key from index+1 to index; if the key not found, we return empty string
      else{
        int i = index+1;
        while(i != index){
          if(i == 26){
            i = 0;
          }
          if(table[i] == key){
            return table[i];
          }
          else if(table[i] == "never used"){
            
			return empty;
          }
          i++;
        }
        return empty;
      }
    }
	
	//Function addKey - for inserting a key in hashtable
    void addKey(string key){
		
	  //If key located return nothing 
      if(locateKey(key) != ""){
        return;
      }
	  
	  //If index is empty, we append key in that index. 
      int index = getIndex(getKey(key));
      if(table[index] == "never used" || table[index] == "tombstone"){
        table[index] = key;
      }
	  
	  //Else, we locate the key in the whole array, if it's not present, we append the key. 
      else{
        int i = index+1;
        while(i != index){
          if(i == 26){
            i = 0;
          }
          if(table[i] == "never used" || table[i] == "tombstone"){
            table[i] = key;
            return;
          }
          i++;
        }
      }
    }
	
	//Function deleteKey for deleting the key
    void deleteKey(string key){
      int index = getIndex(getKey(key));
	  
	  //If key is found, we assign tombstone
      if(table[index] == key){
        table[index] = "tombstone";
		return;
      }
	  
	  //Else, we look through the array, if key's not found, we terminate. 
      else{
        int i = index+1;
        while(i != index){
          if(i == 26){
            i = 0;
          }
          if(table[i] == key){
			table[i] = "tombstone";
            return;
          }
          else if(table[i] == "never used"){
            return;
          }
          i++;
        }
        return;
      }
    }
	
	//Function for printing the table 
    void print(){
      int i = 0;
	  while(i<26){
		if(table[i] != "never used" && table[i] != "tombstone"){
		  string tmp = table[i];
          cout<<tmp<<" ";
        }
		i++;
      }
      cout<<endl;
	  
	  }
};

//Main method 
int main(void) {
    Hashtable table;
    string ip;
    getline( cin, ip );
    istringstream is( ip );
    vector<string> input((istream_iterator<string>(is)), istream_iterator<string>());
    int i = 0;
	
	//If firstChar is A we insert key otherwise remove it. 
	while(i < input.size()){
	  (input[i].front() == 'A') ? table.addKey(input[i].substr(1)) : table.deleteKey(input[i].substr(1));
	  i++;
	}
    table.print();
    return 0;
}

/* Useful References: Acknowledgements 
[1] https://www.modernescpp.com/index.php/hash-tables
[2] https://www.tutorialspoint.com/cplusplus-program-to-implement-hash-tables
[3] https://www.tutorialspoint.com/cplusplus-program-to-implement-hash-tables-with-linear-probing
[4] https://www.geeksforgeeks.org/implementing-hash-table-open-addressing-linear-probing-cpp/
[5] https://www.sanfoundry.com/cpp-program-implement-hash-tables-linear-probing/
*/
