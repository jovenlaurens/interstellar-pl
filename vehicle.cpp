#include "vehicle.h"

#include <cmath>
#include <iostream>

#define pi 3.1415926535897932384626434f

vehicle::~vehicle() = default;

teleported::teleported(int slot, int n, float r, float g, float b) {
    float offset = 0.3f;
    if (slot < n / 2) {
        rect = new rectangle({-10 + offset, 10. - 38. / n * slot - offset}, {-10 + 6 - offset, 10. - 38. / n * (slot + 1) + offset}, r, g, b);
    } else {
        int temp = slot - n / 2;
        rect = new rectangle({10 - offset, 10. - 38. / n * temp - offset}, {10 - 6 + offset, 10. - 38. / n * (temp + 1) + offset}, r, g, b);
    }
}

teleported::~teleported() {
    delete rect;
}

void teleported::draw() {
    rect->draw();
}

UFO::UFO(pair pos, float angle) {
    this->center = pos;
    float theta = angle / 180 * pi;
    fig[0] = new line(center, {center.first + 1.2f * cosf(pi / 4 + theta), center.second + 1.2f * sinf(pi / 4 + theta)}, 1, 0.502f, 0);
    fig[1] = new line(center, {center.first + 1.2f * cosf(3 * pi / 4 + theta), center.second + 1.2f * sinf(3 * pi / 4 + theta)}, 1, 0.502f, 0);
    fig[2] = new semicircle(center, angle, 1, 0, 0, 1);
    fig[3] = new quadrangle({center.first + 0.2f * cosf(pi + theta), center.second + 0.2f * sinf(pi + theta)}, {center.first + 0.8f * cosf(pi + theta), center.second + 0.8f * sinf(pi + theta)}, {center.first + 0.873f * cosf(0.231f + pi + theta), center.second + 0.873f * sinf(0.231f + pi + theta)}, {center.first + 0.25f * cosf(0.927f + pi + theta), center.second + 0.25f * sinf(0.927f + pi + theta)}, 0.965f, 0.922f, 0.161f);
    fig[4] = new quadrangle({center.first + 0.2f * cosf(theta), center.second + 0.2f * sinf(theta)}, {center.first + 0.8f * cosf(theta), center.second + 0.8f * sinf(theta)}, {center.first + 0.873f * cosf(-0.231f + theta), center.second + 0.873f * sinf(-0.231f + theta)}, {center.first + 0.25f * cosf(-0.927f + theta), center.second + 0.25f * sinf(-0.927f + theta)}, 0.965f, 0.922f, 0.161f);
}

UFO::~UFO() {
    for (int i = 0; i < 5; i++) delete fig[i];
}

void UFO::draw() {
    for (int i = 0; i < 5; i++) fig[i]->draw();
}

void UFO::rotate(float &angle) {
    angle += 1;
    if (angle > 360) angle -= 360;
}

spacecraft::spacecraft(pair pos, float o) {
    this->center = pos;
    this->ortho = o;
    fig[0] = new rectangle({center.first - 0.4 * o, center.second + o}, {center.first + 0.4 * o, center.second - o}, 1, 1, 0);
    fig[1] = new triangle({center.first - 0.4 * o, center.second + o}, {center.first - 0.4 * o, center.second - o}, {center.first - 0.8 * o, center.second - o}, 1, 0.6f, 0);
    fig[2] = new triangle({center.first + 0.4 * o, center.second + o}, {center.first + 0.4 * o, center.second - o}, {center.first + 0.8 * o, center.second - o}, 1, 0.6f, 0);
    fig[3] = new triangle({center.first - 0.4 * o, center.second + o}, {center.first + 0.4 * o, center.second + o}, {center.first, center.second + 1.6 * o}, 0, 1, 0);
    fig[4] = new quadrangle({center.first - 0.4 * o, center.second - o}, {center.first + 0.4 * o, center.second - o}, {center.first + 0.35 * o, center.second - 1.1 * o}, {center.first - 0.35 * o, center.second - 1.1 * o}, 0, 0, 0);
    fig[5] = new rectangle({center.first - 0.05 * o, center.second + 0.3 * o}, {center.first + 0.05 * o, center.second + 0.5 * o}, 0, 0.682f, 0.937f);
    fig[6] = new rectangle({center.first - 0.25 * o, center.second + 0.7 * o}, {center.first - 0.15 * o, center.second + 0.8 * o}, 0.925f, 0, 0.549f);
    fig[7] = new rectangle({center.first + 0.15 * o, center.second + 0.7 * o}, {center.first + 0.25 * o, center.second + 0.8 * o}, 0.925f, 0, 0.549f);
}

