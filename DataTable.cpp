#include "DataTable.h"

DataTable::DataTable()
{
    // デフォルトデータを登録（簡易データテーブル）
    enemies_.emplace("スライム", EnemyData{ "スライム", 5, 1, 1.0f });
    enemies_.emplace("ゴブリン", EnemyData{ "ゴブリン", 12, 3, 1.5f });
    enemies_.emplace("オーク", EnemyData{ "オーク", 25, 6, 0.8f });
	enemies_.emplace("ドラゴン", EnemyData{ "ドラゴン", 100, 15, 0.5f });
}

const EnemyData* DataTable::GetEnemyData(const std::string& type) const
{
    auto it = enemies_.find(type);
    if (it == enemies_.end()) return nullptr;
    return &it->second;
}
