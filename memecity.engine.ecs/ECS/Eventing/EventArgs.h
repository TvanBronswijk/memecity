#ifndef _EVENT_ARGS_H
#define  _EVENT_ARGS_H

namespace memecity::engine::ecs::eventing {
		struct EventArgs {
			EventArgs() = default;
			virtual ~EventArgs() = default;
		};
};

#endif
