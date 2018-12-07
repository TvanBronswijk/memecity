#ifndef _GAME_ASSETS_H
#define _GAME_ASSETS_H

namespace assets {
	using Asset = const char*;
	namespace fonts {
		static constexpr Asset DEFAULT_FONT = "Fonts/Minecraftia-Regular.ttf";
	}
	namespace music {
		static constexpr Asset DEFAULT_BGM = "Music/bgm-game.mp3";
		static constexpr Asset MAIN_MENU_BGM = "Music/bgm-menu.mp3";
	}
	namespace sprites {
		namespace tiles {
			static constexpr Asset GRASS = "Sprites/Tiles/green.bmp";
			static constexpr Asset ROAD = "Sprites/Tiles/gray.bmp";
			static constexpr Asset WALL = "Sprites/Tiles/brown.bmp";
			static constexpr Asset WATER = "Sprites/Tiles/blue.bmp";
		}
		static constexpr Asset DARK_BACKGROUND = "Sprites/big_black.bmp";
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
};

#endif
