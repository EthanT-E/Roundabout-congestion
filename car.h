#include <memory>
#include <iostream>
#include <fstream>
#include <string>

class car{
private:
    float speed_mps; // meters per second
    float coord, intial_coord; // coord on road 
    float total_time = 0;// time in seconds
    float length = 2;//Car length in meters
    float acc = 0;
    int id;

public:
  car(int Iid,float Icoord, float Ispeed = 0)
  /*
   * Description:
   *  Car constructor with speed.
   *
   * Parameters:
   *  Icoord(float):
   *	Intial displacement in meters
   *  Ispeed(float):
   *	initial speed of the car in mph.
   * */
  {
    speed_mps = (Ispeed/2.237);
    coord = Icoord;
    intial_coord = Icoord;
    id = Iid;
  }

  void move(std::unique_ptr<car> &ahead_car,bool save = false, float dt=0.1)
  /*
    Description:
      moves car in a time step
    
    Parameters:
      dt(float):
	The time step for the movement in seconds
  */
  // {
  //   float local_coord = coord + speed_mps*dt;
  //   float ahead_car_crash_zone = ahead_car->get_coord() - (ahead_car->get_length()/2);
  //   if (local_coord >= ahead_car_crash_zone){
  //     speed_mps = 0;
  //     coord = ahead_car_crash_zone - 0.2;
  //   }
  //   else{
  //     coord = local_coord;
  //   }
  //   total_time += dt;
  // }
  {
    speed_mps += acc*dt;
    float dist_to_eq = ahead_car->get_coord() - coord + 3;
    float ahead_speed = ahead_car->get_speed();
    acc = ((ahead_speed*ahead_speed) - (speed_mps*speed_mps))/(2*dist_to_eq);
    coord += speed_mps*dt;
    total_time += dt;
  }

  void move_unobstructed(float dt = 0.1){
    coord += speed_mps*dt;
    total_time += dt;
  }

  void print_info(){
    std::cout << "time: " << total_time << " coord: " << coord << " speed: " << speed_mps << std::endl;
  }

  float get_speed()
  {
    return speed_mps;
  }

  float get_disp()
  {
    return (coord-intial_coord);
  }
  float get_coord(){
    return coord;
  }
  float get_length(){
    return length;
  }
};
