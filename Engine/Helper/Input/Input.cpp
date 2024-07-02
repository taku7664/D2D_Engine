#include "pch.h"
#include "Input.h"
#include "../../Render/D2DRender.h"

std::vector<short> KeyDown_Reset;
std::vector<short> KeyUp_Reset;

float			 Input::Horizontal_Axis = 0.f;
float	 		 Input::Vertical_Axis = 0.f;
int		 		 Input::Horizontal_AxisRaw = 0;
int				 Input::Vertical_AxisRaw = 0;
KeyState		 Input::Key_Code[256]{};
MouseState		 Input::Cur_Mouse{};
MouseState		 Input::Pre_Mouse{};
D2D1_VECTOR_2F   Input::mousePosition = { 0,0 };

// 누른 키보드 값을 저장합니다.
void Input::GetKey(MSG msg)
{
	// 딜레이 없게 하려고 
	Key_Code[msg.wParam].IsDown = false;
	if (msg.message == WM_KEYDOWN) {
		if (Key_Code[msg.wParam].IsHold == false) {
			Key_Code[msg.wParam].IsDown = true;
			Key_Code[msg.wParam].IsHold = true;
			KeyDown_Reset.push_back(msg.wParam);
		}
	}
	if (msg.message == WM_KEYUP) {
		Key_Code[msg.wParam].IsHold = false;
		Key_Code[msg.wParam].IsUp = true;
		KeyUp_Reset.push_back(msg.wParam);
	}
}

// 매 업데이트 마지막에 Down이나 Up의 정보들을 초기화시킵니다.
void Input::ResetKey()
{
	while (!KeyDown_Reset.empty())
	{
		Key_Code[KeyDown_Reset.back()].IsDown = false;
		KeyDown_Reset.pop_back();
	}
	while (!KeyUp_Reset.empty()) 
	{
		Key_Code[KeyUp_Reset.back()].IsUp = false;
		KeyUp_Reset.pop_back();
	}
}


// Axis 정보를 갱신합니다.
void Input::Update()
{
	// 키보드 업데이트
	Axis();
	AxisRaw();

	// 마우스 업데이트
	Pre_Mouse = Cur_Mouse;

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(D2DRender::GetHWND(), &pt);

	mousePosition = { (float)pt.x , (float)pt.y };
	Cur_Mouse.Mid = 0;

	Cur_Mouse.Left = (GetKeyState(VK_LBUTTON) & 0x8000) != 0;
	Cur_Mouse.Right = (GetKeyState(VK_RBUTTON) & 0x8000) != 0;
	Cur_Mouse.Mid = (GetKeyState(VK_MBUTTON) & 0x8000) != 0;
}

bool Input::KeyDown(int code)
{
	return Key_Code[code].IsDown;
}
bool Input::KeyDown(KeyType _code)
{
	return Key_Code[(int)_code].IsDown;
}
bool Input::KeyHold(int code)
{
	return Key_Code[code].IsHold;
}
bool Input::KeyHold(KeyType _code)
{
	return Key_Code[(int)_code].IsHold;
}
bool Input::KeyUp(int code)
{
	return Key_Code[code].IsUp;
}

bool Input::KeyUp(KeyType _code)
{
	return Key_Code[(int)_code].IsUp;
}

void Input::Axis()
{
	
	float deltaTime = Time::deltaTime * 3;

	if (Horizontal_Axis >= deltaTime * -1  && Horizontal_Axis <= deltaTime * 1) Horizontal_Axis = 0.f;
	if (Vertical_Axis >= deltaTime * -1  && Vertical_Axis <= deltaTime * 1) Vertical_Axis = 0.f;

	if (Horizontal_Axis >= -1.f && Horizontal_Axis <= 1.f) {
		if (KeyHold(RIGHT)) Horizontal_Axis += deltaTime;
		else if (KeyHold(LEFT)) Horizontal_Axis -= deltaTime;
		else if (Horizontal_Axis != 0.f) Horizontal_Axis += deltaTime * (Horizontal_Axis <= 0 ? 1 : -1);
	}
	if (Horizontal_Axis <= -1.f) Horizontal_Axis = -1.f;
	if (Horizontal_Axis >= 1.f) Horizontal_Axis = 1.f;

	if (Vertical_Axis >= -1.f && Vertical_Axis <= 1.f) {
		if (KeyHold(DOWN)) Vertical_Axis += deltaTime;
		else if (KeyHold(UP)) Vertical_Axis -= deltaTime;
		else if (Vertical_Axis != 0.f) Vertical_Axis += deltaTime * (Vertical_Axis < 0.f ? 1 : -1);
	}
	if (Vertical_Axis <= -1.f) Vertical_Axis = -1.f;
	if (Vertical_Axis >= 1.f) Vertical_Axis = 1.f;
	
}

void Input::AxisRaw()
{
	if (KeyHold(RIGHT)) Horizontal_AxisRaw = 1;
	else if (KeyHold(LEFT)) Horizontal_AxisRaw =- 1;
	else Horizontal_AxisRaw = 0;
	if (KeyHold(DOWN)) Vertical_AxisRaw = 1;
	else if (KeyHold(UP)) Vertical_AxisRaw = -1;
	else Vertical_AxisRaw = 0;
}

float Input::GetAxis(string dir)
{
	if (dir == "Horizontal") return Horizontal_Axis;
	else if (dir == "Vertical") return Vertical_Axis;
	else return 0;
}

int Input::GetAxisRaw(string dir)
{
	if (dir == "Horizontal") return Horizontal_AxisRaw;
	else if (dir == "Vertical") return Vertical_AxisRaw;
	else return 0;
}

void Input::SetAxis(string dir, float value)
{
	if (dir == "Horizontal") Horizontal_Axis = value;
	if (dir == "Vertical") Vertical_Axis = value;
}

void Input::SetAxisRaw(string dir, int value)
{
	if (dir == "Horizontal") Horizontal_AxisRaw = value;
	if (dir == "Vertical") Vertical_AxisRaw = value;
}

bool Input::MouseDown(MouseType _code)
{
	if (_code == MouseType::RIGHT && !Pre_Mouse.Right) return Cur_Mouse.Right;
	if (_code == MouseType::ROLL && !Pre_Mouse.Mid) return Cur_Mouse.Mid;
	if (_code == MouseType::LEFT && !Pre_Mouse.Left) return Cur_Mouse.Left;
	return false;
}

bool Input::MouseHold(MouseType _code)
{
	if (_code == MouseType::RIGHT) return Cur_Mouse.Right;
	if (_code == MouseType::ROLL) return Cur_Mouse.Mid;
	if (_code == MouseType::LEFT) return Cur_Mouse.Left;
	return false;
}

bool Input::MouseUp(MouseType _code)
{
	if (_code == MouseType::RIGHT && !Cur_Mouse.Right && Pre_Mouse.Right) return true;
	if (_code == MouseType::ROLL && !Cur_Mouse.Mid && Pre_Mouse.Mid) return true;
	if (_code == MouseType::LEFT && !Cur_Mouse.Left && Pre_Mouse.Left) return true;
	return false;
}
