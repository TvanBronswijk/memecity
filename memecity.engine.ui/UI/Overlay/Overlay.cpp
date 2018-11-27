#include "Overlay.h"

namespace memecity::engine::ui::overlay {

	void Overlay::render()
	{
		background_texture->set_position(Vector2{ background_texture->get_clipped_rect().w * 0.5f,  background_texture->get_clipped_rect().h * 0.5f });
		multimedia_manager.render_texture(*background_texture);

		for (auto& overlay_item:overlay_items)
		{			
			overlay_item->render();
		}
	}

}