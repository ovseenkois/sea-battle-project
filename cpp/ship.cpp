#include "../headers/ship.h"
#include "../headers/constants.h"

std::pair<int, int> CursorCoordinatesMove(sf::Event& event, Board& board) {
  double cell_size = 50 + 5;
  int i_ = std::floor(static_cast<double>(event.mouseMove.y - board.begin_.y_) / cell_size);
  int j_ = std::floor(static_cast<double>(event.mouseMove.x - board.begin_.x_) / cell_size);
  return {i_, j_};
}

std::pair<int, int> CursorCoordinatesSet(sf::Event& event, Board& board) {
  double cell_size = 50 + 5;
  int i_ = std::floor(static_cast<double>(event.mouseButton.y - board.begin_.y_) / cell_size);
  int j_ = std::floor(static_cast<double>(event.mouseButton.x - board.begin_.x_) / cell_size);
  return {i_, j_};
}

std::pair<int, int> CursorCoordinatesRotate(sf::Event& event, Board& board, sf::RenderWindow& window) {
  int cell_size = 50 + 5;
  int i_ = std::floor((sf::Mouse::getPosition(window).y - board.begin_.y_) / cell_size);
  int j_ = std::floor((sf::Mouse::getPosition(window).x - board.begin_.x_) / cell_size);
  return {i_, j_};
}

bool Ship1::CanStay(int i_, int j_, Board& board) {
  return i_ >= 0 && i_ < board.size_ && j_ >= 0 && j_ < board.size_ && board.close_board_[i_][j_].IsAvailableToSet();
}

void Ship1::SetBoundaries(int i_, int j_, Board& board) {
  for (int i = i_ - 1; i <= i_ + 1; ++i) {
    for (int j = j_ - 1; j <= j_ + 1; ++j) {
      if (i >= 0 && i < board.size_ && j >= 0 && j < board.size_ && !(i == i_ && j == j_)) {
        board.close_board_[i][j].SetAvailable(false);
        board.close_board_[i][j].SetTemporary(false);
      }
    }
  }
}

void Ship1::Move(sf::Event& event, Board& board) {
  int i_ = CursorCoordinatesMove(event, board).first;
  int j_ = CursorCoordinatesMove(event, board).second;
  board.Clear();
  if (CanStay(i_, j_, board)) {
    board.close_board_[i_][j_] = Constants::ShipCell(nullptr, board.close_board_[i_][j_].GetCoordinates());
  }
}

bool Ship1::Set(sf::Event& event, Board& board) {
  int i_ = CursorCoordinatesSet(event, board).first;
  int j_ = CursorCoordinatesSet(event, board).second;
  if (CanStay(i_, j_, board)) {
    board.close_board_[i_][j_] = Constants::ShipCell(this, board.close_board_[i_][j_].GetCoordinates());
    SetBoundaries(i_, j_, board);
    begin_ = Point(i_, j_);
    return true;
  }
  return false;
}

bool Ship1::ShipDestroyed(Board& board) {
  auto i_ = begin_.x_;
  auto j_ = begin_.y_;
  return board.open_board_[i_][j_].IsDestroyed();
}

void Ship1::SetHitBoundaries(Board& board) {
  auto i_ = begin_.x_;
  auto j_ = begin_.y_;
  for (int i = i_ - 1; i <= i_ + 1; ++i) {
    for (int j = j_ - 1; j <= j_ + 1; ++j) {
      if (i >= 0 && i < board.size_ && j >= 0 && j < board.size_ && board.close_board_[i][j].GetPtr() == nullptr) {
        board.open_board_[i][j] = Constants::MissCell(board.open_board_[i][j].GetCoordinates());
      }
    }
  }
}

bool Ship2::CanStay(int i_, int j_, Board& board) {
  if (orientation_ == RIGHT) {
    return i_ >= 0 && i_ < board.size_ && j_ >= 0 && j_ + 1 < board.size_ &&
           board.close_board_[i_][j_].IsAvailableToSet() && board.close_board_[i_][j_ + 1].IsAvailableToSet();
  }
  return i_ >= 0 && i_ + 1 < board.size_ && j_ >= 0 && j_ < board.size_ &&
         board.close_board_[i_][j_].IsAvailableToSet() && board.close_board_[i_ + 1][j_].IsAvailableToSet();
}

