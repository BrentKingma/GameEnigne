#pragma once
#include <queue>
#include <bitset>

class Keyboard
{
	friend class Window;
public:
	class Event
	{
	public:
		enum class Type
		{
			Press,
			Release,
			Invalid
		};
	public:
		Event() noexcept : type(Type::Invalid), code(0u)
		{}
		Event(Type type, unsigned char code) noexcept : type(type), code(code)
		{}
		bool IsPress() const noexcept { return type == Type::Press; }
		bool IsReleased() const noexcept { return type == Type::Release; }
		bool IsValied() const noexcept { return type != Type::Invalid; }
		unsigned char GetCode() const noexcept { return code; }
	private:
		Type type;
		unsigned char code;
	};
public:
	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator= (const Keyboard&) = delete;

	bool IsKeyPressed(unsigned char keycode) const noexcept;
	Event ReadKey() noexcept;
	bool KeyIsEmpty() const noexcept;
	void FlushKey() noexcept;

	char ReadChar() noexcept;
	bool IsCharEmpty() const noexcept;
	void FlushChar() noexcept;
	void Flush() noexcept;

	void EnableAutorepeat() noexcept;
	void DisableAutorepeat() noexcept;
	bool IsAutoRepeatEnabled() const noexcept;
private:
	void OnKeyPressed(unsigned char keycode) noexcept;
	void OnKeyReleased(unsigned char keycode) noexcept;
	void OnChar(char character) noexcept;
	void ClearState() noexcept;
	template<typename T>
	static void TrimBuffer(std::queue<T>& buffer) noexcept;
private:
	///Max number of bits required for keycodes
	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int bufferSize = 16u;
	bool autorepeatEnabled = false;
	std::bitset<nKeys> keyState;
	std::queue<Event> keyBuffer;
	std::queue<char> charBuffer;
};