#pragma once
#include "spine\SkeletonAnimation.h"
#include <spine/PolygonBatch.h>
#include "cocos2d.h"
#include <vector>
#include "renderer\CCQuadCommand.h"

namespace spine {
	using namespace cocos2d;
	class BatchSkeletonAnimation :
		public SkeletonAnimation
	{
	public:
		static BatchSkeletonAnimation* createWithData(spSkeletonData* skeletonData);
		static BatchSkeletonAnimation* createWithFile(const std::string& skeletonDataFile, spAtlas* atlas, float scale = 1);
		static BatchSkeletonAnimation* createWithFile(const std::string& skeletonDataFile, const std::string& atlasFile, float scale = 1);
		
		
		BatchSkeletonAnimation::BatchSkeletonAnimation(spSkeletonData *skeletonData)
			: SkeletonAnimation(skeletonData) {
			initialize();
		}

		BatchSkeletonAnimation::BatchSkeletonAnimation(const std::string& skeletonDataFile, spAtlas* atlas, float scale)
			: SkeletonAnimation(skeletonDataFile, atlas, scale) {
			initialize();
		}

		BatchSkeletonAnimation::BatchSkeletonAnimation(const std::string& skeletonDataFile, const std::string& atlasFile, float scale)
			: SkeletonAnimation(skeletonDataFile, atlasFile, scale) {
			initialize();
		}
		~BatchSkeletonAnimation();
	protected:
		void addQuadVectorCount(size_t amount);
		void draw(Renderer* renderer, const Mat4& transform, uint32_t transformFlags) override;
		void batchInit();
		// quad command pointer
		QuadCommand* _quadCommands;
		// vertex coords, texture coords and color info
		V3F_C4B_T2F_Quad* _quads;
		V3F_C4B_T2F_Quad* quadPointer;
		

	};
}
