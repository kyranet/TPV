#pragma once
#include "ArkanoidBody.h"

class Block final : public ArkanoidBody {
  int color_;
  void setBody(float32 x, float32 y, float32 width, float32 height,
               b2World &world);

 public:
  Block();
  Block(float32 x, float32 y, float32 width, float32 height, int color,
        Texture *texture);
  ~Block();
  void update() override;
  void render() const override;
  void contact();
  void destroy() override;
  std::istream &deserialize(std::istream &out) override;
  std::ostream &serialize(std::ostream &is) const override;
  int getColor() const;
};
