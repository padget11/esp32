#ifndef ESP32Serial_h
#define ESP32Serial_h
class ESP32Serial
{
  public:
  void serial_setup();
  String floatToString(float var);
  void put_string_to_array(char m_array[]);
  String send_and_receive_values();
};
#endif
