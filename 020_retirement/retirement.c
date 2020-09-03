#include <stdio.h>
#include <stdlib.h>
double calculation(double currentSaving, double contribution, double rate);
struct _retire_info{
  int months;
  double contribution;
  double rate_of_return;
};
  typedef struct _retire_info retire_info;


void retirement (int startAge,   //in months
                 double initial, //initial savings in dollars
                 retire_info working, //info about working
                 retire_info retired) //info about being retired)
{
  double totalMoney = initial;
  int age = startAge;
  
  //print working info
  for (int i = 0; i < working.months; i++){
    printf("Age %3d month %2d you have $%.2lf\n", age / 12, age % 12, totalMoney);
     totalMoney = calculation(totalMoney, working.contribution, working.rate_of_return );
    
    age++;
  }
  //print retire info
  for (int i = 0; i < retired.months; i++){
    printf("Age %3d month %2d you have $%.2lf\n", age / 12, age % 12, totalMoney);
    totalMoney = calculation(totalMoney, retired.contribution, retired.rate_of_return );
    age++;
  }


  }


double calculation(double currentSaving,double contribution, double rate){
  double tempt =currentSaving + currentSaving * rate + contribution;
  return tempt;
  
}


int main(){

  retire_info working = {489, 1000.0, 0.045 / 12.0 };
  retire_info retired = {384, -4000.0, 0.01 / 12.0};
  retirement(327, 21345.0, working, retired );
  
  return 0;


}
