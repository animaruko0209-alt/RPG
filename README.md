# RPG（MVC構成）

資料の「厨房・ホール・店長」の役割に沿って分割しています。

| 役割 | ファイル | 担当 |
| --- | --- | --- |
| Model（厨房） | Model/Player、Enemy | HP、攻撃力、回復、敵の状態遷移 |
| Model（厨房） | Model/BattleModel | 戦闘状態、攻撃、薬の回復量、逃走確率、敵の管理 |
| Model（厨房） | Model/DataTable、EnemyFactory、ObjectPool | 敵データ、生成、再利用 |
| View（ホール） | View/BattleView | ステータス、コマンド、戦闘結果の表示 |
| Controller（店長） | Controller/BattleController | 入力の解釈、プレイヤーと敵の行動順、ModelとViewへの指示 |
| 起動処理 | RPG.cpp | Model・View・Controllerの組み立て |

ControllerだけがModelとViewの両方を参照します。Modelは画面出力を行わず、Viewは渡された値を表示するだけです。表示の変更はBattleView、ダメージや回復のルール変更はModelで行います。

攻撃・薬・逃走、敵のステータス、オブジェクトプールは従来の仕様を維持しています。入力が終了した場合は戦闘ループを終了します。

Visual Studio 2022でRPG.slnを開いてビルドしてください。ソースはUTF-8（BOM付き）で統一し、全構成で /utf-8 を指定しています。Windowsコンソールも起動時にUTF-8へ設定します。
