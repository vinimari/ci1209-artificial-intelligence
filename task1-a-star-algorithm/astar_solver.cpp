#include "astar_solver.h"
#include "heuristic.h"

std::vector<Action> AStarSolver::solveProblem1() {
    ChessState initial(3, 6);

    // Configurar bordas
    for (int j = 0; j < 6; j++) {
        initial.board[0][j] = '#';
        initial.board[2][j] = '#';
    }
    for (int i = 0; i < 3; i++) {
        initial.board[i][0] = '#';
        initial.board[i][5] = '#';
    }

    // Estado inicial específico (convertendo coordenadas 1-based para 0-based)
    initial.board[0][0] = 'k'; // cavalo preto em (1,1)
    initial.board[0][1] = 'b'; // bispo branco em (1,2)
    initial.board[0][2] = 'b'; // bispo branco em (1,3)
    initial.board[0][3] = 'b'; // bispo branco em (1,4)
    initial.board[0][4] = 'b'; // bispo branco em (1,5)
    initial.board[0][5] = 't'; // torre branca em (1,6)
    initial.board[1][0] = 'c'; // cavalo branco em (2,1)
    initial.board[1][1] = 'c'; // cavalo branco em (2,2)
    initial.board[1][2] = 'c'; // cavalo branco em (2,3)
    initial.board[1][3] = 'c'; // cavalo branco em (2,4)
    initial.board[1][4] = 't'; // torre branca em (2,5)
    initial.board[1][5] = 't'; // torre branca em (2,6)
    initial.board[2][4] = 't'; // torre branca em (3,5)
    initial.board[2][5] = '_'; // posição vazia em (3,6)

    Position target(2, 5); // (3,6) em coordenadas 1-based = (2,5) em 0-based

    return aStar(initial, target, 1);
}

std::vector<Action> AStarSolver::solveProblem2() {
    ChessState initial(4, 4);

    // Configurar bordas
    for (int j = 0; j < 4; j++) {
        initial.board[0][j] = '#';
        initial.board[3][j] = '#';
    }
    for (int i = 0; i < 4; i++) {
        initial.board[i][0] = '#';
        initial.board[i][3] = '#';
    }

    // Estado inicial específico (convertendo coordenadas 1-based para 0-based)
    initial.board[0][0] = 'c'; // cavalo branco em (1,1)
    initial.board[0][1] = 'c'; // cavalo branco em (1,2)
    initial.board[0][2] = 'c'; // cavalo branco em (1,3)
    initial.board[0][3] = 'c'; // cavalo branco em (1,4)
    initial.board[1][0] = 'b'; // bispo branco em (2,1)
    initial.board[1][1] = 'b'; // bispo branco em (2,2)
    initial.board[1][2] = 'b'; // bispo branco em (2,3)
    initial.board[1][3] = 'b'; // bispo branco em (2,4)
    initial.board[2][0] = 't'; // torre branca em (3,1)
    initial.board[2][1] = 't'; // torre branca em (3,2)
    initial.board[2][2] = 't'; // torre branca em (3,3)
    initial.board[2][3] = 't'; // torre branca em (3,4)
    initial.board[3][0] = '_'; // posição vazia em (4,1)
    initial.board[3][1] = '#'; // obstáculo em (4,2)
    initial.board[3][2] = '#'; // obstáculo em (4,3)
    initial.board[3][3] = 'p'; // peão em (4,4)

    Position finalTarget(3, 0); // (4,1) em 1-based = (3,0) em 0-based

    return aStar(initial, finalTarget, 2);
}

std::vector<Action> AStarSolver::aStar(ChessState initial, Position target, int problem) {
    openSet = PriorityQueue<ChessState>();
    closedSet.clear();

    initial.h_cost = (problem == 1) ?
        Heuristic::problem1Heuristic(initial, target) :
        Heuristic::problem2Heuristic(initial, target, false);

    openSet.push(initial);

    while (!openSet.empty()) {
        ChessState current = openSet.pop();

        if (isGoalState(current, target, problem)) {
            return current.path;
        }

        std::string stateKey = current.getStateKey();
        if (closedSet.find(stateKey) != closedSet.end()) {
            continue;
        }
        closedSet.insert(stateKey);

        // Gerar sucessores
        std::vector<ChessState> successors = generateSuccessors(current, target, problem);

        for (ChessState& successor : successors) {
            std::string succKey = successor.getStateKey();
            if (closedSet.find(succKey) == closedSet.end()) {
                openSet.push(successor);
            }
        }
    }

    return std::vector<Action>(); // Solução não encontrada
}

bool AStarSolver::isGoalState(const ChessState& state, Position target, int problem) {
    if (problem == 1) {
        return state.board[target.row][target.col] == 'k';
    } else {
        return state.board[target.row][target.col] == 'q';
    }
}

std::vector<ChessState> AStarSolver::generateSuccessors(const ChessState& current, Position target, int problem) {
    std::vector<ChessState> successors;

    for (int i = 0; i < current.rows; i++) {
        for (int j = 0; j < current.cols; j++) {
            char piece = current.board[i][j];
            if (piece != '_' && piece != '#') {
                Position pos(i, j);
                std::vector<Position> moves = current.getValidMoves(pos, piece);

                for (const Position& move : moves) {
                    ChessState successor = current;
                    successor.board[i][j] = '_';

                    // Verificar promoção de peão
                    if (piece == 'p' && move.row == 0) {
                        successor.board[move.row][move.col] = 'q';
                    } else {
                        successor.board[move.row][move.col] = piece;
                    }

                    successor.g_cost = current.g_cost + 1;

                    // Verificar se há rainha no tabuleiro
                    bool hasQueen = false;
                    for (int x = 0; x < successor.rows; x++) {
                        for (int y = 0; y < successor.cols; y++) {
                            if (successor.board[x][y] == 'q') {
                                hasQueen = true;
                                break;
                            }
                        }
                        if (hasQueen) break;
                    }

                    successor.h_cost = (problem == 1) ?
                        Heuristic::problem1Heuristic(successor, target) :
                        Heuristic::problem2Heuristic(successor, target, hasQueen);

                    successor.path = current.path;
                    successor.path.push_back(Action(piece, pos, move));

                    successors.push_back(successor);
                }
            }
        }
    }

    return successors;
}