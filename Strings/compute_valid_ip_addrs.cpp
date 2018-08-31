/*
    Problem:
        Given a string number, find all the valid IP addresses that can formed from the given number.
        Eg. 12389: 1.23.8.9, 12.3.8.9 ....

    Input:
        Number: string

    Output:
        All possible Ip addresses in string form
*/

#include<iostream>
#include<string>
#include<vector>
using namespace std;

// checks if a byte position value is valid or not
bool isValid(string& part){

    // no. of digits should be max 3
    if(part.size() > 3)
            return false;

    // a valid part lies between 0 - 255
    // Also 0 is valid but 00 or 000 is invalid
    if(part.size() > 1 && part[0] == '0'){
        return false;
    }

    int num = 0;
    for(int i = 0; i < part.size(); i++){
        num *= 10;
        num += part[i] - '0';
    }

    return num >= 0 && num <= 255;
}

// finds the possible valid IP addresses
/*
    The addresses can be formed by placing '.' between digits.
    A valid IP address consists of 4 8-bit numbers or a total of 32-bits.
    Each byte is separated by '.'. So each position can have value in range(0-255)

    We try for combination by placing '.' for every three digits.
*/
vector<string> generateIPAddress(string num){
    // for storing the ip addresses
    vector<string> ip_addr;

    for(int i = 1; i<4 && i < num.size(); i++){
        // take the first part and check if it is valid
        string first = num.substr(0, i);
        // when the first part is valid, search for the next part
        if(isValid(first)){
            for(int j = 1; j + i < num.size() && j < 4; j++){
                // second term
                string second = num.substr(i, j);
                if(isValid(second)){
                    for(int k = 1; k + j + i < num.size() && k < 4; k++){
                        // third term
                        string third = num.substr(j + i, k);
                        // check if the third term is valid or not
                        if(isValid(third)){
                            for(int m = 1; m + k + j + i < num.size() && m < 4; m++){
                                //fourth term
                                string fourth = num.substr(k + j + i);

                                // check if the last term is valid or not
                                if(isValid(fourth)){
                                    ip_addr.emplace_back(first + "." + second + "." +
                                        third + "." + fourth);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return ip_addr;
}

int main(){
    vector<string> ip_addr = generateIPAddress("172267810");
    vector<string>:: iterator it;
    for(it = ip_addr.begin(); it!=ip_addr.end(); it++)
        cout << *it << endl;
        string t = "256";

    return 0;
}
