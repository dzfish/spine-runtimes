#include "BatchSkeletonAnimation.h"

namespace spine {

	static const int quadTriangles[6] = { 0, 1, 2, 2, 3, 0 };
	BatchSkeletonAnimation::~BatchSkeletonAnimation()
	{
	}


	BatchSkeletonAnimation* BatchSkeletonAnimation::createWithData(spSkeletonData* skeletonData) {
		BatchSkeletonAnimation* node = new BatchSkeletonAnimation(skeletonData);
		node->autorelease();
		node->batchInit();
		return node;
	}

	BatchSkeletonAnimation* BatchSkeletonAnimation::createWithFile(const std::string& skeletonDataFile, spAtlas* atlas, float scale) {
		BatchSkeletonAnimation* node = new BatchSkeletonAnimation(skeletonDataFile, atlas, scale);
		node->autorelease();
		node->batchInit();
		return node;
	}

	BatchSkeletonAnimation* BatchSkeletonAnimation::createWithFile(const std::string& skeletonDataFile, const std::string& atlasFile, float scale) {
		BatchSkeletonAnimation* node = new BatchSkeletonAnimation(skeletonDataFile, atlasFile, scale);
		node->autorelease();
		node->batchInit();
		return node;
	}
	void BatchSkeletonAnimation::batchInit(){
		_quads = nullptr;
		_quadCommands = nullptr;
		setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
	}

	void BatchSkeletonAnimation::draw(Renderer* renderer, const Mat4& transform, uint32_t transformFlags) {

		Color3B nodeColor = getColor();
		_skeleton->r = nodeColor.r / (float)255;
		_skeleton->g = nodeColor.g / (float)255;
		_skeleton->b = nodeColor.b / (float)255;
		_skeleton->a = getDisplayedOpacity() / (float)255;

		int additive = -1;
		Color4B color;
		const float* uvs = nullptr;
		int verticesCount = 0;
		const int* triangles = nullptr;
		int trianglesCount = 0;
		float r = 0, g = 0, b = 0, a = 0;
		
		if (!_quads){
			_quads = new V3F_C4B_T2F_Quad[_skeleton->slotsCount];
		}
		if (!_quadCommands){
			_quadCommands = new QuadCommand[_skeleton->slotsCount];
		}


		for (int i = 0, n = _skeleton->slotsCount; i < n; i++) {
			spSlot* slot = _skeleton->drawOrder[i];
			if (!slot->attachment) continue;
			Texture2D *texture = nullptr;
			switch (slot->attachment->type) {
			case SP_ATTACHMENT_REGION: {
										   spRegionAttachment* attachment = (spRegionAttachment*)slot->attachment;
										   spRegionAttachment_computeWorldVertices(attachment, slot->bone, _worldVertices);
										   texture = getTexture(attachment);
										   uvs = attachment->uvs;
										   verticesCount = 8;
										   triangles = quadTriangles;
										   trianglesCount = 6;
										   r = attachment->r;
										   g = attachment->g;
										   b = attachment->b;
										   a = attachment->a;
										   break;
			}
			case SP_ATTACHMENT_MESH: {
										 spMeshAttachment* attachment = (spMeshAttachment*)slot->attachment;
										 spMeshAttachment_computeWorldVertices(attachment, slot, _worldVertices);
										 texture = getTexture(attachment);
										 uvs = attachment->uvs;
										 verticesCount = attachment->verticesCount;
										 triangles = attachment->triangles;
										 trianglesCount = attachment->trianglesCount;
										 r = attachment->r;
										 g = attachment->g;
										 b = attachment->b;
										 a = attachment->a;
										 break;
			}
			case SP_ATTACHMENT_SKINNED_MESH: {
												 spSkinnedMeshAttachment* attachment = (spSkinnedMeshAttachment*)slot->attachment;
												 spSkinnedMeshAttachment_computeWorldVertices(attachment, slot, _worldVertices);
												 texture = getTexture(attachment);
												 uvs = attachment->uvs;
												 verticesCount = attachment->uvsCount;
												 triangles = attachment->triangles;
												 trianglesCount = attachment->trianglesCount;
												 r = attachment->r;
												 g = attachment->g;
												 b = attachment->b;
												 a = attachment->a;
												 break;
			}
			default:;
			}
			if (texture) {

				BlendFunc bFunc = _blendFunc;
				
				if (slot->data->additiveBlending != additive) {
					bFunc.dst = slot->data->additiveBlending ? GL_ONE : _blendFunc.dst;
					additive = slot->data->additiveBlending;
				}			
							
				color.a = _skeleton->a * slot->a * a * 255;
				float multiplier = _premultipliedAlpha ? color.a : 255;
				color.r = _skeleton->r * slot->r * r * multiplier;
				color.g = _skeleton->g * slot->g * g * multiplier;
				color.b = _skeleton->b * slot->b * b * multiplier;

				quadPointer = _quads + i;

				quadPointer->bl.vertices = { _worldVertices[0], _worldVertices[1], 0 };
				quadPointer->br.vertices = { _worldVertices[2], _worldVertices[3], 0 };
				quadPointer->tl.vertices = { _worldVertices[6], _worldVertices[7], 0 };
				quadPointer->tr.vertices = { _worldVertices[4], _worldVertices[5], 0 };


				quadPointer->bl.colors = color;
				quadPointer->br.colors = color;
				quadPointer->tl.colors = color;
				quadPointer->tr.colors = color;
				
				quadPointer->bl.texCoords = { uvs[0], uvs[1] };
				quadPointer->br.texCoords = { uvs[2], uvs[3] };
				quadPointer->tl.texCoords = { uvs[6], uvs[7] };
				quadPointer->tr.texCoords = { uvs[4], uvs[5] };

				_quadCommands[i].init(_globalZOrder, texture->getName(), getGLProgramState(), bFunc, _quads + i, 1, transform);
				renderer->addCommand(_quadCommands+i);
		

			}

		}

	}



}