void Ship2::SetBoundaries(int i_, int j_, Board& board) {
  int begin_i = i_ - 1;
  int begin_j = j_ - 1;
  int end_i;
  int end_j;
  if (orientation_ == RIGHT) {
    end_i = i_ + 1;
    end_j = j_ + 2;
  } else {
    end_i = i_ + 2;
    end_j = j_ + 1;
  }
  for (int i = begin_i; i <= end_i; ++i) {
    for (int j = begin_j; j <= end_j; ++j) {
      if (i >= 0 && i < board.size_ && j >= 0 && j < board.size_ && !(i == i_ && j == j_)) {
        board.close_board_[i][j].SetAvailable(false);
        board.close_board_[i][j].SetTemporary(false);
      }
    }
  }
}

void Ship2::Move(sf::Event& event, Board& board) {
  int i_ = CursorCoordinatesMove(event, board).first;
  int j_ = CursorCoordinatesMove(event, board).second;
  board.Clear();
  if (orientation_ == RIGHT) {
    if (CanStay(i_, j_, board)) {
      board.close_board_[i_][j_] = Constants::ShipCell(nullptr, board.close_board_[i_][j_].GetCoordinates());
      board.close_board_[i_][j_ + 1] = Constants::ShipCell(nullptr, board.close_board_[i_][j_ + 1].GetCoordinates());
    }
  } else if (orientation_ == DOWN) {
    if (CanStay(i_, j_, board)) {
      board.close_board_[i_][j_] = Constants::ShipCell(nullptr, board.close_board_[i_][j_].GetCoordinates());
      board.close_board_[i_ + 1][j_] = Constants::ShipCell(nullptr, board.close_board_[i_ + 1][j_].GetCoordinates());
    }
  }
}

bool Ship2::Set(sf::Event& event, Board& board) {
  int i_ = CursorCoordinatesSet(event, board).first;
  int j_ = CursorCoordinatesSet(event, board).second;
  if (orientation_ == RIGHT) {
    if (CanStay(i_, j_, board)) {
      board.close_board_[i_][j_] = Constants::ShipCell(this, board.close_board_[i_][j_].GetCoordinates());
      board.close_board_[i_][j_ + 1] = Constants::ShipCell(this, board.close_board_[i_][j_ + 1].GetCoordinates());
      SetBoundaries(i_, j_, board);
      begin_ = Point(i_, j_);
      return true;
    }
  } else if (orientation_ == DOWN) {
    if (CanStay(i_, j_, board)) {
      board.close_board_[i_][j_] = Constants::ShipCell(this, board.close_board_[i_][j_].GetCoordinates());
      board.close_board_[i_ + 1][j_] = Constants::ShipCell(this, board.close_board_[i_ + 1][j_].GetCoordinates());
      SetBoundaries(i_, j_, board);
      begin_ = Point(i_, j_);
      return true;
    }
  }
  return false;
}

void Ship2::Rotate(sf::Event& event, Board& board, sf::RenderWindow& window) {
  int i_ = CursorCoordinatesRotate(event, board, window).first;
  int j_ = CursorCoordinatesRotate(event, board, window).second;
  if (event.key.code == sf::Keyboard::R) {
    if (orientation_ == RIGHT) {
      orientation_ = DOWN;
    } else {
      orientation_ = RIGHT;
    }
    board.Clear();
    if (orientation_ == RIGHT) {
      if (CanStay(i_, j_, board)) {
        board.close_board_[i_][j_] = Constants::ShipCell(nullptr, board.close_board_[i_][j_].GetCoordinates());
        board.close_board_[i_][j_ + 1] = Constants::ShipCell(nullptr, board.close_board_[i_][j_ + 1].GetCoordinates());
      }
    } else if (orientation_ == DOWN) {
      if (CanStay(i_, j_, board)) {
        board.close_board_[i_][j_] = Constants::ShipCell(nullptr, board.close_board_[i_][j_].GetCoordinates());
        board.close_board_[i_ + 1][j_] = Constants::ShipCell(nullptr, board.close_board_[i_ + 1][j_].GetCoordinates());
      }
    }
  }
}

