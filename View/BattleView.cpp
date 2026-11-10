#include "BattleView.h"
#include <iostream>

void BattleView::ShowMessage(const std::string& message) const
{
    std::cout << message << std::endl;
}

void BattleView::ShowError(const std::string& message) const
{
    std::cerr << "エラー: " << message << std::endl;
}

void BattleView::ShowStatus(const std::string& player, int hp, const std::string& enemy,
                            int enemyHP) const
{
    std::cout << "\nプレイヤー: " << player << " HP=" << hp << "\n敵: " << enemy
              << " HP=" << enemyHP << std::endl;
}

void BattleView::ShowSpawn(const std::string& name, int hp) const
{
    std::cout << "敵が出現した: " << name << " HP=" << hp << std::endl;
}

void BattleView::ShowCommands() const
{
    ShowMessage("あなたのターン。選択してください:\n1: 攻撃  2: 薬  3: 逃げる");
}

void BattleView::ShowInvalidInput() const
{
    std::cout << "1〜3の番号を入力してください: ";
}

void BattleView::ShowAttack(const std::string& attacker, const std::string& target, int damage,
                            int hp) const
{
    std::cout << "-> " << attacker << " が " << target << " に攻撃！ " << damage
              << " のダメージ！ 残り HP=" << hp << std::endl;
}

void BattleView::ShowDefeated(const std::string& name) const
{
    std::cout << "-> " << name << " は倒れた！" << std::endl;
}

void BattleView::ShowHeal(const std::string& name, int hp, int maxHP) const
{
    std::cout << "-> " << name << " は薬で回復した！ 現在 HP=" << hp << "/" << maxHP << std::endl;
}
