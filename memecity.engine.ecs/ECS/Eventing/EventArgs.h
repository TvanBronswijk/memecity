#ifndef _EVENT_ARGS_H
#define  _EVENT_ARGS_H

namespace ecs {
	namespace eventing {
		struct EventArgs {
			EventArgs() = default;
			virtual ~EventArgs() = default;
		};
	};
};

#endif
