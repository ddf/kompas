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
  T, O, O, O,   O, O, O, O,   T, O, O, O,   O, O, O, O,
  T, O, O, O,   O, O, O, O,   O, O, T, O,   O, O, O, O,
  T, O, O, O,   O, O, T, O,   O, O, T, O,   O, O, O, O,
  T, O, O, O,   T, O, O, O,   T, O, O, O,   T, O, O, O,
  T, O, O, T,   O, O, T, O,   O, O, T, O,   O, O, T, O,
  T, O, O, T,   O, O, T, O,   O, T, O, O,   T, O, O, T,
  T, O, O, T,   O, O, T, O,   T, O, O, T,   O, O, T, O,
  T, O, T, O,   O, T, O, O,   T, O, O, T,   O, T, T, O,
};

// ALTITUDE - snare patterns
constexpr int data1[kPatternCount * kPatternLength] = {
  O, O, O, O,   T, O, O, O,   O, O, O, O,   T, O, O, O,
  O, O, O, O,   T, O, O, T,   O, O, O, O,   T, O, O, O,
  O, O, O, O,   T, O, O, O,   O, O, T, O,   T, O, O, O,
  O, O, O, O,   T, O, O, T,   O, O, T, O,   T, O, O, O,
  O, O, O, T,   O, O, T, O,   O, O, T, O,   T, O, O, O,
  O, O, O, T,   O, O, T, O,   O, T, O, O,   T, T, O, O,
  O, O, O, T,   O, O, T, T,   O, O, T, O,   T, O, O, T,
  O, O, O, T,   O, O, T, O,   O, T, O, T,   O, O, T, T,
};

// LATITUDE - hat / perc patterns
// starting with the six distinguished rhythm timelines 
// see: Toussaint, Godfried T., The Geometry of Musical Rhythm, Chapter 7 
constexpr int data2[kPatternCount * kPatternLength] = {
  T, O, O, O,   T, O, T, O,   O, O, T, O,   T, O, O, O, // SHIKO
  T, O, O, T,   O, O, T, O,   O, O, T, O,   T, O, O, O, // SON
  T, O, O, T,   O, O, T, O,   O, O, T, T,   O, O, O, O, // SOUKOUS
  T, O, O, T,   O, O, T, O,   O, O, T, O,   O, O, T, O, // GAHU
  T, O, O, T,   O, O, O, T,   O, O, T, O,   T, O, O, O, // RUMBA
  T, O, O, T,   O, O, T, O,   O, O, T, O,   O, T, O, O, // BOSSA-NOVA
  T, O, T, O,   T, O, T, O,   T, O, T, O,   T, O, T, O, // STRAIGHT EIGHTS
  T, O, T, T,   T, O, T, T,   T, O, T, T,   T, O, T, T, // SHUFFLE
};
 
#endif // _DATA_H_