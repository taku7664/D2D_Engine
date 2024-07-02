#pragma once
#include "Renderer.h"


class RectRenderer
	: public Renderer
{
public:

	RectRenderer();
	~RectRenderer();

	virtual void Draw(Camera2D* _camera) final;

	void SetLineColor(D2D1_COLOR_F _color);
	void SetFillColor(D2D1_COLOR_F _color);
	void SetLine(bool _val);
	void SetFill(bool _val);

	float lineWidth;  // �ܰ��� �β�

private:

	D2D1_COLOR_F m_linecolor; // ��
	D2D1_COLOR_F m_fillcolor; // ä���
	bool isFill;
	bool isLine;
};

