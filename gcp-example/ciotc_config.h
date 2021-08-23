/******************************************************************************
 * Copyright 2018 Google
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/
// This file contains your configuration used to connect to Cloud IoT Core

// Important!
// TODO(you): Install root certificate to verify tls connection as described
// in https://www.hackster.io/arichetta/add-ssl-certificates-to-mkr1000-93c89d

#include "arduino_secrets.h"

// Wifi network details.
const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;

// Cloud iot details.
const char* project_id = SECRET_PROJECT_ID;
const char* location = SECRET_CLOUD_REGION;
const char* registry_id = SECRET_REGISTRY_ID;
const char* device_id = SECRET_DEVICE_ID;
// Time (seconds) to expire token += 20 minutes for drift
const int jwt_exp_secs = 3600; // Maximum 24H (3600*24)

// In case we ever need extra topics
const int ex_num_topics = 0;
const char* ex_topics[ex_num_topics];
//const int ex_num_topics = 1;
//const char* ex_topics[ex_num_topics] = {
//  "/devices/my-device/tbd/#"
//};
