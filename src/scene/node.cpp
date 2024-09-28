#include "CloudEngine/scene/node.h"
#include "CloudEngine/vec.h"

bool Node::IsInside(Node &node)
{
    float left1 = position.x - (scale.x / 2);
    float right1 = position.x + (scale.x / 2);
    float top1 = position.y - (scale.y / 2);
    float bottom1 = position.y + (scale.y / 2);
    float back1 = position.z - (scale.z / 2);
    float front1 = position.z + (scale.z / 2);

    // Calculate the other node's bounds
    float left2 = node.position.x - (node.scale.x / 2);
    float right2 = node.position.x + (node.scale.x / 2);
    float top2 = node.position.y - (node.scale.y / 2);
    float bottom2 = node.position.y + (node.scale.y / 2);
    float back2 = node.position.z - (node.scale.z / 2);
    float front2 = node.position.z + (node.scale.z / 2);

    // Check for overlap in all three dimensions
    bool x_overlap = (left1 <= right2) && (left2 <= right1);
    bool y_overlap = (top1 <= bottom2) && (top2 <= bottom1);
    bool z_overlap = (back1 <= front2) && (back2 <= front1);

    // If there's overlap on all three axes, the boxes collide
    return x_overlap && y_overlap && z_overlap;
}
