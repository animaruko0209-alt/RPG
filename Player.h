#pragma once

#include <string>

class Player
{
public:
    Player();
    Player(const std::string& name, int hp, int attack = 10);

    void Update(float dt);
    void TakeDamage(int d);
    void Heal(int amount);
    int GetHP() const;
    int GetAttack() const;
    const std::string& GetName() const;

private:
    std::string name_;
    int hp_;
    int maxHp_;
    int attack_;
};

