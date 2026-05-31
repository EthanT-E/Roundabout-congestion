#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

class car{
private:
    float speed_mps; // meters per second
    float coord, intial_coord; // coord on road
    float angle;// in radians
    float total_time = 0;// time in seconds
    float length = 2;//Car length in meters#
    float kp = 0.4;//responce to space error
    float kv = 1.2;//responce to speed error
    float desired_gap = 10;//metres
    float lin_acc = 0;
    
    bool on_round_about = false;

    const float speed_limit = 18; // about 40 mph
    const float roundabout_radius = 50;//metres
  
    int id;
    

public:
  car(int Iid,float Iangle, float Ispeed = 0)
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
    angle = Iangle;
    intial_coord = coord;
    id = Iid;
  }

  void move(std::unique_ptr<car> &ahead_car, float dt=0.1)
  /*
    Description:
      moves car in a time step

    Parameters:
      ahead car (std::unique_ptr<car> &):
	pointer to the ahead car object
      dt(float):
	The time step for the movement in seconds
  */
  {
    if(on_round_about){
      move_roundabout(ahead_car, dt);
    }
    else {
     striaght_move(ahead_car, dt);
    }
  }

  void striaght_move(std::unique_ptr<car> &ahead_car, float dt=0.1)
  /*
    Description:
      moves car in a time step

    Parameters:
      ahead car (std::unique_ptr<car> &):
	pointer to the ahead car object
      dt(float):
	The time step for the movement in seconds
  */
  {

    float dist_to_eq = ahead_car->get_coord() - coord;

    float ahead_speed = ahead_car->get_speed();

    lin_acc = kp * (dist_to_eq - desired_gap) + kv * (ahead_speed-speed_mps);

    if (speed_mps > (speed_limit*1.1)){
      lin_acc = (speed_limit - speed_mps)/(100);
    }

    const float maxAccel = 4.0;
    const float maxBrake = -9.8;

    if (lin_acc > maxAccel)
	lin_acc = maxAccel;

    if (lin_acc < maxBrake)
	lin_acc = maxBrake;

    speed_mps += lin_acc*dt;

    if(speed_mps < 0){
      speed_mps = 0;
    }

    coord += speed_mps*dt;
    total_time += dt;
  }

  void move_unobstructed(float dt = 0.1){
    coord += speed_mps*dt;
    total_time += dt;

    lin_acc = std::sin(total_time);

    /*
    if(speed_mps > speed_limit){
       lin_acc = (speed_limit-speed_mps)/dt;
    }
    */

    speed_mps += lin_acc*dt;

    if(speed_mps < 0){
      speed_mps = 0;
    }
  }

  void move_roundabout(std::unique_ptr<car> &ahead_car, float dt=0.1){

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
  float get_lin_acc(){
    return lin_acc;
  }
};
