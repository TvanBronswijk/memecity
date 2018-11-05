#include "InteractionEventArgs.h"

std::string InteractionEventArgs::EVENT_ARGS_TYPE = "InteractionEventArgs";

std::string InteractionEventArgs::get_type() {
	return EVENT_ARGS_TYPE;
}

InteractionEventArgs::InteractionEventArgs(int id) {
	source_entity_id = id;
}

InteractionEventArgs::~InteractionEventArgs() {

}