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

enum class TipoObjeto { BOLA, QUADRADO, TRIANGULO, HEXAGONO };

class Bola {
public:
    float x, y;         // posiçao
    float dx, dy;       // direçao
    float r, g, b;      // cor
    float raio;         // tamanho

    Bola() {
        raio = 10 + rand() % 20;
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
        if (x - raio <= 0 || x + raio >= WIDTH) dx = -dx;
        if (y - raio <= 0 || y + raio >= HEIGHT) dy = -dy;
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

    void mudarCor() {
        r = (float)rand() / RAND_MAX;
        g = (float)rand() / RAND_MAX;
        b = (float)rand() / RAND_MAX;
    }
    void aumentarTamanho() { if (raio < 100) raio += 2.0; }
    void diminuirTamanho() { if (raio > 5) raio -= 2.0; }
};

// classe quadrado
class Quadrado {
public:
    float x, y, dx, dy, r, g, b, lado;
    Quadrado() {
        lado = 10 + rand() % 20;
        x = lado + rand() % (WIDTH - 2 * (int)lado);
        y = lado + rand() % (HEIGHT - 2 * (int)lado);
        dx = (rand() % 2 == 0 ? 1 : -1) * (2 + rand() % 4);
        dy = (rand() % 2 == 0 ? 1 : -1) * (2 + rand() % 4);
        r = (float)rand() / RAND_MAX; g = (float)rand() / RAND_MAX; b = (float)rand() / RAND_MAX;
    }
    void mover() {
        x += dx; y += dy;
        if (x - lado <= 0 || x + lado >= WIDTH) dx = -dx;
        if (y - lado <= 0 || y + lado >= HEIGHT) dy = -dy;
    }
    void desenhar() {
        glColor3f(r, g, b); glBegin(GL_QUADS);
        glVertex2f(x - lado, y - lado); glVertex2f(x + lado, y - lado); 
        glVertex2f(x + lado, y + lado); glVertex2f(x - lado, y + lado); 
        glEnd();
    }
    void mudarCor() { r = (float)rand() / RAND_MAX; g = (float)rand() / RAND_MAX; b = (float)rand() / RAND_MAX; }
    void aumentarTamanho() { if (lado < 100) lado += 2.0; }
    void diminuirTamanho() { if (lado > 5) lado -= 2.0; }
};

// classe triangulo
class Triangulo {
public:
    float x, y, dx, dy, r, g, b, tamanho;
    Triangulo() {
        tamanho = 20 + rand() % 30;
        x = tamanho + rand() % (WIDTH - 2 * (int)tamanho);
        y = tamanho + rand() % (HEIGHT - 2 * (int)tamanho);
        dx = (rand() % 2 == 0 ? 1 : -1) * (2 + rand() % 4);
        dy = (rand() % 2 == 0 ? 1 : -1) * (2 + rand() % 4);
        r = (float)rand() / RAND_MAX; g = (float)rand() / RAND_MAX; b = (float)rand() / RAND_MAX;
    }
    void mover() {
        x += dx; y += dy;
        if (x - tamanho <= 0 || x + tamanho >= WIDTH) dx = -dx;
        if (y - tamanho <= 0 || y + tamanho >= HEIGHT) dy = -dy;
    }
    void desenhar() {
        glColor3f(r, g, b); glBegin(GL_TRIANGLES);
        float h = tamanho * sqrt(3.0f) / 2.0f; float half_h = h / 2.0f;
        glVertex2f(x, y + half_h); 
        glVertex2f(x - tamanho / 2.0f, y - half_h); 
        glVertex2f(x + tamanho / 2.0f, y - half_h); 
        glEnd();
    }
    void mudarCor() { r = (float)rand() / RAND_MAX; g = (float)rand() / RAND_MAX; b = (float)rand() / RAND_MAX; }
    void aumentarTamanho() { if (tamanho < 150) tamanho += 3.0; }
    void diminuirTamanho() { if (tamanho > 10) tamanho -= 3.0; }
};

// classe hexagono
class Hexagono {
public:
    float x, y, dx, dy, r, g, b, raio;
    Hexagono() {
        raio = 15 + rand() % 25;
        x = raio + rand() % (WIDTH - 2 * (int)raio);
        y = raio + rand() % (HEIGHT - 2 * (int)raio);
        dx = (rand() % 2 == 0 ? 1 : -1) * (2 + rand() % 4);
        dy = (rand() % 2 == 0 ? 1 : -1) * (2 + rand() % 4);
        r = (float)rand() / RAND_MAX; g = (float)rand() / RAND_MAX; b = (float)rand() / RAND_MAX;
    }
    void mover() {
        x += dx; y += dy;
        if (x - raio <= 0 || x + raio >= WIDTH) dx = -dx;
        if (y - raio <= 0 || y + raio >= HEIGHT) dy = -dy;
    }
    void desenhar() {
        glColor3f(r, g, b); glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y); 
        for (int i = 0; i <= 6; i++) {
            float ang = i * 2.0f * M_PI / 6;
            glVertex2f(x + cos(ang) * raio, y + sin(ang) * raio);
        }
        glEnd();
    }
    void mudarCor() { r = (float)rand() / RAND_MAX; g = (float)rand() / RAND_MAX; b = (float)rand() / RAND_MAX; }
    void aumentarTamanho() { if (raio < 100) raio += 2.0; }
    void diminuirTamanho() { if (raio > 7) raio -= 2.0; }
};

