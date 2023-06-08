WIP UE5.2 UMG C++


** 弾薬や体力を取得する前に、まず 3 つの武器をすべて取得してください **

** マウスを右クリックして武器を切り替えます **

** Maya でモデル化されたメッシュ **



PlayerController はウィジェットを作成し、ビューポートに追加します。

MainMenu はテクスチャをロードし、画像とボタンのスタイルを設定します。

InGameHud はテクスチャをロードし、HUD を設定します。

InGameHudはWeaponWidgetクラスとInfoProgressBarクラスを使用してデータやアニメーションを設定します。

弾薬ピックアップ クラスは、PlayerCharacter の武器の現在および最大弾薬のデータを設定します。
PlayerController->InGameHUDInstance を通じて WeaponWidget テキストを更新します。

武器のオーバーラップは PlayerCharacter にブロードキャストされ、武器が配列に追加されます。

PlayerCharacter は PlayerController->InGameHUDInstance を呼び出して、対応するウィジェットを表示します。