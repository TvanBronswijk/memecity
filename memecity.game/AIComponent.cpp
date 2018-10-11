#include"AIComponent.h"

AIComponent::AIComponent() {
	_fleeing = false;
	_fighting = true;
}

AIComponent::AIComponent(bool fighting, bool fleeing) {
	_fleeing = fleeing;
	_fighting = fighting;
}

std::string AIComponent::get_type() {
	return "AIConponent";
}