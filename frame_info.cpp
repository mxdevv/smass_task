#ifndef __FRAME_INFO_CPP__
#define __FRAME_INFO_CPP__

class Frame_info
{
  using key_t = unsigned char[8];
  static constexpr key_t stat_check_key {
      11, 22, 33, 44, 55, 66, 77, 88 };

public:
  key_t check_key;
  int type, rows, cols;

  constexpr Frame_info();
  Frame_info(int type, int rows, int cols);

  bool checking();
};

constexpr Frame_info::key_t Frame_info::stat_check_key;

constexpr Frame_info::Frame_info()
  : check_key(), type(0), rows(0), cols(0)
{
  for(int i = 0; i < sizeof(key_t); i++) {
    check_key[i] = stat_check_key[i];
  }
}

Frame_info::Frame_info(int type, int rows, int cols)
  : Frame_info()
{
  this->type = type;
  this->rows = rows;
  this->cols = cols;
}

bool Frame_info::checking()
{
  for(int i = 0; i < sizeof(check_key); i++) {
    if (check_key[i] != stat_check_key[i]) {
      return false;
    }
  }
  return true;
}

#endif
