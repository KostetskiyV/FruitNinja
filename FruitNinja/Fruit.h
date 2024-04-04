using namespace System;
using namespace System::Drawing;

#define HALFBLADE_THICKNESS 2.5

#pragma once
ref class Fruit
{
private:
	array<PointF>^ points;
	PointF center;
	double angle;
	double speedX;
	double speedY;
	Color color;

	void setStartGeometry(int fruitIndex) {
		//fruitIndexes:
		//1 - Banana
		//2 - cucumber
		//3 - pear
		//4 - tomato
		switch (fruitIndex)
		{
		case 1:
			{	points = gcnew array<PointF>{ PointF(6, 23), PointF(24, 28), PointF(41, 39),
				PointF(58, 49), PointF(84, 61), PointF(114, 66), PointF(149, 65),
				PointF(179, 54), PointF(206, 43), PointF(224, 35), PointF(227, 59),
				PointF(210, 91), PointF(179, 108), PointF(141, 117), PointF(100, 117),
				PointF(59, 105), PointF(34, 89), PointF(16, 69), PointF(6, 45) }; }
			{	center = PointF(122, 41); }
			{	color = Color::Yellow; }
			break;
		case 2:
			{	points = gcnew array<PointF>{ PointF(2, 71), PointF(3, 56), PointF(15, 40),
			PointF(39, 30), PointF(69, 21), PointF(104, 13), PointF(140, 7),
			PointF(180, 3), PointF(210, 5), PointF(227, 14), PointF(234, 29),
			PointF(231, 47), PointF(209, 64), PointF(181, 74), PointF(151, 83),
			PointF(118, 91), PointF(83, 96), PointF(50, 99), PointF(20, 98), PointF(6, 88) }; }
			{	center = PointF(126, 46); }
			{	color = Color::Green; }
			break;
		case 3:
			{	points = gcnew array<PointF>{ PointF(52, 5), PointF(73, 3), PointF(87, 11),
			PointF(95, 32), PointF(107, 52), PointF(120, 74), PointF(128, 96),
			PointF(128, 116), PointF(120, 146), PointF(98, 164), PointF(71, 167),
			PointF(39, 164), PointF(14, 144), PointF(2, 120), PointF(4, 98),
			PointF(12, 66), PointF(21, 44), PointF(27, 21), PointF(38, 8) }; }
			{	center = PointF(61, 87); }
			{	color = Color::LimeGreen; }
			break;
		default:
			{	points = gcnew array<PointF>{ PointF(93, 1), PointF(114, 2), PointF(134, 6),
			PointF(155, 15), PointF(172, 31), PointF(182, 54), PointF(183, 77),
			PointF(174, 100), PointF(153, 121), PointF(126, 135), PointF(92, 138),
			PointF(60, 134), PointF(33, 121), PointF(13, 101), PointF(4, 79),
			PointF(4, 54), PointF(19, 28), PointF(42, 12), PointF(70, 3) }; }
			{	center = PointF(92, 66); }
			{	color = Color::Red; }
			break;
		}
	}

	PointF rotateAndScale(PointF point) {
		double X = center.X, Y = center.Y;
		double angle0;
		if (point.X == X)
			angle0 = ((-point.Y + Y) / Math::Abs(-point.Y + Y)) * Math::PI / 2 + angle;
		else if (point.X > X)
			angle0 = Math::Atan((-point.Y + Y + 0.0) / (point.X - X)) + angle;
		else
			angle0 = -Math::PI + Math::Atan((-point.Y + Y + 0.0) / (point.X - X)) + angle;
		double len = Math::Sqrt((point.X - X + 0.0) * (point.X - X + 0.0) + (point.Y - Y + 0.0) * (point.Y - Y + 0.0));

		double newX = X + 0.995 * len * Math::Cos(angle0);
		double newY = Y - 0.995 * len * Math::Sin(angle0);
		PointF newPoint = PointF(newX, newY);
		point = newPoint;
		return point;
	}

public:
	Fruit(int strick, int screenSizeX, int screenSizeY) {
		Random^ rand = gcnew Random();
		int fruitIndex = rand->Next(1, 5);
		setStartGeometry(fruitIndex);
		speedX = 5 * (strick + 1);
		speedY = 0;

		angle = 0.14*(rand->NextDouble() - 0.5);
		if (rand->Next(1, 3) == 1) {
			for (int i = 0; i < points->Length-1; points[i].X -= 250, i++) {}
			points[points->Length - 1].X -= 250;
			center.X -= 250;
		}
		else {
			for (int i = 0; i < points->Length-1; points[i].X += screenSizeX, i++) {}
			points[points->Length - 1].X += screenSizeX;
			center.X += screenSizeX;
			speedX *= -1;
		}

		float Y = rand->Next(0, screenSizeY - 201);
		for (int i = 0; i < points->Length-1; points[i].Y += Y, i++) {}
		points[points->Length - 1].Y += Y;
		center.Y += Y;
	}

	array<PointF>^ getPoints() { return points; }

	Color getColor() { return color; }

	bool isOnScreen(int screenSizeX, int screenSizeY) {
		float minY = points[0].Y;
		for (int i = 1; i < points->Length; i++) {
			if (points[i].Y < minY)
				minY = points[i].Y;
		}
		if (minY > screenSizeY)
			return false;
	}

	bool isStriked(int X, int Y) {
		bool a = false, b = false, c = false, d = false;
		for (int i = 0; i < points->Length; i++) {
			if ((X <= points[i].X + HALFBLADE_THICKNESS) && (Y <= points[i].Y + HALFBLADE_THICKNESS))
				a = true;
			if ((X <= points[i].X + HALFBLADE_THICKNESS) && (Y >= points[i].Y - HALFBLADE_THICKNESS))
				b = true;
			if ((X >= points[i].X - HALFBLADE_THICKNESS) && (Y <= points[i].Y + HALFBLADE_THICKNESS))
				c = true;
			if ((X >= points[i].X - HALFBLADE_THICKNESS) && (Y >= points[i].Y - HALFBLADE_THICKNESS))
				d = true;
		}
		return (a && b && c && d);
	}

	void move() {
		center.X += speedX;
		center.Y += speedY;
		for (int i = 0; i < points->Length; i++) {
			points[i].X += speedX;
			points[i].Y += speedY;
			points[i] = rotateAndScale(points[i]);
		}
		speedY += 0.2;
	}

};

