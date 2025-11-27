// ia.cpp
#include "ia.h"
#include "heuristica.h"
#include <limits>
#include <algorithm>
#include <vector>

using namespace std;

Move melhorAcaoRaiz;

int minimax(BoardModel& tabuleiro, int profundidade, int alpha, int beta, bool maxOnca, int profundidadeInicial, const vector<string>& historico) {
    int vencedor;
    
    if (profundidade == 0 || tabuleiro.isFim(vencedor)) {
        return evaluate(tabuleiro);
    }

    vector<Move> movimentos;
    if (maxOnca) {
        tabuleiro.getOncaMovimentos(movimentos);
        // Ordenação
        sort(movimentos.begin(), movimentos.end(), [](const Move& a, const Move& b) {
            return a.isSalto > b.isSalto;
        });
        
        int maxResultado = -numeric_limits<int>::max();
        for (const auto& movimento : movimentos) {
            
            // MAKE
            tabuleiro.mover(movimento);
            
            // RECURSÃO
            int resultado = minimax(tabuleiro, profundidade - 1, alpha, beta, false, profundidadeInicial, historico);

            // UNMAKE
            tabuleiro.desfazer(movimento);
            
            if (resultado > maxResultado) {
                maxResultado = resultado;
                if (profundidade == profundidadeInicial) melhorAcaoRaiz = movimento; 
            }
            alpha = max(alpha, resultado);
            if (beta <= alpha) break;
        }
        return maxResultado;
    } else {
        tabuleiro.getCachorroMovimentos(movimentos);
        int minResultado = numeric_limits<int>::max();
        for (const auto& movimento : movimentos) {
            
            // MAKE
            tabuleiro.mover(movimento);
            
            // RECURSÃO
            int resultado = minimax(tabuleiro, profundidade - 1, alpha, beta, true, profundidadeInicial, historico);
            
            // UNMAKE
            tabuleiro.desfazer(movimento);
            
            if (resultado < minResultado) {
                minResultado = resultado;
                if (profundidade == profundidadeInicial) melhorAcaoRaiz = movimento;
            }
            beta = min(beta, resultado);
            if (beta <= alpha) break;
        }
        return minResultado;
    }
}

Move encontrarMelhorJogada(BoardModel tabuleiro, int profundidade, bool souOnca, const vector<string>& historico) {
    int alpha = -numeric_limits<int>::max();
    int beta = numeric_limits<int>::max();
    
    vector<Move> movimentosIniciais;
    if(souOnca) tabuleiro.getOncaMovimentos(movimentosIniciais);
    else tabuleiro.getCachorroMovimentos(movimentosIniciais);
    
    if(!movimentosIniciais.empty()) melhorAcaoRaiz = movimentosIniciais[0];

    BoardModel tabuleiroBusca = tabuleiro; 
    
    
    Move melhorLocal = movimentosIniciais[0];
    int melhorVal = souOnca ? -999999 : 999999;
    
    for (const auto& m : movimentosIniciais) {
        // MAKE
        tabuleiroBusca.mover(m);
        
        string hash = tabuleiroBusca.toHashString();
        bool repetido = false;
        for(const string& h : historico) if(h == hash) { repetido = true; break; }
        
        int val;
        if (repetido) {
            val = souOnca ? -50000 : 50000;
        } else {
            // RECURSÃO
            val = minimax(tabuleiroBusca, profundidade - 1, alpha, beta, !souOnca, profundidade, historico);
        }
        
        // UNMAKE
        tabuleiroBusca.desfazer(m);

        if (souOnca) {
            if (val > melhorVal) { melhorVal = val; melhorLocal = m; }
            alpha = max(alpha, val);
        } else {
            if (val < melhorVal) { melhorVal = val; melhorLocal = m; }
            beta = min(beta, val);
        }
    }

    return melhorLocal;
}