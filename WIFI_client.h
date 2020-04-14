#ifndef WIFI_client_h
#define WIFI_client_h

class Wifi_client
{
  public:
    void setup_WIFI_client();
    String httpGETRequest(const char* serverName);
};

#endif
