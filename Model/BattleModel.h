#pragma once
#include "Player.h"
#include "EnemyFactory.h"
#include <vector>

// Model：戦闘の状態とルールを管理する。画面表示や入力処理は行わない。
class BattleModel
{
public:
    using EnemyPtr = std::unique_ptr<Enemy, std::function<void(Enemy*)>>;

    BattleModel();
    void SpawnEnemy(const std::string& type);
    void Update(float dt);

    // 状態の参照（外からプレイヤーや敵の一覧を書き換えない）
    const Player& GetPlayer() const
    {
        return player_;
    }

    const std::vector<EnemyPtr>& GetEnemies() const
    {
        return enemies_;
    }

    // 戦闘のルールに従って状態を更新する
    void AttackEnemy(Enemy& target);
    void AttackPlayer(const Enemy& enemy);
    void HealPlayer();
    bool TryEscape();
    void RemoveDeadEnemies();
    bool IsFinished() const;

private:
    Player player_;
    DataTable table_;
    std::shared_ptr<ObjectPool<Enemy>> pool_;
    EnemyFactory factory_;
    std::vector<EnemyPtr> enemies_;
};
