#include <NetworkController.h>

#include "esp_camera.h"
#include "esp_timer.h"
#include "img_converters.h"
#include "Arduino.h"
#include "fb_gfx.h"
#include "soc/soc.h"          //disable brownout problems
#include "soc/rtc_cntl_reg.h" //disable brownout problems
#include "esp_http_server.h"

#define PART_BOUNDARY "123456789000000000000987654321"
#include "cam_headers.h"

#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

class CameraController
{
  httpd_handle_t stream_httpd = NULL;

  static const char *_STREAM_CONTENT_TYPE;
  static const char *_STREAM_BOUNDARY;
  static const char *_STREAM_PART;

  static esp_err_t stream_handler(httpd_req_t *req);

  void startCameraServer();

public:
  NetworkController *p_network;

  CameraController();
  void setup(NetworkController *p_network);
  void loop();
};

#endif