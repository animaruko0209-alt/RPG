// RPG.cpp : サンプルの簡易メインループ（ターン制デモ）
#include <iostream>
#include "GameManager.h"

int main()
{
    auto& gm = GameManager::Instance();
    gm.Initialize();

    // 敵をスポーン（データテーブルに基づく）
    gm.SpawnEnemy("スライム");
    gm.SpawnEnemy("ゴブリン");
	gm.SpawnEnemy("オーク");
	gm.SpawnEnemy("ドラゴン");

    // ターン制バトルループを実行（コンソールで選択）
    gm.RunBattleLoop();

    std::cout << "デモ終了。" << std::endl;
    return 0;
}

