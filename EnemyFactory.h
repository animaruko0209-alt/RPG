#pragma once

#include <memory>
#include <string>
#include "Enemy.h"
#include "ObjectPool.h"
#include "DataTable.h"

class EnemyFactory
{
public:
    EnemyFactory(std::shared_ptr<ObjectPool<Enemy>> pool, const DataTable& table);
    // 生成（unique_ptr を受け取り、破棄時にプールへ戻る）
    std::unique_ptr<Enemy, std::function<void(Enemy*)>> Create(const std::string& type);

private:
    std::shared_ptr<ObjectPool<Enemy>> pool_;
    const DataTable& table_;
};

