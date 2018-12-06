#include "Overlay.h"

namespace memecity::engine::ui::overlay {

	void Overlay::render()
	{
		multimedia_manager->render_texture(*background_texture);

		

		for (auto& overlay_item : overlay_text_items)
		{			
			overlay_item.second->render();
		}

		for (auto& overlay_item : overlay_bar_items)
		{
			overlay_item.second->render();
		}
	}

}