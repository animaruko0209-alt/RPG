#include <iostream>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#endif
#include "Controller/BattleController.h"

int main()
{
#ifdef _WIN32
    // 日本語が文字化けしないよう、コンソールの文字コードを合わせる。
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    // MVCの各担当を作り、Controllerに接続する。
    BattleModel model;
    BattleView view;
    BattleController controller(model, view, std::cin);

    // データテーブルに登録されている敵を出現させる。
    controller.SpawnEnemy("スライム");
    controller.SpawnEnemy("ゴブリン");
    controller.SpawnEnemy("オーク");
    controller.SpawnEnemy("ドラゴン");

    // 入力と戦闘の進行はControllerに任せる。
    controller.RunBattleLoop();
    view.ShowMessage("デモ終了。");

    return 0;
}