bool Ship2::ShipDestroyed(Board& board) {
  auto i_ = begin_.x_;
  auto j_ = begin_.y_;
  if (orientation_ == RIGHT) {
    return board.open_board_[i_][j_].IsDestroyed() && board.open_board_[i_][j_ + 1].IsDestroyed();
  } else {
    return board.open_board_[i_][j_].IsDestroyed() && board.open_board_[i_ + 1][j_].IsDestroyed();
  }
}

void Ship2::SetHitBoundaries(Board& board) {
  auto i_ = begin_.x_;
  auto j_ = begin_.y_;
  int begin_i = i_ - 1;
  int begin_j = j_ - 1;
  int end_i;
  int end_j;
  if (orientation_ == RIGHT) {
    end_i = i_ + 1;
    end_j = j_ + 2;
  } else {
    end_i = i_ + 2;
    end_j = j_ + 1;
  }
  for (int i = begin_i; i <= end_i; ++i) {
    for (int j = begin_j; j <= end_j; ++j) {
      if (i >= 0 && i < board.size_ && j >= 0 && j < board.size_ && board.close_board_[i][j].GetPtr() == nullptr) {
        board.open_board_[i][j] = Constants::MissCell(board.open_board_[i][j].GetCoordinates());
      }
    }
  }
}

bool Ship3::CanStay(int i_, int j_, Board& board) {
  if (orientation_ == RIGHT) {
    return i_ >= 0 && i_ < board.size_ && j_ >= 0 && j_ + 2 < board.size_ &&
           board.close_board_[i_][j_].IsAvailableToSet() && board.close_board_[i_][j_ + 1].IsAvailableToSet() &&
           board.close_board_[i_][j_ + 2].IsAvailableToSet();
  }
  return i_ >= 0 && i_ + 2 < board.size_ && j_ >= 0 && j_ < board.size_ &&
         board.close_board_[i_][j_].IsAvailableToSet() && board.close_board_[i_ + 1][j_].IsAvailableToSet() &&
         board.close_board_[i_ + 2][j_].IsAvailableToSet();
}

void Ship3::SetBoundaries(int i_, int j_, Board& board) {
  int begin_i = i_ - 1;
  int begin_j = j_ - 1;
  int end_i;
  int end_j;
  if (orientation_ == RIGHT) {
    end_i = i_ + 1;
    end_j = j_ + 3;
  } else {
    end_i = i_ + 3;
    end_j = j_ + 1;
  }
  for (int i = begin_i; i <= end_i; ++i) {
    for (int j = begin_j; j <= end_j; ++j) {
      if (i >= 0 && i < board.size_ && j >= 0 && j < board.size_ && !(i == i_ && j == j_)) {
        board.close_board_[i][j].SetAvailable(false);
        board.close_board_[i][j].SetTemporary(false);
      }
    }
  }
}

void Ship3::Move(sf::Event& event, Board& board) {
  int i_ = CursorCoordinatesMove(event, board).first;
  int j_ = CursorCoordinatesMove(event, board).second;
  board.Clear();
  if (orientation_ == RIGHT) {
    if (CanStay(i_, j_, board)) {
      board.close_board_[i_][j_] = Constants::ShipCell(nullptr, board.close_board_[i_][j_].GetCoordinates());
      board.close_board_[i_][j_ + 1] = Constants::ShipCell(nullptr, board.close_board_[i_][j_ + 1].GetCoordinates());
      board.close_board_[i_][j_ + 2] = Constants::ShipCell(nullptr, board.close_board_[i_][j_ + 2].GetCoordinates());
    }
  } else if (orientation_ == DOWN) {
    if (CanStay(i_, j_, board)) {
      board.close_board_[i_][j_] = Constants::ShipCell(nullptr, board.close_board_[i_][j_].GetCoordinates());
      board.close_board_[i_ + 1][j_] = Constants::ShipCell(nullptr, board.close_board_[i_ + 1][j_].GetCoordinates());
      board.close_board_[i_ + 2][j_] = Constants::ShipCell(nullptr, board.close_board_[i_ + 2][j_].GetCoordinates());
    }
  }
}

