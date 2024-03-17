#include "headers/ship.h"
#include "headers/constants.h"

void Ship1::Move(sf::Event& event, Board& board) {
  int cell_size = 50 + 50 / 20;
  int i_ = std::floor((event.mouseMove.y - board.begin_.y_) / cell_size);
  int j_ = std::floor((event.mouseMove.x - board.begin_.x_) / cell_size);
  if (i_ >= 0 && i_ < board.size_ && j_ >= 0 && j_ < board.size_ && board.board_[i_][j_].IsAvailableToSet()) {
    // if (board.board_[i_][j_].GetPtr() != nullptr) {
    //   return;
    // }
    board.board_[i_][j_] = Constants().ShipCell(this, board.board_[i_][j_].GetCoordinates());
    for (int i = 0; i < board.size_; ++i) {
      for (int j = 0; j < board.size_; ++j) {
        if (board.board_[i][j].GetPtr() != nullptr) {
          continue;
        } else {
          board.board_[i][j] = Constants().BoardCell(board.board_[i][j].GetCoordinates());
        }
      }
    }
    board.board_[i_][j_] = Constants().ShipCell(nullptr, board.board_[i_][j_].GetCoordinates());
  }
}

void Ship1::Set(sf::Event& event, Board& board) {
  int cell_size = 50 + 50 / 20;
  int i_ = std::floor((event.mouseButton.y - board.begin_.y_) / cell_size);
  int j_ = std::floor((event.mouseButton.x - board.begin_.x_) / cell_size);
  if (i_ >= 0 && i_ < board.size_ && j_ >= 0 && j_ < board.size_) {
    board.board_[i_][j_] = Constants().ShipCell(this, board.board_[i_][j_].GetCoordinates());
  }
}

void Ship2::Move(sf::Event& event, Board& board) {
  int cell_size = 50 + 50 / 20;
  int i_ = std::floor((event.mouseMove.y - board.begin_.y_) / cell_size);
  int j_ = std::floor((event.mouseMove.x - board.begin_.x_) / cell_size);
  if (orientation_ == RIGHT) {
    if (i_ >= 0 && i_ < board.size_ && j_ >= 0 && j_ + 1 < board.size_ && board.board_[i_][j_].IsAvailableToSet() &&
        board.board_[i_][j_ + 1].IsAvailableToSet()) {
      board.board_[i_][j_] = Constants().ShipCell(this, board.board_[i_][j_].GetCoordinates());
      board.board_[i_][j_ + 1] = Constants().ShipCell(this, board.board_[i_][j_ + 1].GetCoordinates());
      for (int i = 0; i < board.size_; ++i) {
        for (int j = 0; j < board.size_; ++j) {
          if (board.board_[i][j].GetPtr() != nullptr) {
            continue;
          } else {
            board.board_[i][j] = Constants().BoardCell(board.board_[i][j].GetCoordinates());
          }
        }
      }
      board.board_[i_][j_] = Constants().ShipCell(nullptr, board.board_[i_][j_].GetCoordinates());
      board.board_[i_][j_ + 1] = Constants().ShipCell(nullptr, board.board_[i_][j_ + 1].GetCoordinates());
    }
  } else if (orientation_ == DOWN) {
    if (i_ >= 0 && i_ + 1 < board.size_ && j_ >= 0 && j_ < board.size_ && board.board_[i_][j_].IsAvailableToSet() &&
        board.board_[i_ + 1][j_].IsAvailableToSet()) {
      board.board_[i_][j_] = Constants().ShipCell(this, board.board_[i_][j_].GetCoordinates());
      board.board_[i_ + 1][j_] = Constants().ShipCell(this, board.board_[i_ + 1][j_].GetCoordinates());
      for (int i = 0; i < board.size_; ++i) {
        for (int j = 0; j < board.size_; ++j) {
          if (board.board_[i][j].GetPtr() != nullptr) {
            continue;
          } else {
            board.board_[i][j] = Constants().BoardCell(board.board_[i][j].GetCoordinates());
          }
        }
      }
      board.board_[i_][j_] = Constants().ShipCell(nullptr, board.board_[i_][j_].GetCoordinates());
      board.board_[i_ + 1][j_] = Constants().ShipCell(nullptr, board.board_[i_ + 1][j_].GetCoordinates());
    }
  }
}

