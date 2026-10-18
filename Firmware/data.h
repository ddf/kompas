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
  T, O, O, O,   O, O, O, R,   T, O, O, O,   O, O, O, O,
  T, O, O, O,   O, O, R, O,   O, O, T, O,   O, O, O, O,
  T, O, O, R,   O, O, T, O,   O, O, T, O,   O, O, M, O,
  T, O, R, O,   T, O, O, O,   T, O, O, O,   T, O, O, R,
  T, O, O, T,   O, O, T, S,   O, O, T, O,   O, R, T, O,
  T, O, O, T,   O, O, T, O,   O, T, O, R,   T, O, O, T,
  T, M, O, T,   O, R, T, O,   T, O, O, T,   R, O, T, O,
  T, O, T, O,   R, T, O, R,   T, O, R, T,   O, T, T, R,
};

// ALTITUDE - snare patterns
constexpr int data1[kPatternCount * kPatternLength] = {
  O, O, O, O,   T, O, O, O,   O, O, O, O,   T, O, O, O,
  O, O, O, O,   T, O, O, T,   O, R, O, O,   T, O, O, O,
  O, O, O, O,   T, O, O, O,   O, O, T, O,   T, M, O, O,
  O, O, O, O,   T, O, O, T,   O, R, T, O,   T, O, M, O,
  O, O, O, T,   O, R, T, O,   O, O, T, O,   T, O, O, O,
  O, O, O, T,   O, O, T, R,   O, T, O, O,   T, T, M, O,
  O, O, O, T,   O, O, T, T,   O, O, T, O,   T, O, O, T,
  O, O, R, T,   O, R, T, O,   O, T, R, T,   R, R, T, T,
};

// LATITUDE - hat / perc patterns
// starting with the six distinguished rhythm timelines 
// see: Toussaint, Godfried T., The Geometry of Musical Rhythm, Chapter 7 
constexpr int data2[kPatternCount * kPatternLength] = {
  T, O, O, R,   T, O, T, O,   O, R, T, O,   T, O, O, R, // SHIKO
  T, O, R, T,   O, R, T, O,   O, R, T, O,   T, O, O, R, // SON
  T, O, R, T,   O, R, T, O,   O, R, T, T,   O, O, R, R, // SOUKOUS
  T, O, R, T,   O, R, T, O,   O, R, T, O,   O, R, T, O, // GAHU
  T, O, R, T,   O, O, R, T,   O, R, T, O,   T, O, O, R, // RUMBA
  T, O, R, T,   O, R, T, O,   O, R, T, O,   R, T, O, R, // BOSSA-NOVA
  T, R, T, M,   T, R, T, R,   T, R, T, R,   T, R, T, R, // STRAIGHT EIGHTS
  T, R, T, T,   T, R, T, T,   T, R, T, T,   T, R, T, T, // SHUFFLE
};
 
#endif // _DATA_H_