// variaveis globais para objetos mistos
std::vector<Bola> bolas;
std::vector<Quadrado> quadrados;
std::vector<Triangulo> triangulos;
std::vector<Hexagono> hexagonos;

struct UltimoObjeto {
    TipoObjeto tipo;
    size_t indice; 
};

UltimoObjeto ultimoAdicionado = {TipoObjeto::BOLA, 0}; 

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto &b : bolas) b.desenhar();
    for (auto &q : quadrados) q.desenhar();
    for (auto &t : triangulos) t.desenhar();
    for (auto &h : hexagonos) h.desenhar();

    glutSwapBuffers();
}

void idle() {
    for (auto &b : bolas) b.mover();
    for (auto &q : quadrados) q.mover();
    for (auto &t : triangulos) t.mover();
    for (auto &h : hexagonos) h.mover();

    glutPostRedisplay();
}

void removerUltimo() {
    switch(ultimoAdicionado.tipo) {
        case TipoObjeto::BOLA:
            if (!bolas.empty()) bolas.pop_back();
            break;
        case TipoObjeto::QUADRADO:
            if (!quadrados.empty()) quadrados.pop_back();
            break;
        case TipoObjeto::TRIANGULO:
            if (!triangulos.empty()) triangulos.pop_back();
            break;
        case TipoObjeto::HEXAGONO:
            if (!hexagonos.empty()) hexagonos.pop_back();
            break;
    }
}

void mudarCorUltimo() {
    switch(ultimoAdicionado.tipo) {
        case TipoObjeto::BOLA:
            if (!bolas.empty()) bolas.back().mudarCor();
            break;
        case TipoObjeto::QUADRADO:
            if (!quadrados.empty()) quadrados.back().mudarCor();
            break;
        case TipoObjeto::TRIANGULO:
            if (!triangulos.empty()) triangulos.back().mudarCor();
            break;
        case TipoObjeto::HEXAGONO:
            if (!hexagonos.empty()) hexagonos.back().mudarCor();
            break;
    }
}

void redimensionarUltimo(bool aumentar) {
    switch(ultimoAdicionado.tipo) {
        case TipoObjeto::BOLA:
            if (!bolas.empty()) aumentar ? bolas.back().aumentarTamanho() : bolas.back().diminuirTamanho();
            break;
        case TipoObjeto::QUADRADO:
            if (!quadrados.empty()) aumentar ? quadrados.back().aumentarTamanho() : quadrados.back().diminuirTamanho();
            break;
        case TipoObjeto::TRIANGULO:
            if (!triangulos.empty()) aumentar ? triangulos.back().aumentarTamanho() : triangulos.back().diminuirTamanho();
            break;
        case TipoObjeto::HEXAGONO:
            if (!hexagonos.empty()) aumentar ? hexagonos.back().aumentarTamanho() : hexagonos.back().diminuirTamanho();
            break;
    }
}

void teclado(unsigned char tecla, int x, int y) {
    if (tecla == '1') { // adiciona bola
        bolas.push_back(Bola());
        ultimoAdicionado = {TipoObjeto::BOLA, bolas.size() - 1};
    } else if (tecla == '2') { // adiciona quadrado
        quadrados.push_back(Quadrado());
        ultimoAdicionado = {TipoObjeto::QUADRADO, quadrados.size() - 1};
    } else if (tecla == '3') { // adiciona triangulo
        triangulos.push_back(Triangulo());
        ultimoAdicionado = {TipoObjeto::TRIANGULO, triangulos.size() - 1};
    } else if (tecla == '4') { // adiciona hexagono
        hexagonos.push_back(Hexagono());
        ultimoAdicionado = {TipoObjeto::HEXAGONO, hexagonos.size() - 1};
    } else if (tecla == '-') { // remove o ultimo objeto
        removerUltimo();
    } else if (tecla == 'c') { // muda cor do ultimo objeto
        mudarCorUltimo();
    } else if (tecla == 'l') { // aumenta tamanho do ultimo objeto
        redimensionarUltimo(true);
    } else if (tecla == 's') { // diminuir tamanho do ultimo objeto
        redimensionarUltimo(false);
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
    glutCreateWindow("Objetos Mistos saltitantes - OpenGL");

    init();

    bolas.push_back(Bola());

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(teclado);

    glutMainLoop();
    return 0;
}