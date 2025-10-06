#include <GL/glut.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define WIDTH 800
#define HEIGHT 600

class Quadrado {
public:
    float x, y;         // posição do centro
    float dx, dy;       // direção
    float r, g, b;      // cor
    float lado;         // tamanho (metade do lado para facilitar o cálculo)

    Quadrado() {
        lado = 10 + rand() % 20; // tamanho aleatório
        x = lado + rand() % (WIDTH - 2 * (int)lado);
        y = lado + rand() % (HEIGHT - 2 * (int)lado);
        dx = (rand() % 2 == 0 ? 1 : -1) * (2 + rand() % 4);
        dy = (rand() % 2 == 0 ? 1 : -1) * (2 + rand() % 4);
        r = (float)rand() / RAND_MAX;
        g = (float)rand() / RAND_MAX;
        b = (float)rand() / RAND_MAX;
    }

    void mover() {
        x += dx;
        y += dy;

        // colisão nas bordas
        if (x - lado <= 0 || x + lado >= WIDTH)
            dx = -dx;
        if (y - lado <= 0 || y + lado >= HEIGHT)
            dy = -dy;
    }

    void desenhar() {
        glColor3f(r, g, b);
        glBegin(GL_QUADS);
        glVertex2f(x - lado, y - lado); // Canto inferior esquerdo
        glVertex2f(x + lado, y - lado); // Canto inferior direito
        glVertex2f(x + lado, y + lado); // Canto superior direito
        glVertex2f(x - lado, y + lado); // Canto superior esquerdo
        glEnd();
    }

    // altera a cor aleatoriamente
    void mudarCor() {
        r = (float)rand() / RAND_MAX;
        g = (float)rand() / RAND_MAX;
        b = (float)rand() / RAND_MAX;
    }

    void aumentarTamanho() {
        if (lado < 100) lado += 2.0;
    }

    void diminuirTamanho() {
        if (lado > 5) lado -= 2.0;
    }
};

std::vector<Quadrado> quadrados;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto &q : quadrados) {
        q.desenhar();
    }

    glutSwapBuffers();
}

void idle() {
    for (auto &q : quadrados)
        q.mover();

    glutPostRedisplay();
}

void teclado(unsigned char tecla, int x, int y) {
    if (tecla == '+') {
        quadrados.push_back(Quadrado());
    } else if (tecla == '-' && !quadrados.empty()) {
        quadrados.pop_back();
    } else if (tecla == 'c' && !quadrados.empty()) {
        quadrados.back().mudarCor();
    } else if (tecla == 'l' && !quadrados.empty()) {
        quadrados.back().aumentarTamanho();
    } else if (tecla == 's' && !quadrados.empty()) {
        quadrados.back().diminuirTamanho();
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
    glutCreateWindow("Quadrados saltitantes - OpenGL");

    init();

    quadrados.push_back(Quadrado());

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(teclado);

    glutMainLoop();
    return 0;
}