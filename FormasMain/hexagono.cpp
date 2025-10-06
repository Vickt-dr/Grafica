#include <GL/glut.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define WIDTH 800
#define HEIGHT 600

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Hexagono {
public:
    float x, y;         // posição do centro
    float dx, dy;       // direção
    float r, g, b;      // cor
    float raio;         // raio do hexágono (distância do centro ao vértice)

    Hexagono() {
        raio = 15 + rand() % 25; 
        x = raio + rand() % (WIDTH - 2 * (int)raio);
        y = raio + rand() % (HEIGHT - 2 * (int)raio);
        dx = (rand() % 2 == 0 ? 1 : -1) * (2 + rand() % 4);
        dy = (rand() % 2 == 0 ? 1 : -1) * (2 + rand() % 4);
        r = (float)rand() / RAND_MAX;
        g = (float)rand() / RAND_MAX;
        b = (float)rand() / RAND_MAX;
    }

    void mover() {
        x += dx;
        y += dy;

        if (x - raio <= 0 || x + raio >= WIDTH)
            dx = -dx;
        if (y - raio <= 0 || y + raio >= HEIGHT)
            dy = -dy;
    }

    void desenhar() {
        glColor3f(r, g, b);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y); 

        for (int i = 0; i <= 6; i++) {
            float ang = i * 2.0f * M_PI / 6;
            glVertex2f(x + cos(ang) * raio, y + sin(ang) * raio);
        }
        glEnd();
    }

    void mudarCor() {
        r = (float)rand() / RAND_MAX;
        g = (float)rand() / RAND_MAX;
        b = (float)rand() / RAND_MAX;
    }

    void aumentarTamanho() {
        if (raio < 100) raio += 2.0;
    }

    void diminuirTamanho() {
        if (raio > 7) raio -= 2.0;
    }
};

std::vector<Hexagono> hexagonos;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto &h : hexagonos) {
        h.desenhar();
    }

    glutSwapBuffers();
}

void idle() {
    for (auto &h : hexagonos)
        h.mover();

    glutPostRedisplay();
}

void teclado(unsigned char tecla, int x, int y) {
    if (tecla == '+') {
        hexagonos.push_back(Hexagono());
    } else if (tecla == '-' && !hexagonos.empty()) {
        hexagonos.pop_back();
    } else if (tecla == 'c' && !hexagonos.empty()) {
        // altera a cor do ultimo hexagono adicionado
        hexagonos.back().mudarCor();
    } else if (tecla == 'l' && !hexagonos.empty()) {
        // aumenta o tamanho do ultimo hexagono adicionado
        hexagonos.back().aumentarTamanho();
    } else if (tecla == 's' && !hexagonos.empty()) {
        // diminui o tamanho do ultimo hexagono adicionado
        hexagonos.back().diminuirTamanho();
    }
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
}

int main(int argc, char **argv) {
    srand(time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Hexágonos saltitantes - OpenGL");

    init();

    hexagonos.push_back(Hexagono());

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(teclado);

    glutMainLoop();
    return 0;
}