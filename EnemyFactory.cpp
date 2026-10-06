#include "EnemyFactory.h"
#include <stdexcept>

EnemyFactory::EnemyFactory(std::shared_ptr<ObjectPool<Enemy>> pool, const DataTable& table)
    : pool_(pool)
    , table_(table)
{
}

std::unique_ptr<Enemy, std::function<void(Enemy*)>> EnemyFactory::Create(const std::string& type)
{
    const EnemyData* data = table_.GetEnemyData(type);
    if (!data)
    {
        throw std::runtime_error("Unknown enemy type: " + type);
    }

    auto enemyPtr = pool_->Acquire();
    enemyPtr->Init(data->type, data->hp, data->attack, data->speed);

    // Acquire ‚Í unique_ptr<T,Deleter> ‚ð•Ô‚·‚Ì‚Å‚»‚Ì‚Ü‚Ü•Ô‚·
    return enemyPtr;
}
