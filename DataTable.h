#pragma once

#include <string>
#include <unordered_map>

struct EnemyData
{
    std::string type;
    int hp;
    int attack;
    float speed;
};

class DataTable
{
public:
    DataTable();
    const EnemyData* GetEnemyData(const std::string& type) const;

private:
    std::unordered_map<std::string, EnemyData> enemies_;
};

