#ifndef P3_FIGURE_H
#define P3_FIGURE_H

typedef std::pair<float, float> pair;  // float is enough and afterwards use glVertex2f

class figure {
  public:
    virtual ~figure() = default;
    virtual void draw() = 0;

  protected:
    float r{}, g{}, b{};
};

class line : public figure {
  public:
    line(pair pt1, pair pt2, float r, float g, float b);
    void draw() override;

  private:
    pair pt1, pt2;
};

class triangle : public figure {
  public:
    triangle(pair pt1, pair pt2, pair pt3, float r, float g, float b);
    void draw() override;

  private:
    pair pt1, pt2, pt3;
};

class quadrangle : public figure {
  public:
    quadrangle();  // for rect overriding
    quadrangle(pair pt1, pair pt2, pair pt3, pair pt4, float r, float g, float b);
    void draw() override;

  protected:
    pair pt1, pt2, pt3, pt4;
};

class rectangle : public quadrangle {
  public:
    rectangle(pair pt1, pair pt2, float r, float g, float b);
};

class circle : public figure {
  public:
    circle(pair center, float radius, float r, float g, float b);
    void draw() override;

  private:
    pair center;
    float radius;
};

class semicircle : public figure {
  public:
    semicircle(pair center, float angle, float radius, float r, float g, float b);
    void draw() override;

  private:
    pair center;
    float radius;
    float angle;
};

#endif  // P3_FIGURE_H
