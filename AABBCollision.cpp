#include "AABBCollision.h"

bool CheckAABBCollision(Vector2 center, float radius, Rectangle rect)
{
    float closestX = std::fmax(rect.x, std::fmin(center.x, rect.x + rect.width));
    float closestY = std::fmax(rect.y, std::fmin(center.y, rect.y + rect.height));

    float distanceX = center.x - closestX;
    float distanceY = center.y - closestY;

    return (distanceX * distanceX + distanceY * distanceY) <= (radius * radius);
}