#pragma once

// オブジェクトのタグ
enum class ObjectTag
{
	PALYER,			// プレイヤー
	CAMERA,			// カメラ
	FLOOR,			// 床
	FLOOR_SMALL,	// 小さい床
	FLOOR_MOVE,		// 動く床
	ROOF,			// 天井
	SYSTEM_WALL,	// システム壁
	NO_GATE_WALL,	// ゲート生成不可壁
	DUMMY_WALL,		// ダミー壁
	GATE,			// ゲート
	GATE_BULLET,	// ゲート生成弾
	HAND_OBJ,		// 手で持てるオブジェクト
	BUTTON,			// ボタン
	PISTON,			// ピストン
	TURRET,			// タレット
	TURRET_BULLET,			// タレットの球
	LASER_LAUNCH_PAD,	// レーザーの開始地点
	LASER_CATCHER,		// レーザーの終了地点
	LASER_BULLET,	// レーザーの球
	GIMMICK,		// ギミック
	ELEVATOR,		// エレベータ
	CHECK_POINT,	// チェックポイント
	NONE,
};