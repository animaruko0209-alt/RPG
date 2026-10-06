#pragma once

#include <string>

class Enemy
{
public:
    enum class State { Idle, Patrol, Attack, Dead };

    Enemy();
    Enemy(const std::string& type, int hp, int attack, float speed);

    // 初期化（プールから再利用）
    void Init(const std::string& type, int hp, int attack, float speed);

    // 毎フレーム更新（簡易）
    void Update(float dt);

    // ダメージを受ける（ターン制で使用）
    void TakeDamage(int amount);

    // プールに返す前のリセット
    void Reset();

    bool IsDead() const;
    const std::string& GetType() const;
    int GetHP() const;
    int GetAttack() const;

private:
    void ChangeState(State newState);

private:
    std::string type_;
    int hp_;
    int attack_;
    float speed_;
    State state_;
    float stateTimer_;
};

