#include <algorithm>
#include <bitset>
#include <cmath>
#include <ctime>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include "vehicle.h"

struct vehicle_pack {
    float ortho, angle;
    int slot, type, flag;
};

void set_num(int& n) {
    static int num = 0;
    if (num == 0)
        num = n;
    else
        n = num;
}

std::pair<int, int> get_r(int n) {
    std::vector<int> v;
    for (int i = 0; i < n; i++)
        v.push_back(i);
    std::shuffle(v.begin(), v.end(), std::mt19937(std::random_device()()));
    return {v[0], v[1]};
}

void paint(float& r1, float& g1, float& b1, float& r2, float& g2, float& b2) {
    r1 = float(rand()) / float(RAND_MAX);
    g1 = float(rand()) / float(RAND_MAX);
    b1 = float(rand()) / float(RAND_MAX);
    r2 = float(rand()) / float(RAND_MAX);
    g2 = float(rand()) / float(RAND_MAX);
    b2 = float(rand()) / float(RAND_MAX);
}

void draw(int type, float x, float y, float& ortho, int& flag, float& angle) {
    switch (type) {
        case 1: {
            spacecraft sc({x, y}, ortho);
            sc.draw();
            sc.zoom(ortho, flag);
            break;
        }
        case 2: {
            UFO u({x, y}, angle);
            u.draw();
            u.rotate(angle);
            break;
        }
        case 3: {
            car c({x, y});
            c.draw();
            break;
        }
    }
}

pair get_pos(int slot, int n) {
    if (slot < n / 2)
        return {-8, 10 - 38. / n * slot - 19. / n * 1.17};
    slot -= n / 2;
    return {8, 10 - 38. / n * slot - 19. / n * 1.17};
}

bool check(float x, int slot, int n) {
    if (slot < n / 2)
        return x >= 0;
    return x <= 0;
}

int find(std::bitset<20> b) {
    if (b.any() == 0)
        throw std::logic_error("NO parking slots");
    for (unsigned long i = 0; i < 20; i++) {
        if (b[i]) return (int)i;
    }
    return -1;
}

void glDraw() {
    static int ct = -1, n = 0;
    if (n == 0) set_num(n);
    static std::vector<vehicle_pack> v;
    static std::pair<int, int> tp = get_r(n);
    static float angle = 0, r1, g1, b1, r2, g2, b2;
    static bool br_open = true, br_start = false, cur_v;
    static float cur_x, cur_y, cur_ortho = 1, cur_angle = 0;
    static int cur_v_type, cur_v_slot, status = 1, cur_flag;  // 1 -> up 2 -> hor. / -1 -> down -2 -> hor.
    static std::bitset<20> ept((1 << n) - 1);
    ept[(unsigned long)tp.first] = false;
    ept[(unsigned long)tp.second] = false;
    v_parking_lot vpl(n);
    barrier br(angle);
    if (ct % 30 == 0) paint(r1, g1, b1, r2, g2, b2);
    teleported tele1(tp.first, n, r1, g1, b1), tele2(tp.second, n, r2, g2, b2);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (ct % 300 == 0) {
        int rand_num = rand();
        if ((rand_num % 3 && ept.any()) || v.empty()) {  // in
            cur_x = 0;
            cur_y = -13;
            cur_v = true;
            cur_v_type = rand() % 3 + 1;
            status = 1;
            cur_ortho = 1;
            cur_v_slot = find(ept);
            cur_flag = 1;
            cur_angle = 0;
            ept[(unsigned long)cur_v_slot] = false;
        } else {  // exit
            pair pos = get_pos(v.front().slot, n);
            cur_x = pos.first;
            cur_y = pos.second;
            cur_v = true;
            cur_v_type = v.front().type;
            status = -2;
            cur_ortho = v.front().ortho;
            cur_v_slot = v.front().slot;
            cur_flag = v.front().flag;
            cur_angle = v.front().angle;
            v.erase(v.begin());
            ept[(unsigned long)cur_v_slot] = true;
        }
        ct %= 300;
        br_open = true;
        angle = 0;
    }
    for (unsigned long i = 0; i < v.size(); i++) {
        pair pos = get_pos(v[i].slot, n);
        draw(v[i].type, pos.first, pos.second, v[i].ortho, v[i].flag, v[i].angle);
    }
    if ((br_open && ((status == 1) || (status == -1 && cur_y <= -5))) || br_start) {
        br.rotate(angle);
        br_start = true;
        if (angle < 0) br_open = false, br_start = false;
    }
    tele1.draw();
    tele2.draw();
    vpl.draw();
    br.draw();
    if (cur_v) {
        draw(cur_v_type, cur_x, cur_y, cur_ortho, cur_flag, cur_angle);
        switch (status) {
            case 1:
                cur_y += 0.15f;
                if (cur_y >= get_pos(cur_v_slot, n).second) status = 2;
                break;
            case 2:
                if (cur_v_slot < n / 2)
                    cur_x -= 0.1f;
                else
                    cur_x += 0.1f;
                if (fabsf(cur_x) >= fabsf(get_pos(cur_v_slot, n).first)) {
                    cur_v = false;
                    v.push_back({cur_ortho, cur_angle, cur_v_slot, cur_v_type, cur_flag});
                }
                break;
            case -1:
                cur_y -= 0.15f;
                if (cur_y <= -11) cur_v = false;
                break;
            case -2:
                if (cur_v_slot < n / 2)
                    cur_x += 0.1f;
                else
                    cur_x -= 0.1f;
                if (check(cur_x, cur_v_slot, n)) status = -1;
        }
    }
    glutSwapBuffers();
    glFlush();
    ct++;
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    double aspect = (double)w / (double)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-aspect * 10, aspect * 10, -10., 10., -1., 1.);
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void timer(int v) {
    glutTimerFunc(static_cast<unsigned int>(v), timer, v);
    glutPostRedisplay();
}

int main(int argc, char* argv[]) {
    int n;
    std::cout << "Enter the number of slots {12, 14, 16, 18}: ";
    std::cin >> n;
    if (n % 2 || n < 12 || n > 18) throw std::logic_error("The number of slots must be a even number in [12, 18]");
    set_num(n);
    srand((unsigned)time(nullptr));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutCreateWindow(argv[0]);
    init();
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(glDraw);
    glutReshapeFunc(reshape);
    glutTimerFunc(1000 / 30, timer, 1000 / 30);
    glutMainLoop();
    return 0;
}