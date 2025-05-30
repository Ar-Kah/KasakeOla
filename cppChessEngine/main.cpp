#include <iostream>
#include <stdint.h>
#include <string>

using namespace std;

// white chesspiece
uint64_t W_PAWN =   0x000000000000ff00;
uint64_t W_BISHOP = 0x0000000000000024;
uint64_t W_KNIGHT = 0x0000000000000042;
uint64_t W_ROOK =   0X0000000000000081;
uint64_t W_QUEEN =  0x0000000000000008;
uint64_t W_KING =    0X0000000000000010;
  
// BLACK CHESSPIECES
uint64_t B_PAWN =   0X00FF000000000000;
uint64_t B_BISHOP = 0X2400000000000000;
uint64_t B_KNIGHT = 0x4200000000000000;
uint64_t B_ROOK =   0x8100000000000000;
uint64_t B_QUEEN =  0x0800000000000000;
uint64_t B_KING =    0X1000000000000000;

uint64_t FILE_A = 0x0101010101010101;
uint64_t FILE_H = 0x8080808080808080;
uint64_t RANK_2 = 0x000000000000ff00;

// enums
enum Piece {
  whitePawns, whiteKinghts, whiteBishops, whiteRooks, whiteQueens, whiteKings,
  blackPawns, blackKinghts, blackBishops, blackRooks, blackQueens, blackKings,
  numberOfPieces
};

enum File { a, b, c, d, e, f, g, h };

uint64_t blackPieces[Piece::numberOfPieces / 2];
uint64_t whitePieces[Piece::numberOfPieces / 2];

char getPieceCharacter(uint64_t square) {
    uint64_t mask = 1ULL << square;
    // check white pieces
    if (mask & W_PAWN)      return 'P';
    if (mask & W_KNIGHT)    return 'N';
    if (mask & W_BISHOP)    return 'B';
    if (mask & W_ROOK)      return 'R';
    if (mask & W_QUEEN)     return 'Q';
    if (mask & W_KING)       return 'K';
    // check black pieces
    if (mask & B_PAWN)      return 'p';
    if (mask & B_KNIGHT)    return 'n';
    if (mask & B_BISHOP)    return 'b';
    if (mask & B_ROOK)      return 'r';
    if (mask & B_QUEEN)     return 'q';
    if (mask & B_KING)       return 'k';

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
	std::cout << endl;
    }
}

uint64_t whitePawnAttacks() {
    uint64_t whitePawnsAttackLeft = (W_PAWN << 7) & ~FILE_H;
    uint64_t whitePawnsAttackRight = (W_PAWN << 9) & ~FILE_A;

    uint64_t whitePawnsAttack = whitePawnsAttackLeft | whitePawnsAttackRight;
    return whitePawnsAttack;
}

uint64_t blackPawnAttacks() {
    uint64_t blackPawnsAttackLeft = (B_PAWN >> 7) & ~FILE_A;
    uint64_t blackPawnsAttackRight = (B_PAWN >> 9) & ~FILE_H;

    uint64_t blackPawnsAttack = blackPawnsAttackLeft | blackPawnsAttackRight;
    return blackPawnsAttack;
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

uint64_t whitePawnMove(uint64_t square) {
    uint64_t canMove = 0;
    if (square & RANK_2) {
	canMove = square << 16;
    }
    uint64_t oneStep = square << 8;
    canMove |= oneStep;
    for (uint64_t i: blackPieces) {
	if (canMove & i) {
	    canMove |= ~i;
	}
    }
    return canMove;
}

void initWhitePieces() {
    whitePieces[0] = W_PAWN;
    whitePieces[1] = W_KNIGHT;
    whitePieces[2] = W_BISHOP;
    whitePieces[3] = W_ROOK;
    whitePieces[4] = W_QUEEN;
    whitePieces[5] = W_KING;
}

void initBlackPieces() {
    
    blackPieces[0] = W_PAWN;
    blackPieces[1] = W_KNIGHT;
    blackPieces[2] = W_BISHOP;
    blackPieces[3] = W_ROOK;
    blackPieces[4] = W_QUEEN;
    blackPieces[5] = W_KING;
}

// TODO: initailize all of the pieces

int main(int argc, char *argv[]) {
    uint64_t pawn = 0x0000000000001000;
    uint64_t pawnMoves = whitePawnMove(pawn);
    initWhitePieces();
    initBlackPieces();
    for (auto piece : whitePieces) {
	printBitboard(piece);
    }
    return 0;
}
