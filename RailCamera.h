#pragma once
#include"ViewProjection.h"

#include"WorldTransform.h"
class RailCamera {

	public:

		void Initialize();


		void Update();

		private:
	    WorldTransform worldTransform_;

		ViewProjection viewProjection_;


};
