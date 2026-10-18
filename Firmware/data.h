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

// LONGITUDE - kick patterns
constexpr int data0[kPatternCount * kPatternLength] = {
  T, O, O, O,   O, O, O, M,   T, O, O, O,   O, O, O, O,
  T, O, O, O,   O, O, S, O,   O, O, T, O,   O, O, O, O,
  T, O, O, M,   O, O, T, O,   O, O, T, O,   O, O, M, O,
  T, O, M, O,   T, O, O, O,   T, O, O, O,   T, O, O, M,
  T, O, O, T,   O, O, T, S,   O, O, T, O,   O, M, T, O,
  T, O, O, T,   M, O, T, O,   O, T, O, R,   T, O, O, T,
  T, M, O, T,   O, S, T, O,   T, O, O, T,   R, O, T, O,
  T, O, T, O,   S, T, O, M,   T, O, M, T,   O, T, T, M,
};

// ALTITUDE - snare patterns
constexpr int data1[kPatternCount * kPatternLength] = {
  O, O, O, O,   T, O, O, O,   O, O, O, O,   T, O, O, O,
  O, O, O, O,   T, O, O, T,   O, M, O, O,   T, O, O, O,
  O, O, O, O,   T, O, O, O,   O, O, T, O,   T, M, O, O,
  O, O, O, O,   T, O, O, T,   O, M, T, O,   T, O, M, O,
  O, O, O, T,   O, M, T, O,   O, O, T, O,   T, O, O, O,
  O, O, O, T,   O, O, T, M,   O, T, O, O,   T, T, M, O,
  O, O, O, T,   O, O, T, T,   O, O, T, O,   T, O, O, T,
  O, O, M, T,   O, M, T, O,   O, T, M, T,   R, M, T, T,
};

// LATITUDE - hat / perc patterns
// starting with the six distinguished rhythm timelines 
// see: Toussaint, Godfried T., The Geometry of Musical Rhythm, Chapter 7 
constexpr int data2[kPatternCount * kPatternLength] = {
  T, O, O, M,   T, O, T, O,   O, M, T, O,   T, O, O, M, // SHIKO
  T, O, M, T,   O, M, T, O,   O, M, T, O,   T, O, O, M, // SON
  T, O, M, T,   O, M, T, O,   O, M, T, T,   O, O, M, R, // SOUKOUS
  T, O, M, T,   O, M, T, O,   O, M, T, O,   O, M, T, O, // GAHU
  T, O, M, T,   O, O, M, T,   O, M, T, O,   T, O, O, M, // RUMBA
  T, O, R, T,   O, M, T, O,   O, M, T, O,   R, T, O, M, // BOSSA-NOVA
  T, R, T, M,   T, R, T, M,   T, M, T, R,   T, R, T, M, // STRAIGHT EIGHTS
  T, M, T, T,   T, M, T, T,   T, M, T, T,   T, M, T, T, // SHUFFLE
};
 
#endif // _DATA_H_