#include "ia.h"
#include "heuristica.h"
#include <limits>
#include <algorithm>
#include <vector>

using namespace std;

// Variável auxiliar para armazenar a jogada raiz durante a recursão
Move melhorAcaoRaiz;

int minimax(BoardModel tabuleiro, int profundidade, int alpha, int beta, bool maxOnca, int profundidadeInicial) {
    int vencedor;
    if (profundidade == 0 || tabuleiro.isFim(vencedor)) {
        return evaluate(tabuleiro);
    }

    vector<Move> movimentos;
    if (maxOnca) {
        tabuleiro.getOncaMovimentos(movimentos);
        // Ordenação heurística para poda eficiente (capturas primeiro)
        sort(movimentos.begin(), movimentos.end(), [](const Move& a, const Move& b) {
            return a.isSalto > b.isSalto;
        });
        
        int maxResultado = -numeric_limits<int>::max();
        for (const auto& movimento : movimentos) {
            BoardModel prox = tabuleiro;
            prox.mover(movimento);
            int resultado = minimax(prox, profundidade - 1, alpha, beta, false, profundidadeInicial);
            
            if (resultado > maxResultado) {
                maxResultado = resultado;
                // Se estamos na raiz da árvore, salvamos essa como a melhor jogada candidata
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
            BoardModel prox = tabuleiro;
            prox.mover(movimento);
            int resultado = minimax(prox, profundidade - 1, alpha, beta, true, profundidadeInicial);
            
            if (resultado < minResultado) {
                minResultado = resultado;
                // Se estamos na raiz e é a vez da IA (Cachorro), salvamos aqui
                if (profundidade == profundidadeInicial) melhorAcaoRaiz = movimento;
            }
            beta = min(beta, resultado);
            if (beta <= alpha) break;
        }
        return minResultado;
    }
}

Move encontrarMelhorJogada(BoardModel tabuleiro, int profundidade, bool souOnca) {
    int alpha = -numeric_limits<int>::max();
    int beta = numeric_limits<int>::max();
    
    // Fallback caso não encontre nada (evita crash)
    vector<Move> movimentosIniciais;
    if(souOnca) tabuleiro.getOncaMovimentos(movimentosIniciais);
    else tabuleiro.getCachorroMovimentos(movimentosIniciais);
    
    if(!movimentosIniciais.empty()) melhorAcaoRaiz = movimentosIniciais[0];

    // Inicia a recursão. Note que passamos 'souOnca' como o maximizador inicial
    // Se eu sou Onça, quero Max. Se sou Cachorro, o Minimax vai entrar no 'else' mas
    // a lógica interna lida com Min/Max. O importante é quem quer maximizar o score positivo.
    // Score positivo = Bom para Onça.
    // Então, se 'souOnca' é true, chamamos buscando Max. 
    // Se 'souOnca' é false (sou cachorro), queremos minimizar o score da Onça.
    
    // No entanto, minha implementação do minimax acima assume:
    // maxOnca = true -> turno da Onça (Maximiza)
    // maxOnca = false -> turno do Cão (Minimiza)
    // Isso está correto. O que precisamos passar é DE QUEM É O TURNO agora.
    
    minimax(tabuleiro, profundidade, alpha, beta, souOnca, profundidade);
    
    return melhorAcaoRaiz;
}
