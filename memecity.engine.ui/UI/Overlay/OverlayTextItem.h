
#ifndef OVERLAYTEXTITEM_H
#define OVERLAYTEXTITEM_H
#include "OverlayItem.h"

namespace memecity::engine::ui::overlay {
	class OverlayTextItem : public OverlayItem<std::string>
	{
	public:


		OverlayTextItem(MultimediaManager& multimedia_manager, std::string text, int size, float x, float y)
			: OverlayItem(multimedia_manager, text, size, x, y)
		{
		}


		void render() override;
	};
}
#endif // OVERLAYTEXTITEM_H
