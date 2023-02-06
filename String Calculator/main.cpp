#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include "./string_calculator.h"

using std::cout, std::endl, std::cin;
using std::string;

int main() {


  // eof
  // answer to be write underneath the >>
  // invalid lhs and invalid rhs

  //TODO(student): implement the UI

    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;

  
    string lhs = ""; 
    string rhs = ""; 
    string sign = "";
    string equ = "";
    
    std::stringstream ss;
  do{
    cout<<">> ";
    
    
    getline(cin, equ);
    ss.str(equ);
    ss.clear();

    if (equ == "" ||equ == "q"||equ == "quit") {
    cout <<endl<<"farvel!" << endl;
    return 0;
    }
   cout<<'\n';
   
   
    ///////////eof
 
       
    ss >> lhs >> sign >> rhs;

    string total;
    if(sign == "+"){
      total = add(lhs, rhs);
    }else if (sign == "*"){
      total = multiply(lhs, rhs); 
    }
    
    cout<<"ans ="<<endl<<endl;
    cout<<"    "<<total<<endl<<endl;
    
    } while (equ != "" ||equ != "q"||equ != "quit");
  }  
    
    
    
   // DELETE BEFORE SUBMITTING FINAL SCRIPT:  
    

    //Digital to Decimal working
    //cout<<"Digital to Decimal: "<< digit_to_decimal('7') <<endl;
    //cout<<"Digital to Decimal: "<< digit_to_decimal('/') <<endl;

  // Decimal to Digit is working 
    //cout<< "Decimal to Digital: "<< decimal_to_digit(7) <<endl;
    // cout<< "Decimal to Digital: "<< decimal_to_digit(123456) <<endl;
  
  // Trim leasing Zeros is working
    // cout<< "Trim leading zero: " <<trim_leading_zeros("-00123")<< endl;
    // cout<< "Trim leading zero: " <<trim_leading_zeros("00000")<< endl;
    // cout<< "Trim leading zero: " <<trim_leading_zeros("00123")<< endl;
    // cout<< "Trim leading zero: " <<trim_leading_zeros("-00000")<< endl;
    // cout<< "Trim leading zero: " <<trim_leading_zeros("-0000000000000000000326031034539696741651963735362758771645")<< endl;

  //Add funciton
     //cout<< "ADD: " <<add("9","2")<< endl;
    // cout<< "ADD: " <<add("2","-1")<< endl;
    // cout<< "ADD: " <<add("2","1")<< endl;
    // cout<< "ADD: " <<add("1","2")<< endl;
  
  // MULTIPLICATION function:

  // cout<<"MULTIPLY: "<< multiply("-1","1")<<endl;
  // cout<<"MULTIPLY: "<< multiply("0","-1")<<endl;
  // cout<<"MULTIPLY: "<< multiply("-1","-1")<<endl;



