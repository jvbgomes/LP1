#include <iostream>
#include <string>
using namespace std;

class Personagem {
protected:
    string nome;
    int vida;
    int vidaMax;
    int ataque;
    int defesa;

public:
    Personagem(string nome, int vida, int ataque, int defesa)
        : nome(nome), vida(vida), vidaMax(vida), ataque(ataque), defesa(defesa) {}

    virtual void atacar(Personagem& alvo) {
        int dano = ataque - alvo.defesa;
        if (dano < 0) dano = 0;
        alvo.vida -= dano;
        cout << nome << " atacou " << alvo.nome << " causando " << dano << " de dano!" << endl;
        if (alvo.vida <= 0) {
            alvo.vida = 0;
            cout << alvo.nome << " foi derrotado!" << endl;
        }
    }

    bool estaVivo() { return vida > 0; }

    void exibirStatus() {
        cout << "[" << nome << "] HP: " << vida << "/" << vidaMax
             << " ATK: " << ataque << " DEF: " << defesa << endl;
    }

    string getNome() { return nome; }

    virtual ~Personagem() {}
};

class Guerreiro : public Personagem {
private:
    int escudoBonus;

public:
    Guerreiro(string nome)
        : Personagem(nome, 120, 25, 15), escudoBonus(10) {}

    void bloquear() {
        defesa += escudoBonus;
        cout << nome << " levantou o escudo! Defesa aumentada para " << defesa << endl;
    }

    void atacar(Personagem& alvo) override {
        cout << nome << " usa Golpe Poderoso! ";
        int ataqueOriginal = ataque;
        ataque = ataque * 2;
        Personagem::atacar(alvo);
        ataque = ataqueOriginal;
    }
};

class Mago : public Personagem {
private:
    int mana;
    int manaMax;

public:
    Mago(string nome)
        : Personagem(nome, 70, 40, 5), mana(100), manaMax(100) {}

    void lancarFeitico(Personagem& alvo) {
        if (mana < 30) {
            cout << nome << " nao tem mana suficiente!" << endl;
            return;
        }
        mana -= 30;
        int danoMagico = 60;
        alvo.vida -= danoMagico;
        if (alvo.vida < 0) alvo.vida = 0;
        cout << nome << " lanca Bola de Fogo em " << alvo.getNome()
             << " causando " << danoMagico << " de dano magico! (Mana: " << mana << ")" << endl;
        if (!alvo.estaVivo()) cout << alvo.getNome() << " foi derrotado!" << endl;
    }
};

class Arqueiro : public Personagem {
private:
    int flechas;

public:
    Arqueiro(string nome)
        : Personagem(nome, 90, 30, 10), flechas(10) {}

    void atirarFlecha(Personagem& alvo) {
        if (flechas <= 0) {
            cout << nome << " nao tem flechas!" << endl;
            Personagem::atacar(alvo);
            return;
        }
        flechas--;
        cout << nome << " dispara uma flecha! (" << flechas << " restantes) ";
        Personagem::atacar(alvo);
    }
};

int main() {
    Guerreiro g("Thor");
    Mago m("Gandalf");
    Arqueiro a("Legolas");

    cout << "=== Status Inicial ===" << endl;
    g.exibirStatus();
    m.exibirStatus();
    a.exibirStatus();

    cout << "\n=== Combate ===" << endl;
    g.atacar(m);
    m.lancarFeitico(g);
    a.atirarFlecha(m);
    g.bloquear();

    cout << "\n=== Status Final ===" << endl;
    g.exibirStatus();
    m.exibirStatus();
    a.exibirStatus();

    return 0;
}
