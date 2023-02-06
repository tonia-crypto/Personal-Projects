#include <iostream>
#include <string>
#include "./string_calculator.h"

using std::cout, std::endl;
using std::string;

//Decimal to digit: WORKS
unsigned int digit_to_decimal(char digit) {

    // TODO(student): implement
    
    // decimals are from 0 to 9 no negative numbers
    if ((digit == '0') || ( digit >= '1' &&  digit <= '9')){
        //I am getting 55 when plugging in 7 so I am gonna substract 48 to make it equal to the actual number:
      
       int decimal = (int)digit - '0';
       return decimal;
    }else{

      throw (std::invalid_argument("Invalid argument "));
    }
    return 0;
}

// Decimal to dogotal: WORKS
char decimal_to_digit(unsigned int decimal) {
    // TODO(student): implement
    if ((decimal == 0) ||(decimal >= 1 && decimal <= 9)){
        char digit = decimal + '0';
        return digit;
    }else{

      throw (std::invalid_argument("Invalid argument "));
    }
    return '\0';
}

//trimmimg zero: WORKS
string trim_leading_zeros(string num) {
    // TODO(student): implement
    if(num[0] == '0'){
        while(num[0] == '0' ){
            num.erase(0,1);
            if(num.length() == 1 && num[0] == '0'){
                return "0";
            }
        }
    }else if(num[0] == '-'){

        while(num[1]=='0'){
            // cout<<"The nimb is: "<<num[1] <<endl;
            num.erase(1,1);
            if(num.length() == 1 && num[0] == '-'){
                return "0";
            }
        }
    }   
     return num;
}


// NEED WORK 
string subtract(string lhs, string rhs) {
  rhs = "";
  lhs = "";

  return "Did not finish yet!";  
}

