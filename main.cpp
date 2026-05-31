#include <iostream>
#include <memory>
#include <fstream>
#include "./car.h"

int main(int argsc, char* argsv[]){

  const int CAR_NUM = 2;

  std::unique_ptr<car> car_arr[CAR_NUM] = {
    std::make_unique<car>(0,0,0),
    std::make_unique<car>(1,10,30),
  };

  float dt = 0.01;
  int runs = 1000;

  if (argsc == 2){
    runs = std::atoi(argsv[1]);
  }
  
  if (argsc == 3){
    runs = std::atoi(argsv[1]);
    dt = std::atof(argsv[2]);
  }
  std::ofstream speed_file("speed_data.csv");
  std::ofstream acc_file("acc_data.csv");
  std::ofstream coord_file("coord_data.csv");

  speed_file << "time,speed 1,speed 2\n";
  acc_file << "time,acc 1,acc 2\n";
  coord_file << "time,crash,dist\n";

  float time = 0;

  for(int step = 0; step < runs; step++){

    for(int car_index = 0; car_index < (CAR_NUM - 1); car_index++){
      car_arr[car_index]->move(car_arr[car_index+1],dt);
    }

    car_arr[CAR_NUM-1]->move_unobstructed(dt);
    time += 0.1;

    speed_file << time << ",";
    for (int i = 0; i < CAR_NUM;i++){
      speed_file << car_arr[i]->get_speed() << ",";
    }

    acc_file << time << ",";
    for (int i = 0; i < CAR_NUM;i++){
	 acc_file << car_arr[i]->get_acc() << ",";
    }

    coord_file << time << ",";
    if(car_arr[0]->get_coord() < car_arr[1]->get_coord()){
      coord_file << "Safe,";
    }
    else{
      coord_file << "Crash,";
    }

    coord_file << car_arr[1]->get_coord() - car_arr[0]->get_coord() << "\n";

    speed_file << "\b \n";
    acc_file << "\b \n";
  }
  acc_file.close();
  speed_file.close();
  coord_file.close();

}
