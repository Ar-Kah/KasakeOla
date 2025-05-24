#include <iostream>
#include <stdint.h>

using namespace std;

// white chesspiece
uint64_t whitePawns =   0x000000000000ff00;
uint64_t whiteBishops = 0x0000000000000024;
uint64_t whiteKnights = 0x0000000000000042;
uint64_t whiteRooks =   0x0000000000000081;
uint64_t whiteQueens =  0x0000000000000008;
uint64_t whiteKing =    0x0000000000000010;

// black chesspieces
uint64_t blackPawns =   0x00ff000000000000;
uint64_t blackBishops = 0x2400000000000000;
uint64_t blackKnights = 0x4200000000000000;
uint64_t blackRooks =   0x8100000000000000;
uint64_t blackQueens =  0x0800000000000000;
uint64_t blackKing =    0x1000000000000000;

uint64_t FILE_A = 0x0101010101010101;
uint64_t FILE_H = 0x8080808080808080;

char getPieceCharacter(uint64_t square) {
    uint64_t mask = 1ULL << square;

    // check white pieces
    if (mask & whitePawns)      return 'P';
    if (mask & whiteKnights)    return 'N';
    if (mask & whiteBishops)    return 'B';
    if (mask & whiteRooks)      return 'R';
    if (mask & whiteQueens)     return 'Q';
    if (mask & whiteKing)       return 'K';

    // check black pieces
    if (mask & blackPawns)      return 'p';
    if (mask & blackKnights)    return 'n';
    if (mask & blackBishops)    return 'b';
    if (mask & blackRooks)      return 'r';
    if (mask & blackQueens)     return 'q';
    if (mask & blackKing)       return 'k';

    return '.'; // empty square
}


void printBitboard(uint64_t bitboard) {

    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            int square = rank * 8 + file;
            if ((bitboard >> square) & 1) {
                cout << "x ";
            } else {
                cout << ". ";
            }
        }
        cout << " " << rank + 1 << endl;
    }
    cout << "a b c d e f g h" << endl;
}

void printGameBoard() {
    for (short rank = 7; rank >= 0; rank--) {
        for (short file = 0; file < 8; file++) {
            uint64_t square = rank * 8 + file;
            char c = getPieceCharacter(square);
            cout << c << " ";
        }
        cout << endl;
    }
}

uint64_t whitePawnAttacks() {
    uint64_t whitePawnsAttackLeft = (whitePawns << 7) & ~FILE_H;
    uint64_t whitePawnsAttackRight = (whitePawns << 9) & ~FILE_A;

    uint64_t whitePawnsAttack = whitePawnsAttackLeft | whitePawnsAttackRight;
    return whitePawnsAttack;
}

int main(int argc, char *argv[])
{

    return 0;
}
