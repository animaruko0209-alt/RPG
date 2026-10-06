#include "Player.h"
#include <iostream>

Player::Player()
    : name_("勇者")
    , hp_(100)
    , maxHp_(100)
    , attack_(12)
{
}

Player::Player(const std::string& name, int hp, int attack)
    : name_(name)
    , hp_(hp)
    , maxHp_(hp)
    , attack_(attack)
{
}

void Player::Update(float /*dt*/)
{
    // ターン制のため特にフレーム更新は簡易化
    std::cout << "[プレイヤー] " << name_ << " HP=" << hp_ << "/" << maxHp_ << std::endl;
}

void Player::TakeDamage(int d)
{
    hp_ -= d;
    if (hp_ < 0) hp_ = 0;
    std::cout << "-> " << name_ << " は " << d << " のダメージを受けた！ 現在 HP=" << hp_ << "/" << maxHp_ << std::endl;
}

void Player::Heal(int amount)
{
    hp_ += amount;
    if (hp_ > maxHp_) hp_ = maxHp_;
    std::cout << "-> " << name_ << " は " << amount << " 回復した！ 現在 HP=" << hp_ << "/" << maxHp_ << std::endl;
}

int Player::GetHP() const { return hp_; }
int Player::GetAttack() const { return attack_; }
const std::string& Player::GetName() const { return name_; }