void Ship2::Set(sf::Event& event, Board& board) {
  int cell_size = 50 + 50 / 20;
  int i_ = std::floor((event.mouseButton.y - board.begin_.y_) / cell_size);
  int j_ = std::floor((event.mouseButton.x - board.begin_.x_) / cell_size);
  if (orientation_ == RIGHT) {
    if (i_ >= 0 && i_ < board.size_ && j_ >= 0 && j_ + 1 < board.size_) {
      board.board_[i_][j_] = Constants().ShipCell(this, board.board_[i_][j_].GetCoordinates());
      board.board_[i_][j_ + 1] = Constants().ShipCell(this, board.board_[i_][j_ + 1].GetCoordinates());
    }
  } else if (orientation_ == DOWN) {
    if (i_ >= 0 && i_ + 1 < board.size_ && j_ >= 0 && j_ < board.size_) {
      board.board_[i_][j_] = Constants().ShipCell(this, board.board_[i_][j_].GetCoordinates());
      board.board_[i_ + 1][j_] = Constants().ShipCell(this, board.board_[i_ + 1][j_].GetCoordinates());
    }
  }
}

void Ship2::Rotate(sf::Event& event, Board& board, sf::RenderWindow& window) {
  int cell_size = 50 + 50 / 20;
  int i_ = std::floor((sf::Mouse::getPosition(window).y - board.begin_.y_) / cell_size);
  int j_ = std::floor((sf::Mouse::getPosition(window).x - board.begin_.x_) / cell_size);
  if (event.key.code == sf::Keyboard::R) {
    if (orientation_ == RIGHT) {
      if (i_ + 1 < board.size_ && board.board_[i_ + 1][j_].IsAvailableToSet()) {
        board.board_[i_][j_ + 1] = Constants().BoardCell(board.board_[i_][j_ + 1].GetCoordinates());
        board.board_[i_ + 1][j_] = Constants().ShipCell(nullptr, board.board_[i_ + 1][j_].GetCoordinates());
        orientation_ = DOWN;
      }
    } else if (orientation_ == DOWN) {
      if (j_ + 1 < board.size_ && board.board_[i_][j_ + 1].IsAvailableToSet()) {
        board.board_[i_][j_ + 1] = Constants().ShipCell(nullptr, board.board_[i_][j_ + 1].GetCoordinates());
        board.board_[i_ + 1][j_] = Constants().XCell(board.board_[i_ + 1][j_].GetCoordinates());
        orientation_ = RIGHT;
      }
    }
  }
}

void Ship3::Move(sf::Event& event, Board& board) {
  int cell_size = 50 + 50 / 20;
  int i_ = std::floor((event.mouseMove.y - board.begin_.y_) / cell_size);
  int j_ = std::floor((event.mouseMove.x - board.begin_.x_) / cell_size);
  if (i_ >= 0 && i_ < board.size_ && j_ >= 0 && j_ + 2 < board.size_ && board.board_[i_][j_].IsAvailableToSet() &&
      board.board_[i_][j_ + 1].IsAvailableToSet() && board.board_[i_][j_ + 2].IsAvailableToSet()) {
    board.board_[i_][j_] = Constants().ShipCell(this, board.board_[i_][j_].GetCoordinates());
    board.board_[i_][j_ + 1] = Constants().ShipCell(this, board.board_[i_][j_ + 1].GetCoordinates());
    board.board_[i_][j_ + 2] = Constants().ShipCell(this, board.board_[i_][j_ + 2].GetCoordinates());
    for (int i = 0; i < board.size_; ++i) {
      for (int j = 0; j < board.size_; ++j) {
        if (board.board_[i][j].GetPtr() != nullptr) {
          continue;
        } else {
          board.board_[i][j] = Constants().BoardCell(board.board_[i][j].GetCoordinates());
        }
      }
    }
    board.board_[i_][j_] = Constants().ShipCell(nullptr, board.board_[i_][j_].GetCoordinates());
    board.board_[i_][j_ + 1] = Constants().ShipCell(nullptr, board.board_[i_][j_ + 1].GetCoordinates());
    board.board_[i_][j_ + 2] = Constants().ShipCell(nullptr, board.board_[i_][j_ + 2].GetCoordinates());
  }
}

