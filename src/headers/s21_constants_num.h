#ifndef S21_CONSTANTS_NUM_H_
#define S21_CONSTANTS_NUM_H_

#define ZERO_DECIMAL \
  {                  \
    { 0, 0, 0, 0 }   \
  }

#define ZERO_MINUS_DECIMAL  \
  {                         \
    { 0, 0, 0, 0x80000000 } \
  }
#define ONE_DECIMAL \
  {                 \
    { 1, 0, 0, 0 }  \
  }

#define TWO_DECIMAL \
  {                 \
    { 2, 0, 0, 0 }  \
  }

#define THREE_DECIMAL \
  {                   \
    { 3, 0, 0, 0 }    \
  }

#define TEN_DECIMAL \
  {                 \
    { 10, 0, 0, 0 } \
  }

#define MAX_DECIMAL                           \
  {                                           \
    { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0 } \
  }

#define MIN_DECIMAL                                    \
  {                                                    \
    { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000 } \
  }

#define FULL_DECIMAL                                   \
  {                                                    \
    { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF } \
  }

#define ONE_BIG_DECIMAL \
  { ONE_DECIMAL, ZERO_DECIMAL }

#define ZERO_BIG_DECIMAL \
  { ZERO_DECIMAL, ZERO_DECIMAL }

#define FULL_BIG_DECIMAL \
  { FULL_DECIMAL, FULL_DECIMAL }

#define MAX_BIG_DECIMAL \
  { MAX_DECIMAL, MAX_DECIMAL }

#endif  // S21_CONSTANTS_NUM_H_
