#pragma once

#include <memory>
#include <vector>
#include <functional>
#include "Player.h"
#include "Enemy.h"
#include "ObjectPool.h"
#include "DataTable.h"
#include "EnemyFactory.h"

class GameManager
{
public:
    static GameManager& Instance();

    void Initialize();
    void SpawnEnemy(const std::string& type);
    void Update(float dt);

    // ターン制バトルループ（コンソール入力を行う）
    void RunBattleLoop();

private:
    GameManager();
    ~GameManager();

private:
    Player player_;
    DataTable table_;
    std::shared_ptr<ObjectPool<Enemy>> enemyPool_;
    std::unique_ptr<EnemyFactory> factory_;

    // 現在アクティブな敵（unique_ptr を保持することで自動的にプールへ戻る）
    std::vector<std::unique_ptr<Enemy, std::function<void(Enemy*)>>> activeEnemies_;
};

