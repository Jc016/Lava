
#ifndef LAVA_LINE_H
#define LAVA_LINE_H

class LavaLine{

  public:
  LavaLine();
  void reset();
  void process();
  void setId(int id);
  int _length;
  int _x;
  private:
  int _id;
  
};

#endif
