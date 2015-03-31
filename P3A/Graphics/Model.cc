#include "P3A/Graphics/Model.h"

#include "P3A/Graphics/GraphicsContext.h"

namespace P3A{
namespace Graphics{
void Model::Render(void) {
  for (uint32 current = 0; current < mesh_->elements_count; ++current)
    context_->DrawBox(appearance_->element_textures()[mesh_->depth_indexes[current]],
                     element_centers_[mesh_->depth_indexes[current]],
                     interpolation_->bases_[mesh_->depth_indexes[current]]->current.rotation);
}
}
}