bool Ship3::Set(sf::Event& event, Board& board) {
  int i_ = CursorCoordinatesSet(event, board).first;
  int j_ = CursorCoordinatesSet(event, board).second;
  if (orientation_ == RIGHT) {
    if (CanStay(i_, j_, board)) {
      board.close_board_[i_][j_] = Constants::ShipCell(this, board.close_board_[i_][j_].GetCoordinates());
      board.close_board_[i_][j_ + 1] = Constants::ShipCell(this, board.close_board_[i_][j_ + 1].GetCoordinates());
      board.close_board_[i_][j_ + 2] = Constants::ShipCell(this, board.close_board_[i_][j_ + 2].GetCoordinates());
      SetBoundaries(i_, j_, board);
      begin_ = Point(i_, j_);
      return true;
    }
  } else if (orientation_ == DOWN) {
    if (CanStay(i_, j_, board)) {
      board.close_board_[i_][j_] = Constants::ShipCell(this, board.close_board_[i_][j_].GetCoordinates());
      board.close_board_[i_ + 1][j_] = Constants::ShipCell(this, board.close_board_[i_ + 1][j_].GetCoordinates());
      board.close_board_[i_ + 2][j_] = Constants::ShipCell(this, board.close_board_[i_ + 2][j_].GetCoordinates());
      SetBoundaries(i_, j_, board);
      begin_ = Point(i_, j_);
      return true;
    }
  }
  return false;
}

void Ship3::Rotate(sf::Event& event, Board& board, sf::RenderWindow& window) {
  int i_ = CursorCoordinatesRotate(event, board, window).first;
  int j_ = CursorCoordinatesRotate(event, board, window).second;
  if (event.key.code == sf::Keyboard::R) {
    if (orientation_ == RIGHT) {
      orientation_ = DOWN;
    } else {
      orientation_ = RIGHT;
    }
    board.Clear();
    if (orientation_ == RIGHT) {
      if (CanStay(i_, j_, board)) {
        board.close_board_[i_][j_] = Constants::ShipCell(nullptr, board.close_board_[i_][j_].GetCoordinates());
        board.close_board_[i_][j_ + 1] = Constants::ShipCell(nullptr, board.close_board_[i_][j_ + 1].GetCoordinates());
        board.close_board_[i_][j_ + 2] = Constants::ShipCell(nullptr, board.close_board_[i_][j_ + 2].GetCoordinates());
      }
    } else if (orientation_ == DOWN) {
      if (CanStay(i_, j_, board)) {
        board.close_board_[i_][j_] = Constants::ShipCell(nullptr, board.close_board_[i_][j_].GetCoordinates());
        board.close_board_[i_ + 1][j_] = Constants::ShipCell(nullptr, board.close_board_[i_ + 1][j_].GetCoordinates());
        board.close_board_[i_ + 2][j_] = Constants::ShipCell(nullptr, board.close_board_[i_ + 2][j_].GetCoordinates());
      }
    }
  }
}

bool Ship3::ShipDestroyed(Board& board) {
  auto i_ = begin_.x_;
  auto j_ = begin_.y_;
  if (orientation_ == RIGHT) {
    return board.open_board_[i_][j_].IsDestroyed() && board.open_board_[i_][j_ + 1].IsDestroyed() &&
           board.open_board_[i_][j_ + 2].IsDestroyed();
  } else {
    return board.open_board_[i_][j_].IsDestroyed() && board.open_board_[i_ + 1][j_].IsDestroyed() &&
           board.open_board_[i_ + 2][j_].IsDestroyed();
  }
}

void Ship3::SetHitBoundaries(Board& board) {
  auto i_ = begin_.x_;
  auto j_ = begin_.y_;
  int begin_i = i_ - 1;
  int begin_j = j_ - 1;
  int end_i;
  int end_j;
  if (orientation_ == RIGHT) {
    end_i = i_ + 1;
    end_j = j_ + 3;
  } else {
    end_i = i_ + 3;
    end_j = j_ + 1;
  }
  for (int i = begin_i; i <= end_i; ++i) {
    for (int j = begin_j; j <= end_j; ++j) {
      if (i >= 0 && i < board.size_ && j >= 0 && j < board.size_ && board.close_board_[i][j].GetPtr() == nullptr) {
        board.open_board_[i][j] = Constants::MissCell(board.open_board_[i][j].GetCoordinates());
      }
    }
  }
}

