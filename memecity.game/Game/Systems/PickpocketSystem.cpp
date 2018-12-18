#include "PickpocketSystem.h"
#include <stdlib.h>     /* srand, rand */
#include "..\Components\StatsComponent.h"

using namespace memecity::engine::ecs;

void PickpocketSystem::run(EntityManager& em, float dt) const {}

void PickpocketSystem::on_pickpocket(EntityManager& em,  PickpocketEventArgs args)
{
	auto ai = args.ai.get<AIComponent>();
	auto ai_stats = args.ai.get<StatsComponent>();
	auto player_stats = args.player.get<StatsComponent>();
	auto player = args.player.get<PlayerComponent>();

	int player_intelligence = (rand() % player_stats->intelligence);
	int ai_intelligence = (rand() % ai_stats->intelligence);


	if (ai->entity().get<HealthComponent>()->health > 0) {
		if ((player_intelligence - ai_intelligence) < 0) {
			int player_charisma = (rand() % player_stats->charisma);
			if (player_charisma > player_stats->charisma/5) {
				faulty_pickpocket_event.fire(em, FaultyPickpocketEventArgs(ai->entity(), "Excuse you!"));
			}
			else {
				faulty_pickpocket_event.fire(em, FaultyPickpocketEventArgs(ai->entity(), "What the fuck are you doing!"));
				ai->state = Ai_State::Fighting;
			}
		}
		else {
			if (ai->blik_coins > 0) {
				player->blik_coins += ai->blik_coins;
				std::cout << player->blik_coins;
				ai->blik_coins = 0;
				exp_event.fire(em, ExpEventArgs(10, 0));
				auto luck = rand() % player_stats->luck;
				if (luck > player_stats->luck / 5) {
					blikcoins_event.fire(em, BlikCoinEventArgs((player->blik_coins * 1.3)));
				}
				else {
					blikcoins_event.fire(em, BlikCoinEventArgs(player->blik_coins));
				}
			}
		}
	}
}
