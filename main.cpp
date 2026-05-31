#include <iostream>
#include <memory>
#include <fstream>
#include <vector>
#include "./car.h"

int main(int argsc, char* argsv[]){

  float dt = 0.01;
  int runs = 1000;

  runs = std::atoi(argsv[1]);
  const int CAR_NUM = std::atoi(argsv[2]);

  std::vector<std::unique_ptr<car>> car_arr;
  car_arr.reserve(CAR_NUM);

  std::ofstream speed_file("speed_data.csv");
  std::ofstream acc_file("acc_data.csv");
  std::ofstream coord_file("coord_data.csv");

  speed_file << "time";
  acc_file << "time";
  coord_file << "time";

  for(int car_index = 0; car_index < CAR_NUM; car_index++){
    car_arr.push_back(std::make_unique<car>(car_index, car_index*20, car_index*5));
    speed_file << ",speed " << car_index+1;
    acc_file << ",acc " << car_index+1;
    if(car_index != CAR_NUM-1){
      coord_file << ",coord " << car_index+1 << "-" << car_index+2;
    }
  }
  speed_file << "\n";
  acc_file << "\n";
  coord_file << "\n";


  float time = 0;

  for(int step = 0; step < runs; step++){

    for(int car_index = 0; car_index < (CAR_NUM - 1); car_index++){
      car_arr[car_index]->move(car_arr[car_index+1],dt);
    }

    car_arr[CAR_NUM-1]->move_unobstructed(dt);
    time += 0.1;

    speed_file << time;
    acc_file << time;

    for (int i = 0; i < CAR_NUM;i++){
      speed_file << "," << car_arr[i]->get_speed();
      acc_file << "," << car_arr[i]->get_acc();
    }

    coord_file << time;
    for(int car_index = 1; car_index < CAR_NUM; car_index++){
      coord_file << "," << car_arr[car_index]->get_coord() - car_arr[car_index-1]->get_coord();
    }

    coord_file << "\n";
    speed_file << "\n";
    acc_file << "\n";
  }
  acc_file.close();
  speed_file.close();
  coord_file.close();

}
