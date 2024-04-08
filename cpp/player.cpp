#include "../headers/player.h"
#include <iostream>

void Aim::Move(sf::Event& event, Board& board) {
  int i_ = CursorCoordinatesMove(event, board).first;
  int j_ = CursorCoordinatesMove(event, board).second;
  board.Clear();
  if (i_ >= 0 && i_ < board.size_ && j_ >= 0 && j_ < board.size_ && board.open_board_[i_][j_].GetTemporary()) {
    board.open_board_[i_][j_] = Constants::ChooseCell(board.open_board_[i_][j_].GetCoordinates());
  }
}
Strikes Aim::Set(sf::Event& event, Board& board) {
  int i_ = CursorCoordinatesSet(event, board).first;
  int j_ = CursorCoordinatesSet(event, board).second;
  if (i_ >= 0 && i_ < board.size_ && j_ >= 0 && j_ < board.size_ && board.open_board_[i_][j_].GetTemporary()) {
    if (board.close_board_[i_][j_].GetPtr()) {
      board.open_board_[i_][j_] = Constants::HitCell(board.open_board_[i_][j_].GetCoordinates());
      board.open_board_[i_][j_].Destroy();
      return HIT;
    } else {
      board.open_board_[i_][j_] = Constants::MissCell(board.open_board_[i_][j_].GetCoordinates());
      return MISS;
    }
  }
  return FALSE;
}

// bool Aim::CanStay(int i_, int j_, Board& board) {}
// void Aim::SetBoundaries(int i_, int j_, Board& board) {}

Player::~Player() = default;

Player::Player(Board& board, std::unique_ptr<PlayerState> state)
    : board_(board), counter_(0), state_(std::move(state)), aim_(Aim()) {
  ships_.reserve(10);
  for (int i = 9; i >= 0; --i) {
    if (i <= 3) {
      ships_.push_back(std::unique_ptr<IShip>(new Ship1()));
    }
    if (i >= 4 && i <= 6) {
      ships_.push_back(std::unique_ptr<IShip>(new Ship2()));
    }
    if (i >= 7 && i <= 8) {
      ships_.push_back(std::unique_ptr<IShip>(new Ship3()));
    }
    if (i == 9) {
      ships_.push_back(std::unique_ptr<IShip>(new Ship4()));
    }
  }
}

void Player::MoveShip(sf::Event& event) {
  ships_[counter_]->Move(event, board_);
}
void Player::SetShip(sf::Event& event, Player& other_player) {
  if (ships_[counter_]->Set(event, board_)) {
    ++counter_;
  }
  if (counter_ == 10) {
    SetState(state_->Next());
    board_.Close();
    other_player.board_.Open();
    SendRequestToChangeState(other_player, other_player.state_->Next());
    board_.CopyCloseToOpen();
  }
}
void Player::RotateShip(sf::Event& event, sf::RenderWindow& window) {
  ships_[counter_]->Rotate(event, board_, window);
}

void Player::SetState(std::unique_ptr<PlayerState> state) {
  state_ = std::move(state);
}

void Player::Handle(sf::Event& event, sf::RenderWindow& window, Player& other_player) {
  state_->Handle(event, window, *this, other_player);
}

void Player::SendRequestToChangeState(Player& player, std::unique_ptr<PlayerState> state) {
  player.state_ = std::move(state);
}

void Player::Choose(sf::Event& event, Player& other_player) {
  board_.Open();
  other_player.board_.Close();
  aim_.Move(event, other_player.board_);
}

void Player::Strike(sf::Event& event, Player& other_player) {
  Strikes strike = aim_.Set(event, other_player.board_);
  if (strike == HIT) {
    other_player.CheckShips();
    return;
  } else if (strike == MISS) {
    SetState(state_->Next());
    SendRequestToChangeState(other_player, other_player.state_->Next());
  }
}

void Player::CheckShips() {
  for (size_t i = 0; i < ships_.size(); ++i) {
    if (ships_[i]->ShipDestroyed(board_)) {
      ships_[i]->SetHitBoundaries(board_);
    }
  }

}