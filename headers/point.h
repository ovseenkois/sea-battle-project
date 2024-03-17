#ifndef POINT_H
#define POINT_H



struct Point {
  int x_;
  int y_;
  Point() = default;
  Point(int x, int y) : x_(x), y_(y) {
  }
};
#endif