//ADD function: WORKING
string add(string lhs, string rhs) {
    bool negative = false;
    if (lhs.at(0) == '-' && rhs.at(0) == '-') {
        negative = true;
        lhs = lhs.erase(0,1);
        rhs = rhs.erase(0,1);
    } else if (lhs.at(0) == '-' || rhs.at(0) == '-') {
        return subtract(lhs, rhs); // look for the signs
    }

    // TODO(student): implement
    if(rhs == "0"){
        return lhs;
    }else if(lhs == "0"){
        return rhs;
    }else if ( lhs == rhs && rhs == "0"){
        return "0";
    }
    //trying to make two strings the same size:
    while(lhs.size() > rhs.size()){
        rhs.insert(0,"0");
    }
  
    while(lhs.size() < rhs.size()){
        lhs.insert(0,"0");
    }
    

    int rhs_int; 
    int lhs_int; 
    int carry = 0; 

    // reverse the number to go back to the actual phase we need it in:

    string reversed_str_result = "";

    for(int i = lhs.size()-1; i >=0; i--) {
        lhs_int = digit_to_decimal(lhs.at(i)); 
        rhs_int = digit_to_decimal(rhs.at(i));
        
        int temp = lhs_int + rhs_int + carry; 

        reversed_str_result = reversed_str_result + decimal_to_digit(temp%10);
        carry = temp/ 10;

    }
    reversed_str_result = reversed_str_result + decimal_to_digit(carry);
    int size = reversed_str_result.size();
    for (int i = 0; i < (size/2); i ++){
        char temp = reversed_str_result.at(i);
        reversed_str_result.at(i) = reversed_str_result.at(size-i-1);
        reversed_str_result.at(size-i-1) = temp;

    }

    // return the negative sign for one side negative number:
    
    if (negative) {
        reversed_str_result.insert(0,"-");
    }

    return  trim_leading_zeros(reversed_str_result);
}
// NEED WORK 
string multiply(string lhs, string rhs) {
//    cout << "--- calling: multiply(string, string) ---" << endl;

    // cout << "lhs: " << lhs << endl;
    // cout << "rhs: " << rhs << endl;
    // cout << endl;

   // check the negative sign:
    bool negative = false;
    if (lhs.at(0) == '-' && rhs.at(0) == '-') {
        lhs = lhs.erase(0,1);
        rhs = rhs.erase(0,1);
    } else if (lhs.at(0) == '-' || rhs.at(0) == '-') {
        negative = true; // look for the signs
        if(lhs.at(0) == '-'){
            lhs.erase(0,1);
        }if(rhs.at(0)== '-'){
            rhs.erase(0,1);
        } 
    }

// some Varibale introduction:
    string mult_result="0";
    string top;
    string bot;
    int bot_int;
    int top_int;
    int mult_carry = 0;
    string mult_total = "";


    // easy test, mutiply by "0" :
    if(rhs == "0"){
        return "0";
    }else if(lhs == "0"){
        return "0";
    }else if ( lhs == "0" && rhs == "0"){
        return "0";
    }

    // easy test, mutiply by "1" :
    if(rhs == "1"){
        return lhs;
    }else if(lhs == "1"){
        return rhs;
    }else if ( lhs == "1" && rhs == "1"){
        return "1";
    }
    
    // actual multiplication:
    // have bigger number on top and smaller number on bottom:
    lhs = "0" + lhs;
    rhs = "0" + rhs;

    if( lhs.size() > rhs.size()){
        top = lhs;
        bot = rhs;
    }else{
        top= rhs;
        bot = lhs;
    }

string sum = "0";

    // cout << "BEFORE LOOP top number:    " << top << endl;
    // cout << "BEFORE LOOP bottom number: " << bot << endl;

    string postfix = "";

    // loop through bottom digit
    for(int i = bot.size()-1; i >= 0; i--) {

        // cout << "i: " << i << endl;
        // cout << "   bottom digit: " << bot.at(i) << endl;
        
        // mult_total= "0";


        // for(int k = (bot.size()-1-i); k > 0; k--){
        //     mult_total.push_back('0');
        // }

        mult_total = postfix;


        // loop through top digit
        for(int j = top.size()-1; j >=0;j--){

            // cout << "   j: " << j << endl;
            // cout << "      top digit: " << top.at(j) << endl;


            bot_int = digit_to_decimal(bot.at(i)); 
            top_int = digit_to_decimal(top.at(j));
            
            int temp = (bot_int * top_int) + mult_carry;

            // cout << "      OLD temp: " << temp << endl;

            mult_carry = temp / 10;
            if (temp > 9) {
                temp = temp % 10;
            }

            // cout << "      NEW temp: " << temp << endl;

            // cout << "      mult_carry: " << mult_carry << endl;            
            // cout << "      debug decimal_to_digit: " << decimal_to_digit(temp) << endl;
            // cout << "      BEFORE mult_total: " << mult_total << endl;
            mult_total = decimal_to_digit(temp) + mult_total;
            // cout << "      AFTER mult_total: " << mult_total << endl;
                      
           //cout<< "mult_total after dec to dig:   " << mult_total << endl;
    
            // 08
            // mult_total = trim_leading_zeros(mult_total);
           
            
            // cout<< "mult_total after dec to dig:   " << mult_total << endl;
            // //place*=10;
            // cout<< "i         : "<< i<< endl;
            // cout<< " sum      :" << sum<< endl;

        }

        // cout << "mult_total: " << mult_total << endl;

        postfix += "0";


        // cout << "OLD sum: " << sum << endl;
        // cout << "mult_total: " << mult_total << endl;

        sum = add(sum, mult_total);

        //cout << "NEW sum: " << sum << endl;
    

        //cout <<"sum: " << sum << endl;
      
    }
    //sum = sum.erase(sum.size()-1);
// return the negative sign for one side negative number:
    
    if (negative) {
        sum.insert(0,"-");
    }

    return trim_leading_zeros(sum);

} 


//EXTRA CREDITS: NEED WORK