bool Ship4::CanStay(int i_, int j_, Board& board) {
  if (orientation_ == RIGHT) {
    return i_ >= 0 && i_ < board.size_ && j_ >= 0 && j_ + 3 < board.size_ &&
           board.close_board_[i_][j_].IsAvailableToSet() && board.close_board_[i_][j_ + 1].IsAvailableToSet() &&
           board.close_board_[i_][j_ + 2].IsAvailableToSet() && board.close_board_[i_][j_ + 3].IsAvailableToSet();
  }
  return i_ >= 0 && i_ + 3 < board.size_ && j_ >= 0 && j_ < board.size_ &&
         board.close_board_[i_][j_].IsAvailableToSet() && board.close_board_[i_ + 1][j_].IsAvailableToSet() &&
         board.close_board_[i_ + 2][j_].IsAvailableToSet() && board.close_board_[i_ + 3][j_].IsAvailableToSet();
}

void Ship4::SetBoundaries(int i_, int j_, Board& board) {
  int begin_i = i_ - 1;
  int begin_j = j_ - 1;
  int end_i;
  int end_j;
  if (orientation_ == RIGHT) {
    end_i = i_ + 1;
    end_j = j_ + 4;
  } else {
    end_i = i_ + 4;
    end_j = j_ + 1;
  }
  for (int i = begin_i; i <= end_i; ++i) {
    for (int j = begin_j; j <= end_j; ++j) {
      if (i >= 0 && i < board.size_ && j >= 0 && j < board.size_ && !(i == i_ && j == j_)) {
        board.close_board_[i][j].SetAvailable(false);
        board.close_board_[i][j].SetTemporary(false);
      }
    }
  }
}

void Ship4::Move(sf::Event& event, Board& board) {
  int i_ = CursorCoordinatesMove(event, board).first;
  int j_ = CursorCoordinatesMove(event, board).second;
  board.Clear();
  if (orientation_ == RIGHT) {
    if (CanStay(i_, j_, board)) {
      board.close_board_[i_][j_] = Constants::ShipCell(nullptr, board.close_board_[i_][j_].GetCoordinates());
      board.close_board_[i_][j_ + 1] = Constants::ShipCell(nullptr, board.close_board_[i_][j_ + 1].GetCoordinates());
      board.close_board_[i_][j_ + 2] = Constants::ShipCell(nullptr, board.close_board_[i_][j_ + 2].GetCoordinates());
      board.close_board_[i_][j_ + 3] = Constants::ShipCell(nullptr, board.close_board_[i_][j_ + 3].GetCoordinates());
    }
  } else if (orientation_ == DOWN) {
    if (CanStay(i_, j_, board)) {
      board.close_board_[i_][j_] = Constants::ShipCell(nullptr, board.close_board_[i_][j_].GetCoordinates());
      board.close_board_[i_ + 1][j_] = Constants::ShipCell(nullptr, board.close_board_[i_ + 1][j_].GetCoordinates());
      board.close_board_[i_ + 2][j_] = Constants::ShipCell(nullptr, board.close_board_[i_ + 2][j_].GetCoordinates());
      board.close_board_[i_ + 3][j_] = Constants::ShipCell(nullptr, board.close_board_[i_ + 3][j_].GetCoordinates());
    }
  }
}

bool Ship4::Set(sf::Event& event, Board& board) {
  int i_ = CursorCoordinatesSet(event, board).first;
  int j_ = CursorCoordinatesSet(event, board).second;
  if (orientation_ == RIGHT) {
    if (CanStay(i_, j_, board)) {
      board.close_board_[i_][j_] = Constants::ShipCell(this, board.close_board_[i_][j_].GetCoordinates());
      board.close_board_[i_][j_ + 1] = Constants::ShipCell(this, board.close_board_[i_][j_ + 1].GetCoordinates());
      board.close_board_[i_][j_ + 2] = Constants::ShipCell(this, board.close_board_[i_][j_ + 2].GetCoordinates());
      board.close_board_[i_][j_ + 3] = Constants::ShipCell(this, board.close_board_[i_][j_ + 3].GetCoordinates());
      SetBoundaries(i_, j_, board);
      begin_ = Point(i_, j_);
      return true;
    }
  } else if (orientation_ == DOWN) {
    if (CanStay(i_, j_, board)) {
      board.close_board_[i_][j_] = Constants::ShipCell(this, board.close_board_[i_][j_].GetCoordinates());
      board.close_board_[i_ + 1][j_] = Constants::ShipCell(this, board.close_board_[i_ + 1][j_].GetCoordinates());
      board.close_board_[i_ + 2][j_] = Constants::ShipCell(this, board.close_board_[i_ + 2][j_].GetCoordinates());
      board.close_board_[i_ + 3][j_] = Constants::ShipCell(this, board.close_board_[i_ + 3][j_].GetCoordinates());
      SetBoundaries(i_, j_, board);
      begin_ = Point(i_, j_);
      return true;
    }
  }
  return false;
}

