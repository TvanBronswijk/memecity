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
			constexpr inline Asset GRASS = "Sprites/Tiles/grass_00.bmp";
			constexpr inline Asset GRASS1 = "Sprites/Tiles/grass_01.bmp";
			constexpr inline Asset GRASS2 = "Sprites/Tiles/grass_02.bmp";
			constexpr inline Asset GRASS3 = "Sprites/Tiles/grass_03.bmp";
			constexpr inline Asset ROAD = "Sprites/Tiles/paving_00.bmp";
			constexpr inline Asset ROAD1 = "Sprites/Tiles/paving_01.bmp";
			constexpr inline Asset ROAD2 = "Sprites/Tiles/paving_02.bmp";
			constexpr inline Asset ROAD3 = "Sprites/Tiles/paving_03.bmp";
			constexpr inline Asset WALL = "Sprites/Tiles/wall_00.bmp";
			constexpr inline Asset WATER = "Sprites/Tiles/water_00.bmp";
		}
		constexpr inline Asset DARK_BACKGROUND = "Sprites/big_black.bmp";
		constexpr inline Asset TIN_CAN = "Sprites/Tin_can.png";
	}
	namespace spritesheets {
		static constexpr Asset HUMAN_MALE_1 = "Spritesheets/SpriteSheet.png";
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
	namespace saves
	{
		static constexpr Asset SAVE_GAME = "new-game.txt";
	}
};

#endif
