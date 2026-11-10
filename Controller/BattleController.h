#pragma once
#include "../Model/BattleModel.h"
#include "../View/BattleView.h"
#include <istream>

// Controller：入力を解釈し、Modelの更新とViewの表示を順番に指示する。
class BattleController
{
public:
    BattleController(BattleModel& model, BattleView& view, std::istream& input);

    void SpawnEnemy(const std::string& type);
    void RunBattleLoop();

private:
    bool ReadCommand(int& choice);

    BattleModel& model_;
    BattleView& view_;
    std::istream& input_;
};
