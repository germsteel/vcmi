/*
 * MapOverlayLogVisualizer.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#include "StdInc.h"
#include "MapOverlayLogVisualizer.h"
#include "MapViewModel.h"

#include "../../lib/logging/VisualLogger.h"
#include "../render/Canvas.h"
#include "../render/Colors.h"
#include "../render/EFont.h"
#include "../gui/TextAlignment.h"


MapOverlayLogVisualizer::MapOverlayLogVisualizer(Canvas & target, std::shared_ptr<MapViewModel> model)
	: target(target), model(model)
{
}

void MapOverlayLogVisualizer::drawLine(int3 start, int3 end)
{
	const Point offset = Point(30, 30);

	auto level = model->getLevel();

	if(start.z != level || end.z != level)
		return;

	auto pStart = model->getTargetTileArea(start).topLeft();
	auto pEnd = model->getTargetTileArea(end).topLeft();
	auto viewPort = target.getRenderArea();

	pStart.x += 3;
	pEnd.x -= 3;

	pStart += offset;
	pEnd += offset;

	if(viewPort.isInside(pStart) && viewPort.isInside(pEnd))
	{
		target.drawLine(pStart, pEnd, ColorRGBA(255, 255, 0), ColorRGBA(255, 0, 0));
	}
}

void MapOverlayLogVisualizer::drawText(int3 tile, std::vector<std::string> texts)
{
	const Point offset = Point(5, 5);

	auto level = model->getLevel();

	if(tile.z != level)
		return;

	auto pStart = offset + model->getTargetTileArea(tile).topLeft();
	auto viewPort = target.getRenderArea();

	if(viewPort.isInside(pStart))
	{
		target.drawText(pStart, EFonts::FONT_TINY, Colors::YELLOW, ETextAlignment::TOPCENTER, texts);
	}
}
