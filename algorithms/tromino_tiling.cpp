#include <map>
#include <array>
#include <cmath>
#include <cassert>

enum class Piece {
    rightUp,
    leftUp,
    leftDown,
    rightDown,
};

using Position = std::pair<int, int>;

// struct CompareY {
//     bool operator() (const std::pair<int, int>& a, const std::pair<int, int>& b) {
//         if (a.second == b.second) {
//             return a.first < b.first;
//         }
//         return a.second < b.second;
//     }
// }

// class Board {
//     int size;
//     std::set<std::pair<int, int>> pieces_sorted_by_x;
//     std::set<std::pair<int, int>, CompareY> pieces_sorted_by_y;
//     std::map<std::pair<int, int>, Piece> pieces;

//     Board(int n) {
//         size = std::pow(2, n);
//     }
// };

class Board {
private:
    int** squares;
    int size;
    std::vector<std::pair<Piece, Position>> pieces;

public:
    Board(int n) {
        size = std::pow(2, n);
        squares = new int*[size];
        for (int i = 0; i < size; i++) {
            squares[i] = new int[size];
            for (int j; j < size; j++) {
                squares[i][j] = 0;
            }
        }
    }

    void add_piece(Piece piece, Position pos) {
        pieces.push_back(std::make_pair(piece, pos));
        if (pos.first < 0 || pos.first >= size || pos.second < 0 || pos.second >= size) {
            throw std::out_of_range("Position is out of bounds.");
        }

        int piece_no = pieces.size();
        if (piece == Piece::leftDown) {
            if (pos.first == size - 1 || pos.second == 0) {
                throw std::runtime_error("Can't add piece.");
            }
            occupy_board(piece_no, pos);
            occupy_board(piece_no, Position(pos.first + 1, pos.second));
            occupy_board(piece_no, Position(pos.first, pos.second - 1));
        } else if (piece == Piece::leftUp) {
            if (pos.first == 0 || pos.second == 0) {
                throw std::runtime_error("Can't add piece.");
            }
            occupy_board(piece_no, pos);
            occupy_board(piece_no, Position(pos.first - 1, pos.second));
            occupy_board(piece_no, Position(pos.first, pos.second - 1));
        } else if (piece == Piece::rightUp) {
            if (pos.first == 0 || pos.second == size - 1) {
                throw std::runtime_error("Can't add piece.");
            }
            occupy_board(piece_no, pos);
            occupy_board(piece_no, Position(pos.first - 1, pos.second));
            occupy_board(piece_no, Position(pos.first, pos.second + 1));
        } else { // Piece::rightDown
            if (pos.first == size - 1 || pos.second == size - 1) {
                throw std::runtime_error("Can't add piece.");
            }
            occupy_board(piece_no, pos);
            occupy_board(piece_no, Position(pos.first + 1, pos.second));
            occupy_board(piece_no, Position(pos.first, pos.second + 1));
        }
    }

    bool is_ocuppied(Position pos) {
        return squares[pos.first][pos.second];
    }

    void occupy_board(int piece_no, Position pos) {
        if (is_ocuppied(pos)) {
            throw std::runtime_error("Can't occupy this space.");
        }
        squares[pos.first][pos.second] = piece_no;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                printf("%1d ", squares[i][j]);
            }
            printf("\n");
        }
    }
};

int main() {
    int n = 3;
    Board board(n);
    board.add_piece(Piece::rightDown, {2, 1});
    board.add_piece(Piece::rightDown, {3, 2});
    board.print();
    return 0;
}