spacecraft::~spacecraft() {
    for (int i = 0; i < 8; i++) delete fig[i];
}

void spacecraft::draw() {
    for (int i = 0; i < 8; i++) fig[i]->draw();
}

void spacecraft::zoom(float &_ortho, int &flag) const {
    if (_ortho >= 1.05) flag = 0;
    if (_ortho <= 0.8) flag = 1;
    if (flag)
        _ortho = ortho + 0.01f;
    else
        _ortho = ortho - 0.02f;
    if (_ortho >= 1.05) flag = 0;
    if (_ortho <= 0.8) flag = 1;
}

car::car(pair pos) {
    this->center = pos;
    this->fig[0] = new quadrangle({center.first - 1.2, center.second + 0.5}, {center.first + 1.2, center.second + 0.5}, {center.first + 1, center.second + 1.2}, {center.first - 1, center.second + 1.2}, 0.545f, 0.569f, 0.976f);
    this->fig[1] = new rectangle({center.first - 1.6, center.second + 0.5}, {center.first + 1.6, center.second - 0.5}, 0.902f, 0.894f, 0.471f);
    this->fig[2] = new circle({center.first - 1, center.second - 0.4}, 0.4f, 0.949f, 0.580f, 0.565f);
    this->fig[3] = new circle({center.first + 1, center.second - 0.4}, 0.4f, 0.949f, 0.580f, 0.565f);
}

car::~car() {
    for (int i = 0; i < 4; i++) delete fig[i];
}

void car::draw() {
    for (int i = 0; i < 4; i++) fig[i]->draw();
}

v_parking_lot::v_parking_lot(int n) {
    this->n = n;
    l[0] = new line({-10, 10}, {-10, -9}, 0.5f, 0.5f, 0.5f);
    l[1] = new line({10, 10}, {10, -9}, 0.5f, 0.5f, 0.5f);
    for (int i = 0; i <= n / 2; i++) {
        l[2 * i + 2] = new line({-10, 10 - 38. / n * i}, {-10 + 5, 10 - 38. / n * i}, 0.5f, 0.5f, 0.5f);
        l[2 * i + 3] = new line({10, 10 - 38. / n * i}, {10 - 5, 10 - 38. / n * i}, 0.5f, 0.5f, 0.5f);
    }
}

v_parking_lot::~v_parking_lot() {
    for (int i = 0; i < n + 4; i++) delete l[i];
}

void v_parking_lot::draw() {
    for (int i = 0; i < n + 4; i++) l[i]->draw();
}

barrier::barrier(float angle) {
    float offset = 0.2f;
    this->angle = angle;
    l[0] = new line({-5, -10 + offset}, {-5 + 3.4 * cosf(angle), -10 + offset + 5 * sinf(angle)}, 1, 0.5f, 0.5f);
    l[1] = new line({5, -10 + offset}, {5 - 3.4 * cosf(angle), -10 + offset + 5 * sinf(angle)}, 1, 0.5f, 0.5f);
}

barrier::~barrier() {
    delete l[0];
    delete l[1];
}

void barrier::draw() {
    l[0]->draw();
    l[1]->draw();
}

void barrier::rotate(float &_angle) const {
    static bool flag = true;
    if (flag)
        _angle = angle + 0.01f;
    else
        _angle = angle - 0.01f;
    if (_angle > 0.36) flag = false;
    if (_angle < 0) flag = true;
}
