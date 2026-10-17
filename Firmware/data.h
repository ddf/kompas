#ifndef _DATA_H_
#define _DATA_H_

constexpr int kPatternLength = 16;
constexpr int kPatternCount  = 8;
constexpr int T = 32; // always trigger this step
constexpr int F = 24;  // frequently trigger this step
constexpr int S = 16;  // sometimes trigger this step
constexpr int M =  8;  // maybe trigger this step
constexpr int R =  2;   // rarely trigger this step
constexpr int O =  0;    // never trigger this step

constexpr int data0[kPatternCount * kPatternLength] = {
  T, O, O, O,   T, O, O, O,   T, O, O, O,   T, O, O, O,
  T, O, O, O,   T, O, S, O,   T, O, O, O,   T, O, S, O,
  T, O, O, O,   S, O, T, O,   T, O, S, O,   S, O, T, O,
  T, O, O, S,   O, O, T, O,   T, O, S, S,   O, O, T, O,
  T, O, O, T,   O, O, T, O,   T, O, O, T,   O, R, T, O,
  T, O, O, T,   O, O, T, O,   O, T, O, O,   T, O, O, F,
  T, O, R, T,   M, O, T, O,   R, T, O, R,   T, O, M, F,
  T, O, S, T,   R, O, T, M,   M, T, O, M,   T, S, S, F,
};

#endif