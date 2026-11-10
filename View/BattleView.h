#pragma once
#include <string>

// View：Controllerから渡された値を表示する。Modelの変更や戦闘の判断は行わない。
class BattleView
{
public:
    void ShowMessage(const std::string& message) const;
    void ShowError(const std::string& message) const;
    void ShowStatus(const std::string& player, int hp, const std::string& enemy, int enemyHP) const;
    void ShowSpawn(const std::string& name, int hp) const;
    void ShowCommands() const;
    void ShowInvalidInput() const;
    void ShowAttack(const std::string& attacker, const std::string& target, int damage,
                    int hp) const;
    void ShowDefeated(const std::string& name) const;
    void ShowHeal(const std::string& name, int hp, int maxHP) const;
};
