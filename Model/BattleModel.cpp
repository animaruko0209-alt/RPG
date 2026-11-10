#include "BattleModel.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

BattleModel::BattleModel()
    : player_("勇者", 100, 12), pool_(std::make_shared<ObjectPool<Enemy>>(5)),
      factory_(pool_, table_)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void BattleModel::SpawnEnemy(const std::string& type)
{
    enemies_.push_back(factory_.Create(type));
}

void BattleModel::Update(float dt)
{
    player_.Update(dt);
    for (auto& enemy : enemies_)
    {
        enemy->Update(dt);
    }
    RemoveDeadEnemies();
}

void BattleModel::AttackEnemy(Enemy& target)
{
    target.TakeDamage(player_.GetAttack());
}

void BattleModel::AttackPlayer(const Enemy& enemy)
{
    player_.TakeDamage(enemy.GetAttack());
}

void BattleModel::HealPlayer()
{
    player_.Heal(30);
}

bool BattleModel::TryEscape()
{
    return std::rand() % 100 < 60;
}

void BattleModel::RemoveDeadEnemies()
{
    enemies_.erase(std::remove_if(enemies_.begin(), enemies_.end(),
                                  [](const EnemyPtr& enemy) { return enemy->IsDead(); }),
                   enemies_.end());
}

bool BattleModel::IsFinished() const
{
    return player_.GetHP() <= 0 || enemies_.empty();
}
