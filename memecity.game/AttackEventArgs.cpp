#include "AttackEventArgs.h"

std::string AttackEventArgs::EVENT_ARGS_TYPE = "AttackEventArgs";

std::string AttackEventArgs::get_type() {
	return EVENT_ARGS_TYPE;
}

AttackEventArgs::AttackEventArgs(int source, int target) {
	source_entity_id = source;
	target_entity_id = target;
}

AttackEventArgs::~AttackEventArgs() {

}