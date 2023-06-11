#include "LevelPropertiesComponent.h"
#include "GameTime.h"

dae::LevelPropertiesComponent * dae::LevelPropertiesComponent::m_pCurrentLevelMap{nullptr};

dae::LevelPropertiesComponent::LevelPropertiesComponent(GameObject* pOwner)
	:BaseComponent(pOwner)
{
}

glm::vec2 dae::LevelPropertiesComponent::MoveOnGrid(const glm::vec2& position, const glm::vec2& size, const glm::vec2& direction, float speed)
{
	glm::vec2 result{position};	// default don't move

	// find tile on position
	glm::vec2 positionInGrid{position - m_LevelOffset};
	// position at character middle feet
	positionInGrid.x += size.x / 2;
	positionInGrid.y += size.y;

	int indexX{ static_cast<int>(floor(positionInGrid.x / m_TileSize.x)) };
	int indexY{ static_cast<int>(floor(positionInGrid.y / m_TileSize.y)) };

	if (direction.x > 0.5f || direction.x < -0.5f) // moving horizontal	
	{ 	
		// check if close to ground
		float edge{ m_TileSize.y * indexY };
		if (positionInGrid.y < edge + m_CanWalkMargin)
		{
			// close to top edge
			LevelTileProperties tile = m_pTiles[indexY][indexX];
			if (tile.moveHorizontal)
			{
				result.y = m_LevelOffset.y + edge - size.y - m_GroundMargin;	// small margin to stay on top 
				result.x += direction.x * speed * GameTime::GetInstance().ElapsedSeconds();

				if (result.x < m_LevelOffset.x)
				{
					// left bound
					result.x = m_LevelOffset.x;
				}
				else if (result.x + size.x > m_LevelOffset.x + m_LevelTotalSize.x)
				{
					// right bound
					result.x = m_LevelOffset.x + m_LevelTotalSize.x - size.x;
				}
			}

			return result;
		}
		edge += m_TileSize.y;
		if (positionInGrid.y > edge - m_CanWalkMargin)
		{
			// close to bottom edge
			LevelTileProperties tile = m_pTiles[indexY + 1][indexX];
			if (tile.moveHorizontal)
			{
				result.y = m_LevelOffset.y + edge - size.y - m_GroundMargin;	// small margin to stay on top 
				result.x += direction.x * speed * GameTime::GetInstance().ElapsedSeconds();

				if (result.x < m_LevelOffset.x)
				{
					// left bound
					result.x = m_LevelOffset.x;
				}
				else if (result.x + size.x > m_LevelOffset.x + m_LevelTotalSize.x)
				{
					// right bound
					result.x = m_LevelOffset.x + m_LevelTotalSize.x - size.x;
				}
			}

			return result;
		}
	}

	// TODO: fix moving vertical
	if (direction.y > 0.5f || direction.y < -0.5f) // moving vertical	
	{
		// check if close to center
		float center{ m_TileSize.x * (indexX + 0.5f) };
		if (positionInGrid.x < center + m_CanWalkMargin && positionInGrid.x > center - m_CanWalkMargin)
		{
			// close to center
			LevelTileProperties tile = m_pTiles[indexY][indexX];
			LevelTileProperties tileBelow = m_pTiles[indexY + 1][indexX];
			float edge{ m_TileSize.y * indexY };
			
			// if moveVertical or close to ground, going down and tile below can move vertical
			if (tile.moveVertical || (direction.y < 0.5f && tileBelow.moveVertical && positionInGrid.y - size.y < edge + m_CanWalkMargin))
			{
				result.x = m_LevelOffset.x + center - (size.x / 2); // -direction.y because y == 0 is top of the screen
				result.y += -direction.y * speed * GameTime::GetInstance().ElapsedSeconds();

				// top row is empty -> add 1x tilesize to bounds
				if (result.y + size.y < m_LevelOffset.y + m_TileSize.y + m_GroundMargin)
				{
					// upper bound
					result.y = m_LevelOffset.y + m_TileSize.y + m_GroundMargin - size.y;
				}
				else if (result.y + size.y > m_LevelOffset.y + m_LevelTotalSize.y)
				{
					// lower bound
					result.y = m_LevelOffset.y + m_LevelTotalSize.y - size.y;
				}
			}

			if (direction.y > 0.5f)
			{
				// moving up
				edge = m_LevelOffset.y + m_TileSize.y * indexY;
				if (result.y + size.y < edge)
				{
					// passed edge to next tile
					LevelTileProperties edgeTile = m_pTiles[indexY - 1][indexX];
					if (!edgeTile.moveVertical)
					{
						// clamp to ground
						result.y = edge - size.y - m_GroundMargin;
					}
				}
			}
			else
			{
				// moving down
				edge = m_LevelOffset.y + m_TileSize.y * (indexY + 1);
				if (result.y + size.y > edge)
				{
					// passed edge to next tile
					LevelTileProperties edgeTile = m_pTiles[indexY + 1][indexX];
					if (!edgeTile.moveVertical)
					{
						// clamp to ground
						result.y = edge - size.y - m_GroundMargin;
					}
				}
			}
			return result;
		}
	}

	return result; // even if nothing moved, result contains start position
}

void dae::LevelPropertiesComponent::SetTileAmount(int x, int y)
{
	m_TileAmount = { x, y };

	m_pTiles.clear();
	for (int i{}; i < y; ++i)
	{
		// clear textures, reserve the right capacity
		m_pTiles.push_back(std::vector<LevelTileProperties>{});
		m_pTiles.back().reserve(x);
	}

	m_LevelTotalSize = { x * m_TileSize.x, y * m_TileSize.y };
}

void dae::LevelPropertiesComponent::SetTileSize(int x, int y)
{
	m_TileSize = { x, y };
	m_LevelTotalSize = { x * m_TileAmount.x, y * m_TileAmount.y };
}
