#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include "./car.h"

int main(){
  std::unique_ptr<car> car_arr[5] = {
    std::make_unique<car>(car(0,0,20)),
    std::make_unique<car>(car(1,10,10)),
    std::make_unique<car>(car(2,20,30)),
    std::make_unique<car>(car(3,30,50)),
    std::make_unique<car>(car(4,40,10))
  };
  
  std::ofstream file("data.csv");

  file << "time,speed 1,acc 1, speed 2, acc 2, speed 3, acc 3, speed 4, acc 4, speed 5, acc 5";

  for(int i = 0; i < 1000; i++){
    car_arr[0]->move(car_arr[1]);
    car_arr[1]->move(car_arr[2]);
    car_arr[2]->move(car_arr[3]);
    car_arr[3]->move(car_arr[4]);
    car_arr[4]->move_unobstructed();
    
    file << i << "," << car_arr[0]->get_speed() << "," << car_arr[0]->get_acc() << ","<< car_arr[1]->get_speed() << "," << car_arr[1]->get_acc() << ","<< car_arr[2]->get_speed() << "," << car_arr[2]->get_acc() << ","<< car_arr[3]->get_speed() << "," << car_arr[3]->get_acc() << ","<< car_arr[4]->get_speed() << "," << car_arr[4]->get_acc() << "\n";
  }
  file.close();

}