void Ship4::Rotate(sf::Event& event, Board& board, sf::RenderWindow& window) {
  int i_ = CursorCoordinatesRotate(event, board, window).first;
  int j_ = CursorCoordinatesRotate(event, board, window).second;
  if (event.key.code == sf::Keyboard::R) {
    if (orientation_ == RIGHT) {
      orientation_ = DOWN;
    } else {
      orientation_ = RIGHT;
    }
    board.Clear();
    if (orientation_ == RIGHT) {
      if (CanStay(i_, j_, board)) {
        board.close_board_[i_][j_] = Constants::ShipCell(nullptr, board.close_board_[i_][j_].GetCoordinates());
        board.close_board_[i_][j_ + 1] = Constants::ShipCell(nullptr, board.close_board_[i_][j_ + 1].GetCoordinates());
        board.close_board_[i_][j_ + 2] = Constants::ShipCell(nullptr, board.close_board_[i_][j_ + 2].GetCoordinates());
        board.close_board_[i_][j_ + 3] = Constants::ShipCell(nullptr, board.close_board_[i_][j_ + 3].GetCoordinates());
      }
    } else if (orientation_ == DOWN) {
      if (CanStay(i_, j_, board)) {
        board.close_board_[i_][j_] = Constants::ShipCell(nullptr, board.close_board_[i_][j_].GetCoordinates());
        board.close_board_[i_ + 1][j_] = Constants::ShipCell(nullptr, board.close_board_[i_ + 1][j_].GetCoordinates());
        board.close_board_[i_ + 2][j_] = Constants::ShipCell(nullptr, board.close_board_[i_ + 2][j_].GetCoordinates());
        board.close_board_[i_ + 3][j_] = Constants::ShipCell(nullptr, board.close_board_[i_ + 3][j_].GetCoordinates());
      }
    }
  }
}

bool Ship4::ShipDestroyed(Board& board) {
  auto i_ = begin_.x_;
  auto j_ = begin_.y_;
  if (orientation_ == RIGHT) {
    return board.open_board_[i_][j_].IsDestroyed() && board.open_board_[i_][j_ + 1].IsDestroyed() &&
           board.open_board_[i_][j_ + 2].IsDestroyed() && board.open_board_[i_][j_ + 3].IsDestroyed();
  } else {
    return board.open_board_[i_][j_].IsDestroyed() && board.open_board_[i_ + 1][j_].IsDestroyed() &&
           board.open_board_[i_ + 2][j_].IsDestroyed() && board.open_board_[i_ + 3][j_].IsDestroyed();
  }
}

void Ship4::SetHitBoundaries(Board& board) {
  auto i_ = begin_.x_;
  auto j_ = begin_.y_;
  int begin_i = i_ - 1;
  int begin_j = j_ - 1;
  int end_i;
  int end_j;
  if (orientation_ == RIGHT) {
    end_i = i_ + 1;
    end_j = j_ + 4;
  } else {
    end_i = i_ + 4;
    end_j = j_ + 1;
  }
  for (int i = begin_i; i <= end_i; ++i) {
    for (int j = begin_j; j <= end_j; ++j) {
      if (i >= 0 && i < board.size_ && j >= 0 && j < board.size_ && board.close_board_[i][j].GetPtr() == nullptr) {
        board.open_board_[i][j] = Constants::MissCell(board.open_board_[i][j].GetCoordinates());
      }
    }
  }
}