#ifndef _MULTIMEDIAMANAGER_H
#define _MULTIMEDIAMANAGER_H
#include "AssetManager.h"

class MultimediaManager
{
	private:
		std::shared_ptr<AssetManager> asset_manager;

	public:
		MultimediaManager(std::shared_ptr<AssetManager> assetManager);
		void Init();
};

#endif