#include "P3A\Graphics\Model.h"
#include "P3A\Graphics\GraphicsContext.h"

void P3A::Graphics::Model::Render(void)
{
        for (uint32 current = 0; current < mesh->elements_count; ++current)
                context.DrawBox(appearance->element_textures[mesh->depth_indexes[current]], element_centers[mesh->depth_indexes[current]], interpolation_current->rotations[mesh->depth_indexes[current]]);
}