void Ship3::Set(sf::Event& event, Board& board) {
  int cell_size = 50 + 50 / 20;
  int i_ = std::floor((event.mouseButton.y - board.begin_.y_) / cell_size);
  int j_ = std::floor((event.mouseButton.x - board.begin_.x_) / cell_size);
  if (i_ >= 0 && i_ < board.size_ && j_ >= 0 && j_ + 2 < board.size_) {
    board.board_[i_][j_] = Constants().ShipCell(this, board.board_[i_][j_].GetCoordinates());
    board.board_[i_][j_ + 1] = Constants().ShipCell(this, board.board_[i_][j_ + 1].GetCoordinates());
    board.board_[i_][j_ + 2] = Constants().ShipCell(this, board.board_[i_][j_ + 2].GetCoordinates());
  }
}

void Ship4::Move(sf::Event& event, Board& board) {
  int cell_size = 50 + 50 / 20;
  int i_ = std::floor((event.mouseMove.y - board.begin_.y_) / cell_size);
  int j_ = std::floor((event.mouseMove.x - board.begin_.x_) / cell_size);
  if (i_ >= 0 && i_ < board.size_ && j_ >= 0 && j_ + 3 < board.size_ && board.board_[i_][j_].IsAvailableToSet() &&
      board.board_[i_][j_ + 1].IsAvailableToSet() && board.board_[i_][j_ + 2].IsAvailableToSet() &&
      board.board_[i_][j_ + 3].IsAvailableToSet()) {
    board.board_[i_][j_] = Constants().ShipCell(this, board.board_[i_][j_].GetCoordinates());
    board.board_[i_][j_ + 1] = Constants().ShipCell(this, board.board_[i_][j_ + 1].GetCoordinates());
    board.board_[i_][j_ + 2] = Constants().ShipCell(this, board.board_[i_][j_ + 2].GetCoordinates());
    board.board_[i_][j_ + 3] = Constants().ShipCell(this, board.board_[i_][j_ + 3].GetCoordinates());
    for (int i = 0; i < board.size_; ++i) {
      for (int j = 0; j < board.size_; ++j) {
        if (board.board_[i][j].GetPtr() != nullptr) {
          continue;
        } else {
          board.board_[i][j] = Constants().BoardCell(board.board_[i][j].GetCoordinates());
        }
      }
    }
    board.board_[i_][j_] = Constants().ShipCell(nullptr, board.board_[i_][j_].GetCoordinates());
    board.board_[i_][j_ + 1] = Constants().ShipCell(nullptr, board.board_[i_][j_ + 1].GetCoordinates());
    board.board_[i_][j_ + 2] = Constants().ShipCell(nullptr, board.board_[i_][j_ + 2].GetCoordinates());
    board.board_[i_][j_ + 3] = Constants().ShipCell(nullptr, board.board_[i_][j_ + 3].GetCoordinates());
  }
}

void Ship4::Set(sf::Event& event, Board& board) {
  int cell_size = 50 + 50 / 20;
  int i_ = std::floor((event.mouseButton.y - board.begin_.y_) / cell_size);
  int j_ = std::floor((event.mouseButton.x - board.begin_.x_) / cell_size);
  if (i_ >= 0 && i_ < board.size_ && j_ >= 0 && j_ + 3 < board.size_) {
    board.board_[i_][j_] = Constants().ShipCell(this, board.board_[i_][j_].GetCoordinates());
    board.board_[i_][j_ + 1] = Constants().ShipCell(this, board.board_[i_][j_ + 1].GetCoordinates());
    board.board_[i_][j_ + 2] = Constants().ShipCell(this, board.board_[i_][j_ + 2].GetCoordinates());
    board.board_[i_][j_ + 3] = Constants().ShipCell(this, board.board_[i_][j_ + 3].GetCoordinates());
  }
}
