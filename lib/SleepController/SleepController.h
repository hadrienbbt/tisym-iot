#include <NetworkController.h>

#ifndef SLEEP_CONTROLLER_H
#define SLEEP_CONTROLLER_H

class SleepController
{
  NetworkController *p_network;
  uint64_t mask;
  uint8_t btn_0;
  uint8_t btn_1;
  uint8_t btn_2;
  uint8_t btn_3;
  uint8_t prog_btn;

public:
  SleepController(const uint64_t mask, const uint8_t btn_0, const uint8_t btn_1, const uint8_t btn_2, const uint8_t btn_3, const uint8_t prog_btn);
  void setup(NetworkController *p_networkController);

  void sleep();
};

#endif