#pragma once

struct color {
  short r;
  short g;
  short b;
  short a;

  color(short r, short g, short b, short a) : r(r), g(g), b(b), a(a) {}

  color(short r, short g, short b) : r(r), g(g), b(b), a(255) {}
};

const color RED = color(255, 0, 0);
const color GREEN = color(0, 255, 0);
const color BLUE = color(0, 0, 255);
const color BLACK = color(0, 0, 0);
const color WHITE = color(255, 255, 255);
const color BACKGROUND = color(16, 42, 97);
