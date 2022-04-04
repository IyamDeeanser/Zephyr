#ifndef PID_H
#define PID_H

class PID{
public:
  float error = 0;
  float lastError = 0;
  float totalError = 0;
  float P = 0, I = 0, D = 0;
  float Output = 0;

//   PID()
//   : error(0), lastError(0), totalError(0), P(0), I(0), D(0), Output(0) {
//   }
};

#endif