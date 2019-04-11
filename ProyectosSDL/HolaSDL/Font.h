#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include "Texture.h"

class Font {
 private:
  TTF_Font *_font = nullptr;
  SDL_Renderer *_renderer;
  Uint32 _size = 8;

 public:
  Font(){};
  Font(SDL_Renderer *renderer, string filename, int size);
  ~Font();
  TTF_Font *getFont() const;
  SDL_Renderer *getRenderer() const;
  void liberate();
  void load(string filename);
};
