#include <NetworkController.h>

#ifndef SLEEP_CONTROLLER_H
#define SLEEP_CONTROLLER_H

class SleepController
{
  uint64_t mask;

public:
  SleepController(const uint64_t mask);
  void setup(NetworkController *p_networkController);
};

#endif