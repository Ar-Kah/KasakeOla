#include <cstdint>
#include <vector>
#include <iostream>
#include <stdint.h>

using namespace std;
uint64_t FILE_A = 0x0101010101010101;
uint64_t FILE_H = 0x8080808080808080;
uint64_t RANK_2 = 0x000000000000ff00;

// enums
enum Piece {
  whitePawns, whiteBishops, whiteKnights, whiteRooks, whiteQueens, whiteKings,
  blackPawns, blackBishops, blackKnights, blackRooks, blackQueens, blackKings,
  numberOfPieces
};

enum File { a, b, c, d, e, f, g, h };

char getPieceCharacter(uint64_t square, const std::vector<uint64_t>& bitboards) {
    uint64_t mask = 1ULL << square;
    // check white pieces
    if (mask & bitboards.at(Piece::whitePawns))      return 'P';
    if (mask & bitboards.at(Piece::whiteKnights))    return 'N';
    if (mask & bitboards.at(Piece::whiteBishops))    return 'B';
    if (mask & bitboards.at(Piece::whiteRooks))      return 'R';
    if (mask & bitboards.at(Piece::whiteQueens))     return 'Q';
    if (mask & bitboards.at(Piece::whiteKings))       return 'K';
    // check black pieces
    if (mask & bitboards.at(Piece::blackPawns))     return 'p';
    if (mask & bitboards.at(Piece::blackKnights))    return 'n';
    if (mask & bitboards.at(Piece::blackBishops))    return 'b';
    if (mask & bitboards.at(Piece::blackRooks))     return 'r';
    if (mask & bitboards.at(Piece::blackQueens))    return 'q';
    if (mask & bitboards.at(Piece::blackKings))      return 'k';

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

void printGameBoard(const std::vector<uint64_t>& bitboards) {
    for (short rank = 7; rank >= 0; rank--) {
        for (short file = 0; file < 8; file++) {
            uint64_t square = rank * 8 + file;
            char c = getPieceCharacter(square, bitboards);
            cout << c << " ";
        }
        std::cout << endl;
    }
}

File charToInt(char c) {
    switch (c) {
        case 'a': return File::a;
        case 'b': return File::b;
        case 'c': return File::c;
        case 'd': return File::d;
        case 'e': return File::e;
        case 'f': return File::f;
        case 'g': return File::g;
        case 'h': return File::h;
        default:
            throw std::invalid_argument("Invalid file character");
    }
}

uint64_t whitePawnMove(uint64_t square, std::vector<uint64_t> bitboards) {
    uint64_t canMove = 0;
    if (square & RANK_2) {
        canMove = square << 16;
    }
    uint64_t oneStep = square << 8;
    canMove |= oneStep;
    for (int x = 5; x < 12; x++) {
        if (canMove & bitboards.at(x)) {
            canMove |= ~bitboards.at(x);
        }
    }
    return canMove;
}

std::vector<uint64_t> makePieces() {
    
    std::vector<uint64_t> bitboards{
    // white chesspiece
    0x000000000000ff00,     // pawns
    0x0000000000000024, // knights
    0x0000000000000042, // bishops
    0X0000000000000081, // Rooks
    0x0000000000000008, // queen
    0X0000000000000010, // king

    // black pieces
	0X00FF000000000000, // pawns
	0X2400000000000000, // knights
	0x4200000000000000, // bishops
	0x8100000000000000, // rooks
	0x0800000000000000, // queen
	0X1000000000000000, // king

};
    return bitboards;
}

int main(int argc, char *argv[]) {
    std::vector<uint64_t> bitboards = makePieces();
    printGameBoard(bitboards);
    
    return 0;
}
