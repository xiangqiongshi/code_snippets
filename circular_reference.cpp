//
//  main.cpp
//  test
//
//  Created by XIANGQIONG SHI on 6/26/20.
//  Copyright © 2020 xiangqiong. All rights reserved.
//
//circular reference
//https://www.internalpointer.com/post/beginner-s-look-smart-pointers-modern-c

#include <iostream>

struct Player
{
  //std::shared_ptr<Player> companion;
    std::weak_ptr<Player> companion;
    Player() {std::cout<< "Player\n"; }
  ~Player() { std::cout << "~Player\n"; }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::shared_ptr<Player> jasmine = std::make_shared<Player>();
    std::shared_ptr<Player> albert  = std::make_shared<Player>();

    jasmine->companion = albert; // (1)
    albert->companion  = jasmine; // (2)
    std::cout<<"jasmine count: "<<jasmine.use_count()<<std::endl;
    std::cout<<"albert count: "<<albert.use_count()<<std::endl;
    return 0;
}
