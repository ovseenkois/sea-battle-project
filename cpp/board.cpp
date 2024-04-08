#include "../headers/board.h"

Board::Board(int size, Point begin, int cell_size) : size_(size), begin_(begin), cell_size_(cell_size) {
  close_board_.resize(size_);
  for (int i = 0; i < size_; ++i) {
    close_board_[i].resize(size_);
  };
  open_board_.resize(size_);
  for (int i = 0; i < size_; ++i) {
    open_board_[i].resize(size_);
  };
  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      sf::RectangleShape shape(sf::Vector2f(cell_size_, cell_size_));
      sf::Color cell_color(180, 180, 255);
      shape.setOutlineColor(cell_color);
      shape.setOutlineThickness(cell_size_ / 20);
      shape.setPosition(begin_.x_ + i * (cell_size_ + 100 / 20), begin_.y_ + j * (cell_size_ + 100 / 20));
      Cell cell(shape, cell_size_, nullptr);
      close_board_[j][i] = cell;
    }
  }
  symbols_ =
      std::vector<Symbol>({Symbol("A"), Symbol("B"), Symbol("C"), Symbol("D"), Symbol("E"), Symbol("F"), Symbol("G"),
                           Symbol("H"), Symbol("I"), Symbol("J"), Symbol("0"), Symbol("1"), Symbol("2"), Symbol("3"),
                           Symbol("4"), Symbol("5"), Symbol("6"), Symbol("7"), Symbol("8"), Symbol("9")});
  for (int i = 0; i < 10; ++i) {
    symbols_[i].text_.setPosition(begin_.x_ + i * 55 + 20, begin_.y_ - 30);
  }
  for (int i = 10; i < 20; ++i) {
    symbols_[i].text_.setPosition(begin_.x_ - 30, begin_.y_ + (i - 10) * 55 + 15);
  }
}
void Board::Draw(sf::RenderWindow& window) {
  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      if (open_) {
        window.draw(close_board_[i][j].GetShape());
      } else {
        window.draw(open_board_[i][j].GetShape());
      }
    }
  }
  for (int i = 0; i < 20; ++i) {
    window.draw(symbols_[i].text_);
  }
}

void Board::Clear() {
  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      if (open_) {
        if (close_board_[i][j].GetTemporary()) {
          close_board_[i][j] = Constants::BoardCell(close_board_[i][j].GetCoordinates());
        }
      } else {
        if (open_board_[i][j].GetTemporary()) {
          open_board_[i][j] = Constants::BoardCell(open_board_[i][j].GetCoordinates());
        }
      }
    }
  }
}

void Board::Close() {
  open_ = false;
}

void Board::Open() {
  open_ = true;
}

void Board::CopyCloseToOpen() {
  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      if (close_board_[i][j].GetPtr()) {
        open_board_[i][j] = Constants::HideBoardCell(close_board_[i][j]);
      } else {
        open_board_[i][j] = Constants::BoardCell(close_board_[i][j].GetCoordinates());
      }
    }
  }
}