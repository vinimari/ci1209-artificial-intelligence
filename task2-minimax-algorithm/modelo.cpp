#include "modelo.h"
#include <sstream>
#include <cstring>
#include <cmath>

bool Coord::operator==(const Coord& other) const {
    return r == other.r && c == other.c;
}

string Move::toString(char mySide) const {
    stringstream ss;
    ss << mySide << " "; 
    
    if (isSalto) {
        ss << "s " << caminhoSaltosMultiplos.size() << " " << de.r << " " << de.c;
        for (const auto& p : caminhoSaltosMultiplos) {
            ss << " " << p.r << " " << p.c;
        }
    } else {
        ss << "m " << de.r << " " << de.c << " " << para.r << " " << para.c;
    }
    return ss.str() + "\n"; 
}

int BoardModel::id(int r, int c) const { return r * 10 + c; }

bool BoardModel::isPosicaoValida(int l, int c) const {
    if(l < 1 || l > 7 || c < 1 || c > 5) return false;
    if(l == 6 && (c == 1 || c == 5)) return false;
    if(l == 7 && (c == 2 || c == 4)) return false;
    return true;
}

void BoardModel::initAdj() {
    for (int r = 1; r <= 7; ++r) {
        for (int c = 1; c <= 5; ++c) {
            if (!isPosicaoValida(r, c)) continue;
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr == 0 && dc == 0) continue;
                    int nr = r + dr;
                    int nc = c + dc;
                    if (isPosicaoValida(nr, nc)) {
                        bool isDiagonal = (abs(dr) + abs(dc) == 2);
                        if (isDiagonal && (r + c) % 2 != 0) continue;
                        adj[id(r,c)].push_back({nr, nc});
                    }
                }
            }
        }
    }
}

BoardModel::BoardModel() {
    initAdj();
    cachorrosPegos = 0;
}

void BoardModel::parseFromString(const char* str) {
    int cachorrosNoTabuleiro = 0;
    for (int r = 1; r <= 7; ++r) {
        for (int c = 1; c <= 5; ++c) {
            int index = r * 8 + c; 
            char ch = str[index];
            if (ch == 'c') { tabuleiro[r][c] = CACHORRO; cachorrosNoTabuleiro++; }
            else if (ch == 'o') tabuleiro[r][c] = ONCA;
            else tabuleiro[r][c] = VAZIO;
        }
    }
    cachorrosPegos = 14 - cachorrosNoTabuleiro;
}

Piece BoardModel::getElemento(int r, int c) const { return tabuleiro[r][c]; }
int BoardModel::getCachorrosPegos() const { return cachorrosPegos; }

Coord BoardModel::getOncaPos() const {
    for(int r=1; r<=7; r++)
        for(int c=1; c<=5; c++)
            if(tabuleiro[r][c] == ONCA) return {r,c};
    return {0,0};
}

void BoardModel::buscaSaltos(Coord curr, Piece tabuleiroAux[8][6], vector<Coord>& caminho, vector<Move>& movimentacoes) const {
    bool isSaltoPossivel = false;
    int currId = id(curr.r, curr.c);
    
    if (adj.count(currId)) {
        for (auto vizinho : adj.at(currId)) {
            if (tabuleiroAux[vizinho.r][vizinho.c] == CACHORRO) {
                int dr = vizinho.r - curr.r;
                int dc = vizinho.c - curr.c;
                Coord dest = {vizinho.r + dr, vizinho.c + dc};

                if (isPosicaoValida(dest.r, dest.c) && tabuleiroAux[dest.r][dest.c] == VAZIO) {
                    bool isValido = true;
                    if (abs(dr)==1 && abs(dc)==1) { 
                       if ((vizinho.r + vizinho.c) % 2 != 0) isValido = false; 
                    }

                    if (isValido) {
                        tabuleiroAux[curr.r][curr.c] = VAZIO;
                        tabuleiroAux[vizinho.r][vizinho.c] = VAZIO;
                        tabuleiroAux[dest.r][dest.c] = ONCA;
                        
                        caminho.push_back(dest);
                        buscaSaltos(dest, tabuleiroAux, caminho, movimentacoes);
                        caminho.pop_back();
                        
                        tabuleiroAux[dest.r][dest.c] = VAZIO;
                        tabuleiroAux[vizinho.r][vizinho.c] = CACHORRO;
                        tabuleiroAux[curr.r][curr.c] = ONCA;
                        isSaltoPossivel = true;
                    }
                }
            }
        }
    }

    if (!isSaltoPossivel && !caminho.empty()) {
        movimentacoes.push_back({getOncaPos(), caminho.back(), true, caminho});
    }
}

void BoardModel::getOncaMovimentos(vector<Move>& movimentacoes) const {
    Coord j = getOncaPos();
    if (adj.count(id(j.r, j.c))) {
        for (auto n : adj.at(id(j.r, j.c))) {
            if (tabuleiro[n.r][n.c] == VAZIO) {
                movimentacoes.push_back({j, n, false, {}});
            }
        }
    }
    Piece tabuleiroAux[8][6];
    memcpy(tabuleiroAux, tabuleiro, sizeof(tabuleiro));
    vector<Coord> caminho;
    buscaSaltos(j, tabuleiroAux, caminho, movimentacoes);
}

void BoardModel::getCachorroMovimentos(vector<Move>& moves) const {
    for(int r=1; r<=7; r++) {
        for(int c=1; c<=5; c++) {
            if(tabuleiro[r][c] == CACHORRO) {
                if (adj.count(id(r,c))) {
                    for(auto n : adj.at(id(r,c))) {
                        if(tabuleiro[n.r][n.c] == VAZIO) {
                            moves.push_back({{r,c}, n, false, {}});
                        }
                    }
                }
            }
        }
    }
}

void BoardModel::mover(const Move& m) {
    if (m.isSalto) {
        Coord curr = m.de;
        for (const auto& dest : m.caminhoSaltosMultiplos) {
            int midR = (curr.r + dest.r) / 2;
            int midC = (curr.c + dest.c) / 2;
            tabuleiro[curr.r][curr.c] = VAZIO;
            tabuleiro[midR][midC] = VAZIO;
            tabuleiro[dest.r][dest.c] = ONCA;
            curr = dest;
            cachorrosPegos++;
        }
    } else {
        Piece p = tabuleiro[m.de.r][m.de.c];
        tabuleiro[m.de.r][m.de.c] = VAZIO;
        tabuleiro[m.para.r][m.para.c] = p;
    }
}

bool BoardModel::isFim(int& vencedor) const {
    if (cachorrosPegos >= 5) { vencedor = 1; return true; }
    vector<Move> movimentosOnca;
    getOncaMovimentos(movimentosOnca);
    if (movimentosOnca.empty()) { vencedor = 2; return true; }
    vencedor = 0;
    return false;
}
