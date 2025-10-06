#include <GL/glut.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define WIDTH 800
#define HEIGHT 600

class Triangulo {
public:
    float x, y;         // posição do centro
    float dx, dy;       // direção
    float r, g, b;      // cor
    float tamanho;      // tamanho do lado do triângulo equilátero

    Triangulo() {
        tamanho = 20 + rand() % 30; // tamanho aleatório
        x = tamanho + rand() % (WIDTH - 2 * (int)tamanho);
        y = tamanho + rand() % (HEIGHT - 2 * (int)tamanho);
        dx = (rand() % 2 == 0 ? 1 : -1) * (2 + rand() % 4);
        dy = (rand() % 2 == 0 ? 1 : -1) * (2 + rand() % 4);
        r = (float)rand() / RAND_MAX;
        g = (float)rand() / RAND_MAX;
        b = (float)rand() / RAND_MAX;
    }

    void mover() {
        x += dx;
        y += dy;

        if (x - tamanho <= 0 || x + tamanho >= WIDTH)
            dx = -dx;
        if (y - tamanho <= 0 || y + tamanho >= HEIGHT)
            dy = -dy;
    }

    void desenhar() {
        glColor3f(r, g, b);
        glBegin(GL_TRIANGLES);

        float h = tamanho * sqrt(3.0f) / 2.0f;
        float half_h = h / 2.0f;

        // vertice superior
        glVertex2f(x, y + half_h);

        // vertice inferior esquerdo
        glVertex2f(x - tamanho / 2.0f, y - half_h);

        // vertice inferior direito
        glVertex2f(x + tamanho / 2.0f, y - half_h);

        glEnd();
    }

    void mudarCor() {
        r = (float)rand() / RAND_MAX;
        g = (float)rand() / RAND_MAX;
        b = (float)rand() / RAND_MAX;
    }

    void aumentarTamanho() {
        if (tamanho < 150) tamanho += 3.0;
    }

    void diminuirTamanho() {
        if (tamanho > 10) tamanho -= 3.0;
    }
};

std::vector<Triangulo> triangulos;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto &t : triangulos) {
        t.desenhar();
    }

    glutSwapBuffers();
}

void idle() {
    for (auto &t : triangulos)
        t.mover();

    glutPostRedisplay();
}

void teclado(unsigned char tecla, int x, int y) {
    if (tecla == '+') {
        triangulos.push_back(Triangulo());
    } else if (tecla == '-' && !triangulos.empty()) {
        triangulos.pop_back();
    } else if (tecla == 'c' && !triangulos.empty()) {
        // altera a cor do ultimo triangulo adicionado
        triangulos.back().mudarCor();
    } else if (tecla == 'l' && !triangulos.empty()) {
        // aumenta o tamanho do ultimo triangulo adicionado
        triangulos.back().aumentarTamanho();
    } else if (tecla == 's' && !triangulos.empty()) {
        // diminui o tamanho do ultimo triangulo adicionado
        triangulos.back().diminuirTamanho();
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
    glutCreateWindow("Triângulos saltitantes - OpenGL");

    init();

    triangulos.push_back(Triangulo());

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(teclado);

    glutMainLoop();
    return 0;
}