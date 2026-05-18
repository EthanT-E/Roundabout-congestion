#include <iostream>
#include <memory>
#include <vector>
#include "./car.h"


int main(){
  std::unique_ptr<car> car_arr[3] = {
    std::make_unique<car>(car(0,0,20)),
    std::make_unique<car>(car(1,10,10)),
    std::make_unique<car>(car(2,20,30))
  };
  
  car_arr[0]->print_info();
  car_arr[1]->print_info();
  car_arr[2]->print_info();

  for(int i = 0; i < 1000; i++){
    car_arr[0]->move(car_arr[1]);
    car_arr[1]->move(car_arr[2]);
    car_arr[2]->move_unobstructed();
    
    std::cout <<"Car 1: ";
    car_arr[0]->print_info();
    std::cout <<"Car 2: ";
    car_arr[1]->print_info();
    std::cout <<"Car 3: ";
    car_arr[2]->print_info();
    std::cout << std::endl;
  }
  // std::unique_ptr<car> car_1 = std::make_unique<car> (car(0,10));
  // std::unique_ptr<car> car_2 = std::make_unique<car> (car(20,0));

  // for (int i = 0; i < 1000; i++){
  //   car_1->move(car_2);
  // }

}
