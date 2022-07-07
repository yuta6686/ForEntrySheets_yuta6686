# ForEntrySheets_yuta6686
-------------------------------------------------------------------------------------------------------------------------------
# 構成
```mermaid
graph TB
	all((作品))
	dx2((2年DirectX))
	hew2((2年HEW))
	ngt((日本ゲーム大賞))
	bld((Blender))
	wpf((WPF))

	all --> ngt
	all --> hew2
	all --> dx2	
	all --> bld
	all --> wpf
		
	ngt --> ngt_sum1[Unity 2Dゲーム] --> 
	ntg_sum1[チーム制作<br>]-->ntg_sum2.5[<b>担当箇所</b>]-->
	ngt_sum2[タイトル<br>リザルト<br>シーン選択<br>エリア選択<br>フェード<br>シェーダ<br>アニメーション<br>など]
	hew2 --> hew2_sum1[Hal Event Week:</br>学内コンテスト]-->hew2_sum2[DirectX:2Dゲーム]
	--> hew2_sum3[チーム制作<br>担当箇所]
	--> hew2_sum4[ゲームのコア<br>エフェクト<br>など]
	dx2 --> dx2_sum1[DirectX:3Dゲーム]
	bld-->bld_sum1[独学]-->bld_sum2[制作物]-->
	bld_sum3[剣 </br>エフェクト </br>geometry node </br>shader node]
	wpf-->wpf_sum1[専科]-->wpf_sum2[制作物]-->wpf_sum3[アイコンエディタ]
	
```
-------------------------------------------------------------------------------------------------------------------------------


## 日本ゲーム大賞作品

### タイトル「***HopSlime***」

### 詳細情報

#### 期間
- 2022年3月1日～5月31日

#### チーム制作
- 人数：10人（プログラマ6名,プランナー1名,デザイナー3名)

#### どんなゲーム？

#### 担当箇所

- シーン
	- タイトルシーン
	- エリア選択シーン
	- ステージ選択シーン
	- リザルトシーン

- ゲーム
	- ギミック一部
	- ゴール演出

- その他
	- エフェクト
	- シェーダグラフによる特殊表現

#### こだわった点
- コインエフェクト
	- 種類を増やすことで、より見栄えをよくしようとした。
- スライムの反発エフェクト
	- シェーダグラフとうまく組み合わせて、作成した。
- タイトル、ゴール、選択シーンのアニメーション
	- UnityのAnimationを使用してキーフレームでのアニメーション制作をしました。
	
