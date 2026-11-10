#include "BattleController.h"
#include <limits>
#include <exception>

BattleController::BattleController(BattleModel& model, BattleView& view, std::istream& input)
    : model_(model), view_(view), input_(input)
{
}

void BattleController::SpawnEnemy(const std::string& type)
{
    try
    {
        model_.SpawnEnemy(type);
        const auto& enemy = *model_.GetEnemies().back();
        view_.ShowSpawn(enemy.GetType(), enemy.GetHP());
    }
    catch (const std::exception& e)
    {
        view_.ShowError(e.what());
    }
}

bool BattleController::ReadCommand(int& choice)
{
    while (true)
    {
        if (input_ >> choice)
        {
            if (choice >= 1 && choice <= 3)
            {
                return true;
            }
        }
        else
        {
            if (input_.eof() || input_.bad())
            {
                return false;
            }
            input_.clear();
        }
        // 不正な入力を捨てて、次のコマンドを読み直す。
        input_.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        view_.ShowInvalidInput();
    }
}

void BattleController::RunBattleLoop()
{
    if (model_.GetEnemies().empty())
    {
        view_.ShowMessage("戦闘対象の敵がいません。");
        return;
    }
    view_.ShowMessage("=== 戦闘開始 ===");
    while (!model_.IsFinished())
    {
        const auto& player = model_.GetPlayer();
        auto& target = *model_.GetEnemies().front();

        // 1. 現在の状態とコマンドを表示する。
        view_.ShowStatus(player.GetName(), player.GetHP(), target.GetType(), target.GetHP());
        view_.ShowCommands();

        // 2. 入力を読み取り、選ばれた行動をModelに指示する。
        int choice;
        if (!ReadCommand(choice))
        {
            view_.ShowMessage("入力が終了したため、戦闘を終了します。");
            return;
        }

        if (choice == 1)
        {
            model_.AttackEnemy(target);
            view_.ShowAttack(player.GetName(), target.GetType(), player.GetAttack(),
                             target.GetHP());
            if (target.IsDead())
            {
                view_.ShowDefeated(target.GetType());
            }

            // 撃破メッセージを出してから、敵を一覧から取り除く。
            model_.RemoveDeadEnemies();
        }
        else if (choice == 2)
        {
            model_.HealPlayer();
            view_.ShowHeal(player.GetName(), player.GetHP(), player.GetMaxHP());
        }
        else
        {
            if (model_.TryEscape())
            {
                view_.ShowMessage("-> 逃走に成功した！");
                return;
            }
            view_.ShowMessage("-> 逃走に失敗した！");
        }

        // 3. 残っている敵が順番に攻撃する。
        for (const auto& enemy : model_.GetEnemies())
        {
            model_.AttackPlayer(*enemy);
            view_.ShowAttack(enemy->GetType(), player.GetName(), enemy->GetAttack(),
                             player.GetHP());
            if (player.GetHP() <= 0)
            {
                break;
            }
        }
    }

    // 4. 戦闘の終了結果を表示する。
    if (model_.GetPlayer().GetHP() <= 0)
    {
        view_.ShowMessage("あなたは倒れた... ゲームオーバー");
    }
    else
    {
        view_.ShowMessage("戦闘に勝利した！");
    }
}
