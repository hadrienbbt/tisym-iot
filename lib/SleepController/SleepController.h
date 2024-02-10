#include <NetworkController.h>

#ifndef SLEEP_CONTROLLER_H
#define SLEEP_CONTROLLER_H

class SleepController
{
public:
  NetworkController *p_networkController;
  uint64_t mask;

  SleepController(const uint64_t mask);
  void setup(NetworkController *p_networkController);
};

#endif