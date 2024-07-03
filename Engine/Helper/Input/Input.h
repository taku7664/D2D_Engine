#pragma once

using namespace std;

struct KeyState {
	bool IsDown = false;
	bool IsHold = false;
	bool IsUp = false;
};

struct MouseState {
	bool Left = false;
	bool Right = false;
	bool Mid = false;
};

class Input
{
private:

	static float Horizontal_Axis;
	static float Vertical_Axis;
	static int Horizontal_AxisRaw;
	static int Vertical_AxisRaw;
	static KeyState Key_Code[256];
	static MouseState Cur_Mouse;
	static MouseState Pre_Mouse;

	static void Axis();
	static void AxisRaw();

public:

	static Vector2 mousePosition;

	static void GetKey(MSG msg);
	static void Update();
	static void ResetKey();

	// Ű���尡 ���ȴ��� Ȯ���մϴ�.
	static bool KeyDown(int _code);
	static bool KeyDown(KeyType _code);
	// Ű���尡 ������ �ִ� ������ Ȯ���մϴ�.
	static bool KeyHold(int _code);
	static bool KeyHold(KeyType _code);
	// Ű���带 �ô��� Ȯ���մϴ�.
	static bool KeyUp(int _code);
	static bool KeyUp(KeyType _code);

	static float GetAxis(string _dir);
	static int GetAxisRaw(string _dir);

	static void SetAxis(string _dir, float value);
	static void SetAxisRaw(string _dir, int value);

	static bool MouseDown(MouseType _code);
	static bool MouseHold(MouseType _code);
	static bool MouseUp(MouseType _code);

};