#include <iostream>
#include <string>
using namespace std;

class Vetor2D {
public:
    float x, y;

    Vetor2D(float x = 0, float y = 0) : x(x), y(y) {}

    Vetor2D operator+(const Vetor2D& outro) const {
        return Vetor2D(x + outro.x, y + outro.y);
    }

    Vetor2D operator-(const Vetor2D& outro) const {
        return Vetor2D(x - outro.x, y - outro.y);
    }

    Vetor2D operator*(float escalar) const {
        return Vetor2D(x * escalar, y * escalar);
    }

    bool operator==(const Vetor2D& outro) const {
        return x == outro.x && y == outro.y;
    }

    void exibir() const {
        cout << "(" << x << ", " << y << ")";
    }
};

class Vetor3D : public Vetor2D {
public:
    float z;

    Vetor3D(float x = 0, float y = 0, float z = 0) : Vetor2D(x, y), z(z) {}

    Vetor3D operator+(const Vetor3D& outro) const {
        return Vetor3D(x + outro.x, y + outro.y, z + outro.z);
    }

    Vetor3D operator-(const Vetor3D& outro) const {
        return Vetor3D(x - outro.x, y - outro.y, z - outro.z);
    }

    float produtoEscalar(const Vetor3D& outro) const {
        return x * outro.x + y * outro.y + z * outro.z;
    }

    Vetor3D produtoVetorial(const Vetor3D& outro) const {
        return Vetor3D(
            y * outro.z - z * outro.y,
            z * outro.x - x * outro.z,
            x * outro.y - y * outro.x
        );
    }

    void exibir() const {
        cout << "(" << x << ", " << y << ", " << z << ")";
    }
};

int main() {
    cout << "=== Vetor 2D ===" << endl;
    Vetor2D v1(3, 4);
    Vetor2D v2(1, 2);

    cout << "v1 = "; v1.exibir(); cout << endl;
    cout << "v2 = "; v2.exibir(); cout << endl;

    Vetor2D soma = v1 + v2;
    cout << "v1 + v2 = "; soma.exibir(); cout << endl;

    Vetor2D diff = v1 - v2;
    cout << "v1 - v2 = "; diff.exibir(); cout << endl;

    Vetor2D escal = v1 * 3;
    cout << "v1 * 3 = "; escal.exibir(); cout << endl;

    cout << "v1 == v2? " << (v1 == v2 ? "Sim" : "Nao") << endl;

    cout << "\n=== Vetor 3D ===" << endl;
    Vetor3D u(1, 2, 3);
    Vetor3D w(4, 5, 6);

    cout << "u = "; u.exibir(); cout << endl;
    cout << "w = "; w.exibir(); cout << endl;

    Vetor3D soma3 = u + w;
    cout << "u + w = "; soma3.exibir(); cout << endl;

    cout << "u . w = " << u.produtoEscalar(w) << endl;

    Vetor3D cruz = u.produtoVetorial(w);
    cout << "u x w = "; cruz.exibir(); cout << endl;

    return 0;
}
