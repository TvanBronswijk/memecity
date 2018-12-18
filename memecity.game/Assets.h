#ifndef _GAME_ASSETS_H
#define _GAME_ASSETS_H

namespace assets {
	using Asset = const char*;
	using AssetMap = const std::map<Asset, int>;
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
			static inline AssetMap GRASS{ {GRASS0, 48}, {GRASS1, 96}, {GRASS2, 98}, {GRASS3, 100} };

			constexpr inline Asset ROAD0 = "Sprites/Tiles/paving_00.bmp";
			constexpr inline Asset ROAD1 = "Sprites/Tiles/paving_01.bmp";
			constexpr inline Asset ROAD2 = "Sprites/Tiles/paving_02.bmp";
			constexpr inline Asset ROAD3 = "Sprites/Tiles/paving_03.bmp";
			static inline AssetMap ROAD{ {ROAD0, 90}, {ROAD1, 96}, {ROAD2, 97}, {ROAD3, 100} };

			constexpr inline Asset WALL0 = "Sprites/Tiles/wall_00.bmp";
			static inline AssetMap WALL{ {WALL0, 100} };

			constexpr inline Asset WATER0 = "Sprites/Tiles/water_00.bmp";
			static inline AssetMap WATER{ {WATER0, 100} };
		}

		constexpr inline Asset DARK_BACKGROUND = "Sprites/big_black.bmp";
		constexpr inline Asset TIN_CAN = "Sprites/Tin_can.png";
	}
	namespace spritesheets {
		static constexpr Asset HUMAN_MALE_1 = "Spritesheets/SpriteSheet.png";
	}
	namespace advertisements {
		static constexpr Asset ADVERTISEMENT_ONE = "Advertisements/AbbeyGames.png";
		static constexpr Asset ADVERTISEMENT_TWO = "Advertisements/AdventOfCode.png";
		static constexpr Asset ADVERTISEMENT_THREE = "Advertisements/CodedFun.png";
		static constexpr Asset ADVERTISEMENT_FOUR = "Advertisements/CppCon.png";
		static constexpr Asset ADVERTISEMENT_FIVE = "Advertisements/BananaWho.png";
		static constexpr Asset ADVERTISEMENT_SIX = "Advertisements/CocaCola.png";
		static constexpr Asset ADVERTISEMENT_SEVEN = "Advertisements/BurgerKing.png";
		static constexpr Asset ADVERTISEMENT_EIGHT = "Advertisements/kolrd.png";

		const static std::vector<std::string> ADS{ ADVERTISEMENT_ONE, ADVERTISEMENT_TWO, ADVERTISEMENT_THREE, ADVERTISEMENT_FOUR, ADVERTISEMENT_FIVE, ADVERTISEMENT_SIX, ADVERTISEMENT_SEVEN, ADVERTISEMENT_EIGHT };

		inline std::string get_random_ad()
		{
			const auto index = rand() % assets::advertisements::ADS.size();
			return ADS[index];
		}
	}
};

#endif