### スクリーンショット
![claer](https://user-images.githubusercontent.com/68798323/177542177-e7ffee3b-1614-4ce7-b85f-db5b44ce443a.png)
![SS_1-1](https://user-images.githubusercontent.com/68798323/177542190-a0f2755a-69ad-4e68-8604-13b67f972f90.png)
![SS_4-1](https://user-images.githubusercontent.com/68798323/177542197-08f4eaa5-7286-4dce-a568-2fe76088d4e7.png)
![SS_5-1](https://user-images.githubusercontent.com/68798323/177542203-74edcd96-3465-4ab3-9842-c577a97e8475.png)
![title](https://user-images.githubusercontent.com/68798323/177542229-f74b3d35-9d2f-45d8-b05f-bed3a71a1a84.png)
-------------------------------------------------------------------------------------------------------------------------------


## Hal Event Week（学内コンテスト) ：スクリーンショット

### タイトル「***ぶっ飛べっ!!ナットウ・トライアル***」

### 詳細情報

#### 期間
 - 2021年10月8日 ~ 2022年1月31日
 
 #### チーム制作
 - 人数：7人(プログラマ4人,プランナー1人,デザイナー2人)
 
 #### どんなゲーム？

#### 担当箇所
- ゲームシーン
	- プレイヤーの挙動
	- 糸の挙動		
- エフェクト
	- アイテム
	- 時間遅延演出

#### こだわった点
- ジャンプ中のエフェクト
	- 最後まで飛ぶと風エフェクトがでる。
- ワイヤーアクション
	- 振り子みたいな動きと、直線的な動きを使い分けられるように工夫しました。
	- (反省)ワイヤーを曲線で表現する。

![screen_shoot_001](https://user-images.githubusercontent.com/68798323/177543117-ad4a55b2-793c-484e-8f8a-6bac24472ac7.jpg)
![screen_shoot_002](https://user-images.githubusercontent.com/68798323/177543133-4812d084-0b94-4296-9dfe-04d070d99c8b.jpg)
![screen_shoot_003](https://user-images.githubusercontent.com/68798323/177543147-c84711f1-108f-402a-9ece-01188f6bd6f5.jpg)
![screen_shoot_004](https://user-images.githubusercontent.com/68798323/177543161-51e967c1-a715-4162-a856-636351b055de.jpg)
![screen_shoot_005](https://user-images.githubusercontent.com/68798323/177543176-6e9bc251-15e9-414e-a5e2-79c47d4579a5.jpg)
![screen_shoot_006](https://user-images.githubusercontent.com/68798323/177543188-81ad45c6-6fee-4251-be0b-4de9c1119daa.jpg)

-------------------------------------------------------------------------------------------------------------------------------


## 2年DirectX 学内コンテスト：スクリーンショット


![スクリーンショット_001](https://user-images.githubusercontent.com/68798323/177544072-c918fffc-e10d-43c9-8d7c-5d0794bc9d41.jpg)

![image](https://user-images.githubusercontent.com/68798323/177544009-edefedbf-79ee-43d2-ad59-cdc3c7d6d496.png)
![image](https://user-images.githubusercontent.com/68798323/177544030-4d7c4d65-4b8c-44cd-af4a-876ad5691e73.png)
![image](https://user-images.githubusercontent.com/68798323/177544062-9759c21f-545b-4970-ab0c-8c8302619f79.png)
-------------------------------------------------------------------------------------------------------------------------------


## Blender作品

### 詳細情報
- 独学
- 2020年6月からYoutubeのチュートリアルを見ながら始める。
- 武器・エフェクトなどを制作
- Geometry Node でモデリング勉強中
- Shader Node でシェーダを研究中

### 武器など
![手榴弾サイクレス](https://user-images.githubusercontent.com/68798323/177544915-9cafd69d-2691-48a2-83ae-13bb75ce6f83.png)
![カーボンローラー](https://user-images.githubusercontent.com/68798323/177544702-310e7755-32e1-479c-a5b8-17679e9a1cde.png)
![kirito_haikei](https://user-images.githubusercontent.com/68798323/177544724-e2cc518e-ef6f-448d-bd95-c89493d0c15b.png)
![妖刀「羅刹」4](https://user-images.githubusercontent.com/68798323/177544796-977b5488-db4d-46b3-879a-ad9c82cc7b9c.png)
![ランベントライト7](https://user-images.githubusercontent.com/68798323/177544832-88f9d9a4-299c-4577-a8c6-bf31a27be7ed.png)
![ランス5](https://user-images.githubusercontent.com/68798323/177544851-28353241-0fe2-4148-9c10-078ff1fa6932.png)
![asuna_sword](https://user-images.githubusercontent.com/68798323/177544860-143e031b-1e26-4abe-bebd-c5e8d12898ea.png)
![splush_bomb1](https://user-images.githubusercontent.com/68798323/177544875-21b02e99-d1bd-42e0-a0a9-8eeba7430550.png)

### エフェクトなど
![tornerd_effect_001](https://user-images.githubusercontent.com/68798323/177544894-94b7d4cd-9ae6-43a8-ba9a-d15d64c5b04b.png)
![趙エフェクト](https://user-images.githubusercontent.com/68798323/177544904-4d5068f5-6d5d-40f8-be55-c69c2409b026.png)
![blender](https://user-images.githubusercontent.com/68798323/177544972-375c1125-aa55-4d13-8169-82eb50d633bd.png)
![thunder1](https://user-images.githubusercontent.com/68798323/177544986-feef1762-cbbb-4170-a187-3af4c5ab10b4.png)

-------------------------------------------------------------------------------------------------------------------------------


## WPF

### このアイコンエディタでできること

- 32ビットのビットマップ画像を開く
- 保存する
- 拡大・縮小
- Redo・Undo
- カラーパレットで色変更

![image_001](https://user-images.githubusercontent.com/68798323/177545085-1a51f379-7072-4ba2-bc11-1bac1f49a9a9.png)
![image_002](https://user-images.githubusercontent.com/68798323/177545094-dd821edb-2f53-475b-964c-051a904c9a64.png)
![image_003](https://user-images.githubusercontent.com/68798323/177545103-b0e8fa41-8e88-4565-84c1-447eda56cc5e.png)
-------------------------------------------------------------------------------------------------------------------------------


