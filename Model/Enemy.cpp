#include "Enemy.h"

Enemy::Enemy()
    : type_("Unknown"), hp_(0), attack_(0), speed_(0.0f), state_(State::Idle), stateTimer_(0.0f)
{
}

Enemy::Enemy(const std::string& type, int hp, int attack, float speed)
{
    Init(type, hp, attack, speed);
}

void Enemy::Init(const std::string& type, int hp, int attack, float speed)
{
    type_ = type;
    hp_ = hp;
    attack_ = attack;
    speed_ = speed;
    state_ = State::Idle;
    stateTimer_ = 0.0f;
}

void Enemy::Update(float dt)
{
    if (state_ == State::Dead)
    {
        return;
    }

    stateTimer_ += dt;
    switch (state_)
    {
    case State::Idle:
        if (stateTimer_ > 1.0f)
        {
            ChangeState(State::Patrol);
        }
        break;
    case State::Patrol:
        if (stateTimer_ > 2.0f)
        {
            ChangeState(State::Attack);
        }
        break;
    case State::Attack:
        // ターン制の攻撃はBattleModelで処理する
        if (stateTimer_ > 3.0f)
        {
            ChangeState(State::Patrol);
        }
        break;
    case State::Dead:
        break;
    }
}

void Enemy::TakeDamage(int amount)
{
    hp_ -= amount;
    if (hp_ <= 0)
    {
        hp_ = 0;
        ChangeState(State::Dead);
    }
}

void Enemy::ChangeState(State newState)
{
    state_ = newState;
    stateTimer_ = 0.0f;
}

void Enemy::Reset()
{
    type_.clear();
    hp_ = 0;
    attack_ = 0;
    speed_ = 0.0f;
    state_ = State::Idle;
    stateTimer_ = 0.0f;
}

bool Enemy::IsDead() const
{
    return state_ == State::Dead;
}

const std::string& Enemy::GetType() const
{
    return type_;
}

int Enemy::GetHP() const
{
    return hp_;
}

int Enemy::GetAttack() const
{
    return attack_;
}
