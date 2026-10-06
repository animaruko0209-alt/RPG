#include "GameManager.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

GameManager& GameManager::Instance()
{
    static GameManager inst;
    return inst;
}

GameManager::GameManager()
    : player_("勇者", 100, 12)
{
}

GameManager::~GameManager() = default;

void GameManager::Initialize()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    enemyPool_ = std::make_shared<ObjectPool<Enemy>>(5); // 初期プールサイズ
    factory_ = std::make_unique<EnemyFactory>(enemyPool_, table_);
}

void GameManager::SpawnEnemy(const std::string& type)
{
    try
    {
        auto enemy = factory_->Create(type);
        std::cout << "敵を出現させた: " << enemy->GetType() << " HP=" << enemy->GetHP() << std::endl;
        activeEnemies_.push_back(std::move(enemy));
    }
    catch (const std::exception& e)
    {
        std::cerr << "出現エラー: " << e.what() << std::endl;
    }
}

void GameManager::Update(float dt)
{
    player_.Update(dt);

    for (auto it = activeEnemies_.begin(); it != activeEnemies_.end();)
    {
        (*it)->Update(dt);
        if ((*it)->IsDead())
        {
            std::cout << "敵 " << (*it)->GetType() << " は倒れた。プールに戻します。" << std::endl;
            it = activeEnemies_.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void GameManager::RunBattleLoop()
{
    if (activeEnemies_.empty())
    {
        std::cout << "戦闘対象の敵がいません。" << std::endl;
        return;
    }

    std::cout << "=== 戦闘開始 ===" << std::endl;

    while (player_.GetHP() > 0 && !activeEnemies_.empty())
    {
        // ステータス表示（最初の敵をターゲットにする）
        std::cout << std::endl;
        std::cout << "プレイヤー: " << player_.GetName() << " HP=" << player_.GetHP() << std::endl;
        Enemy* target = activeEnemies_.front().get();
        std::cout << "敵: " << target->GetType() << " HP=" << target->GetHP() << std::endl;

        // プレイヤーのターン
        std::cout << "あなたのターン。選択してください:" << std::endl;
        std::cout << "1: 攻撃  2: 回復  3: 逃走" << std::endl;
        int choice = 0;
        while (!(std::cin >> choice) || choice < 1 || choice > 3)
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "1～3の番号を入力してください: ";
        }

        if (choice == 1)
        {
            // 攻撃
            int dmg = player_.GetAttack();
            std::cout << "-> " << player_.GetName() << " は " << target->GetType() << " に攻撃！" << std::endl;
            target->TakeDamage(dmg);

            if (target->IsDead())
            {
                // erase will call deleter and return to pool
                activeEnemies_.erase(activeEnemies_.begin());
            }
        }
        else if (choice == 2)
        {
            // 回復（固定値）
            player_.Heal(30);
        }
        else // 逃走
        {
            int roll = std::rand() % 100;
            if (roll < 60) // 60%で成功
            {
                std::cout << "-> 逃走に成功した！" << std::endl;
                return;
            }
            else
            {
                std::cout << "-> 逃走に失敗した！" << std::endl;
            }
        }

        // 敵ターン（生存している敵全員が攻撃）
        if (player_.GetHP() > 0)
        {
            for (auto it = activeEnemies_.begin(); it != activeEnemies_.end(); ++it)
            {
                Enemy* e = it->get();
                if (!e->IsDead())
                {
                    int edmg = e->GetAttack();
                    std::cout << "-> " << e->GetType() << " の攻撃！" << std::endl;
                    player_.TakeDamage(edmg);
                    if (player_.GetHP() <= 0) break;
                }
            }
        }

        // 敵の死体処理（もし戦闘中に複数倒れた場合）
        for (auto it = activeEnemies_.begin(); it != activeEnemies_.end();)
        {
            if ((*it)->IsDead())
                it = activeEnemies_.erase(it);
            else
                ++it;
        }
    }

    if (player_.GetHP() <= 0)
    {
        std::cout << "あなたは倒れた... ゲームオーバー" << std::endl;
    }
    else
    {
        std::cout << "戦闘に勝利した！" << std::endl;
    }
}
