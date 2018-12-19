#ifndef _GAME_ASSETS_H
#define _GAME_ASSETS_H

namespace assets {
	using Asset = const char*;
	namespace fonts {
		constexpr inline Asset DEFAULT_FONT = "Fonts/Minecraftia-Regular.ttf";
	}
	namespace music {
		constexpr inline Asset DEFAULT_BGM = "Music/bgm-game.mp3";
		constexpr inline Asset MAIN_MENU_BGM = "Music/bgm-menu.mp3";
	}
	namespace sprites {
		namespace tiles {
			constexpr inline Asset GRASS0 = "Sprites/Tiles/grass_00.bmp";
			constexpr inline Asset GRASS1 = "Sprites/Tiles/grass_01.bmp";
			constexpr inline Asset GRASS2 = "Sprites/Tiles/grass_02.bmp";
			constexpr inline Asset GRASS3 = "Sprites/Tiles/grass_03.bmp";
			const static std::map<Asset, int> GRASS{ {GRASS0, 48}, {GRASS1, 96}, {GRASS2, 98}, {GRASS3, 100} };

			constexpr inline Asset ROAD0 = "Sprites/Tiles/paving_00.bmp";
			constexpr inline Asset ROAD1 = "Sprites/Tiles/paving_01.bmp";
			constexpr inline Asset ROAD2 = "Sprites/Tiles/paving_02.bmp";
			constexpr inline Asset ROAD3 = "Sprites/Tiles/paving_03.bmp";
			const static std::map<Asset, int> ROAD{ {ROAD0, 90}, {ROAD1, 96}, {ROAD2, 97}, {ROAD3, 100} };

			constexpr inline Asset WALL0 = "Sprites/Tiles/wall_00.bmp";
			const static std::map<Asset, int> WALL{ {WALL0, 100} };

			constexpr inline Asset WATER0 = "Sprites/Tiles/water_00.bmp";
			const static std::map<Asset, int> WATER{ {WATER0, 100} };
		}

		constexpr inline Asset DARK_BACKGROUND = "Sprites/big_black.bmp";
		constexpr inline Asset TIN_CAN = "Sprites/Tin_can.png";
	}
	namespace spritesheets {
		constexpr inline Asset HUMAN_MALE_1 = "Spritesheets/SpriteSheet.png";
		constexpr inline Asset HUMAN_FIGHTING_1 = "Spritesheets/FightingSheet.png";
		constexpr inline Asset HUMAN_DYING_1 = "Spritesheets/DeadSheet.png";
		constexpr inline Asset HUMAN_TEST_1 = "Spritesheets/Boy1SpriteSheet.png";

	}
	namespace advertisements {
		static constexpr Asset ADVERTISEMENT_ONE = "Advertisements/BurgerKing.png";
		static constexpr Asset ADVERTISEMENT_TWO = "Advertisements/BananaWho.png";
		static constexpr Asset ADVERTISEMENT_THREE = "Advertisements/CocaCola.png";

		const static std::vector<std::string> ADS{ ADVERTISEMENT_ONE, ADVERTISEMENT_TWO, ADVERTISEMENT_THREE };

		inline std::string get_random_ad()
		{
			const auto index = rand() % assets::advertisements::ADS.size();
			return ADS[index];
		}
	}
};

#endif
