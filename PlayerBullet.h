#pragma once
#include"Model.h"
#include "WorldTransform.h"
#include<cassert>



class PlayerBullet 
{
public:
	///<summary>
	///初期化
	/// </summary>
	/// <parm name="model">モデル</param>
	/// <parm name="position">初期座標</param>
	
	void Iniialize(Model* model, const Vector3& position);


	///<summary>
	///更新
	/// </summary>
	/// 
	
	void Update();

	///< summary>
	/// 描画
	///  </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
  
	void Draw(const ViewProjection& viewProjection);


	private:

		WorldTransform worldTransform_;

	    Model* model_ = nullptr;

	    uint32_t textureHandle_ = 0u;
};
