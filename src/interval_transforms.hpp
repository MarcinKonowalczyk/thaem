// #pragma once
#ifndef INTERVAL_TRANSFORMS_HPP
#define INTERVAL_TRANSFORMS_HPP

// https://www.youtube.com/watch?v=mr5xkf6zSzk

inline float slowStart2(float x) { return x*x; }
inline float slowStart3(float x) { return x*x*x; }
inline float slowStart4(float x) { return x*x*x*x; }

inline float fastStart2(float x) { return 1-(1-x)*(1-x); }
inline float fastStart3(float x) { return 1-(1-x)*(1-x)*(1-x); }
inline float fastStart4(float x) { return 1-(1-x)*(1-x)*(1-x)*(1-x); }

// Sharp ramps

// Ramp or reverse ramp in a half, zero otherwise
inline float firstHalf(float x)           { return (x > 0.5) ? 0.0   : 2*x;   }
inline float secondHalf(float x)          { return (x > 0.5) ? 2*x-1 : 0.0;   }
// inline float firstHalfBackwards(float x)  { return (x > 0.5) ? 0.0   : 1.0-2*x; }
inline float secondHalfBackwards(float x) { return (x > 0.5) ? 2-2*x : 0.0;   }

// TODO: Explain this better
// Ramp or reverse ramp in a half, held/preemptive one/zero otherwise
inline float firstHalfHold(float x)           { return (x > 0.5) ? 1.0   : 2*x;   }
inline float secondHalfHold(float x)          { return (x > 0.5) ? 2*x-1 : 0.0;   }
inline float firstHalfHoldBackwards(float x)  { return (x > 0.5) ? 0.0   : 1-2*x; }
inline float secondHalfHoldBackwards(float x) { return (x > 0.5) ? 2-2*x : 1.0;   }

// Ramp bac and forth
inline float backAndForth(float x) { return (x > 0.5) ? 2-2*x  : 2*x; }
inline float forthAndBack(float x) { return (x > 0.5) ? x*2-1 : 1-2*x; }

inline float mix(float x, float y, float alpha) { return (1.0-alpha)*x + alpha*y; }

#endif /* INTERVAL_TRANSFORMS_HPP */