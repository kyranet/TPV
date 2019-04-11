#pragma once

#include "ArkanoidBody.h"
#include "checkML.h"

class Award : public ArkanoidBody {
 private:
  Uint32 _framerate;
  Uint32 _frame;
  b2Timer *_animationTimer;
  float32 _speed;
  bool _contacted;
  void setBody(float32 x, float32 y, float32 width, float32 height,
               b2World &world);

 public:
  Award() { _animationTimer = new b2Timer(); };
  Award(float32 x, float32 y, float32 width, float32 height, float32 speed,
      Uint32 framerate, Texture *texture);
  ~Award();
  virtual void update();
  virtual void render() const;
  virtual void contact();
  virtual void destroy();
  virtual void afterUpdate();
  virtual void onBeginContact(RigidBody *rigidbody);
  virtual std::istream &deserialize(std::istream &out);
  virtual std::ostream &serialize(std::ostream &is) const;
  int getFramerate() const { return _framerate; };
};