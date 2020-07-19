//
//  airline_tickets.hpp
//  test
//
//  Created by XIANGQIONG SHI on 7/16/20.
//  Copyright © 2020 xiangqiong. All rights reserved.
//

#include <stdio.h>

/*
You're building a tool to estimate the cost of various airplane tickets based on the airline, distance and seating class. Your tool must take in this information as a series of inputs (one ticket calculation per line of input) and produce a list of output costs.

Each airline contains its own cost requirements. Ultimately, the airline is only interested in two major components: the space you take on the plane, and the distance you fly. You must generate estimates using this gathered data:

Airlines: United, Delta, Southwest

Operating Costs:

 - Economy:  No charge
 - Premium:  $25
 - Business: $50 + $0.25/mile

Per-Airline Prices:

 - Delta charges $0.50/mile
   + OperatingCost
   
 - United charges $0.75/mile
   + OperatingCost
   + $0.10/mile for Premium seats

 - Southwest charges $1.00/mile


Keep in mind that, while there are only three airlines listed above, your solution should be able to expand to dozens of individual airlines, most of which will base their adjustments in part on the "Operating Costs" above.

Additional airlines could use arbitrary functions of miles and seating class. For example, "LuigiAir charges $100 or 2 * OperatingCost, whichever is higher."

You can assume that the input will be provided as a list of strings and that there could be millions of lines of input. Each string will provide the Airline, Distance and Seating Class. Please review the examples below:

Example Input:
-------------------------------------------
United 150.0 Premium
Delta 60.0 Business
Southwest 1000.0 Economy
-------------------------------------------

Example Output:
-------------------------------------------
152.50
95.00
1000.00
-------------------------------------------

Explanation of Output:
-------------------------------------------
152.50      (150.0 * (0.75 + 0.10) + 25)
95.00       (60.0 * (0.50 + 0.25) + 50)
1000.00     (1000.0 * 1.00)
-------------------------------------------
 */

#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

const vector<string> input = {
  "United 150.0 Premium",
  "Delta 60.0 Business",
  "Southwest 1000.0 Economy"
};

enum Seat{
   Economy,
   Premium,
   Business
};

class Airline{
public:
    Airline(){};
    virtual ~Airline(){};
    virtual float ticketPrice(float, Seat) = 0;
};

class United: public Airline{
public:
    United(){
        cout<<"United!"<<endl;
    }
  float ticketPrice(float miles, Seat S){
      float opCost = 0;
      if(S == Economy)
        opCost = 0;
      else if(S == Premium)
        opCost = 25+0.1*miles;
      else if(S == Business)
        opCost = 50+0.25*miles;
      float totalCost = opCost + 0.75*miles;
     return totalCost;
  }
};

class Delta: public Airline{
public:
    Delta(){
        cout<<"Delta!"<<endl;
    }
  float ticketPrice(float miles, Seat S){
      float opCost = 0;
      if(S == Economy)
        opCost = 0;
      else if(S == Premium)
        opCost = 25;
      else if(S == Business)
        opCost = 50+0.25*miles;
      float totalCost = opCost + 0.5*miles;
     return totalCost;
  }
};

class Southwest: public Airline{
public:
    Southwest(){
        cout<<"Southwest!"<<endl;
    }
  float ticketPrice(float miles, Seat S){
      
    float totalCost = 1*miles;
     return totalCost;
  }
};

std::shared_ptr<Airline> getAirline(const string& str){
    shared_ptr<Airline> A;
    if(str.compare("United") == 0){
        A = make_shared<United>();
    }
    else if(str.compare("Delta") == 0){
        A = make_shared<Delta>();
    }
    else if(str.compare("Southwest") == 0){
        A = make_shared<Southwest>();
    }
    return A;
}

Seat getSeat(const string& str){
    Seat S = Premium;
    if(str.compare("Premium") == 0){
        S = Premium;
    }
    else if(str.compare("Business") == 0){
        S = Business;
    }
    else if(str.compare("Economy") == 0){
        S = Economy;
    }
    return S;
}

int main() {
    for(int i = 0; i < input.size(); i++){
        stringstream ss(input[i]);
        string str;
        ss >> str;
        std::shared_ptr<Airline> A = getAirline(str);
        ss >> str;
        float miles = stof(str);
        ss >> str;
        Seat S = getSeat(str);
        float price = A->ticketPrice(miles, S);
        std::cout<<price<<std::endl;
    }
    return 0;
}
