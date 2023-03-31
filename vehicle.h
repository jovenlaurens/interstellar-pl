#ifndef P3_V_VEHICLE_H
#define P3_V_VEHICLE_H

#include <utility>

#include "figure.h"

typedef std::pair<float, float> pair;

class v_parking_lot {
  public:
    v_parking_lot(int n);
    ~v_parking_lot();
    void draw();

  private:
    int n;
    line *l[24];
};

class barrier {
  public:
    barrier(float angle = 0);
    ~barrier();
    void draw();
    void rotate(float &_angle) const;

  private:
    float angle;
    line *l[2];
};

class vehicle {
  public:
    virtual ~vehicle();
    virtual void draw() = 0;

  protected:
    pair center;
};

class teleported : public vehicle {
  public:
    teleported(int slot, int n, float r, float g, float b);
    ~teleported() override;
    void draw() override;

  private:
    rectangle *rect;
};

class UFO : public vehicle {
  public:
    UFO(pair pos, float angle);
    ~UFO() override;
    void draw() override;
    void rotate(float &angle);

  private:
    figure *fig[5];
};

class spacecraft : public vehicle {
  public:
    spacecraft(pair pos, float ortho);
    ~spacecraft() override;
    void draw() override;
    void zoom(float &_ortho, int &flag) const;

  private:
    figure *fig[8];
    float ortho;
};

class car : public vehicle {
  public:
    car(pair pos);
    ~car() override;
    void draw() override;

  private:
    figure *fig[4];
};

#endif  // P3_V_VEHICLE_H
