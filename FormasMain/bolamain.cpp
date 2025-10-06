#include <GL/glut.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define WIDTH 800
#define HEIGHT 600

// ----------------------------
// Classe Bola
// ----------------------------
class Bola {
public:
    float x, y;         // posição
    float dx, dy;       // direção
    float r, g, b;      // cor
    float raio;         // tamanho

    Bola() {
        raio = 10 + rand() % 20; // tamanho aleatório
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

        // colisão nas bordas
        if (x - raio <= 0 || x + raio >= WIDTH)
            dx = -dx;
        if (y - raio <= 0 || y + raio >= HEIGHT)
            dy = -dy;
    }

    void desenhar() {
        glColor3f(r, g, b);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for (int i = 0; i <= 30; i++) {
            float ang = i * 2.0f * M_PI / 30;
            glVertex2f(x + cos(ang) * raio, y + sin(ang) * raio);
        }
        glEnd();
    }
};

// ----------------------------
// Variáveis globais
// ----------------------------
std::vector<Bola> bolas;

// ----------------------------
// Funções de exibição e controle
// ----------------------------
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto &b : bolas) {
        b.desenhar();
    }

    glutSwapBuffers();
}

void idle() {
    for (auto &b : bolas)
        b.mover();

    glutPostRedisplay();
}

void teclado(unsigned char tecla, int x, int y) {
    if (tecla == '+') {
        bolas.push_back(Bola());
    } else if (tecla == '-' && !bolas.empty()) {
        bolas.pop_back();
    }
}

// ----------------------------
// Inicialização
// ----------------------------
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
}

// ----------------------------
// Função principal
// ----------------------------
int main(int argc, char **argv) {
    srand(time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Bolas saltitantes - OpenGL");

    init();

    // adiciona uma bola inicial
    bolas.push_back(Bola());

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(teclado);

    glutMainLoop();
    return 0;
}

