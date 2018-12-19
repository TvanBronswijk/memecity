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

			constexpr inline Asset HARDWOOD0 = "Sprites/Tiles/hardwood_00.png";
			static inline AssetMap HARDWOOD{ {HARDWOOD0, 100} };

			constexpr inline Asset HARDWOODDARK0 = "Sprites/Tiles/hardwood_dark_00.png";
			static inline AssetMap HARDWOODDARK{ {HARDWOODDARK0, 100} };

			constexpr inline Asset MARBLEBLACK0 = "Sprites/Tiles/black_00.png";
			constexpr inline Asset MARBLEBLACK1 = "Sprites/Tiles/black_01.png";
			static inline AssetMap MARBLEBLACK{ {MARBLEBLACK0, 50}, {MARBLEBLACK1, 100} };

			constexpr inline Asset MARBLEWHITE0 = "Sprites/Tiles/white_00.png";
			constexpr inline Asset MARBLEWHITE1 = "Sprites/Tiles/white_01.png";
			static inline AssetMap MARBLEWHITE{ {MARBLEWHITE0, 50}, {MARBLEWHITE1, 100} };

			constexpr inline Asset CARPETBROWN0 = "Sprites/Tiles/brown_00.png";
			constexpr inline Asset CARPETBROWN1 = "Sprites/Tiles/brown_01.png";
			static inline AssetMap CARPETBROWN{ {CARPETBROWN0, 50}, {CARPETBROWN1, 100} };

			constexpr inline Asset CARPETLIGHTGRAY0 = "Sprites/Tiles/light_gray_00.png";
			constexpr inline Asset CARPETLIGHTGRAY1 = "Sprites/Tiles/light_gray_01.png";
			static inline AssetMap CARPETLIGHTGRAY{ {CARPETLIGHTGRAY0, 50}, {CARPETLIGHTGRAY1, 100} };

			constexpr inline Asset CARPETTAN0 = "Sprites/Tiles/tan_00.png";
			constexpr inline Asset CARPETTAN1 = "Sprites/Tiles/tan_01.png";
			static inline AssetMap CARPETTAN{ {CARPETTAN0, 50}, {CARPETTAN1, 100} };
		
			constexpr inline Asset STATION0 = "Sprites/Tiles/ns_00.png";
			static inline AssetMap STATION{ {STATION0, 100} };
		}

		constexpr inline Asset DARK_BACKGROUND = "Sprites/big_black.bmp";
		constexpr inline Asset TIN_CAN = "Sprites/Tin_can.png";
	}
	namespace spritesheets {
		constexpr inline Asset BOY_1 = "Spritesheets/Boy1SpriteSheet.png";
		constexpr inline Asset BOY_2 = "Spritesheets/Boy2SpriteSheet.png";
		constexpr inline Asset BOY_3 = "Spritesheets/Boy3SpriteSheet.png";
		constexpr inline Asset GIRL_1 = "Spritesheets/Girl1SpriteSheet.png";
		constexpr inline Asset GIRL_2 = "Spritesheets/Girl2SpriteSheet.png";
		constexpr inline Asset POLICE_1 = "Spritesheets/PoliceSpriteSheet.png";

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
	namespace saves
	{
		static constexpr Asset SAVE_GAME = "new-game.txt";
		static constexpr Asset SAVE_MAP = "map.txt";
		static constexpr Asset SAVE_HIGHSCORES = "highscores.meme";
	}
};

#endif
