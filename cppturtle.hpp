/*
 * MIT License
 *
 * Copyright (c) 2021 kmc7468
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#ifndef _WIN32
#	error "Windows 환경에서만 사용할 수 있습니다."
#elif defined(_MSC_VER) && _MSC_VER < 1900 || !defined(_MSC_VER) && __cplusplus < 201103L
#	error "C++11이 지원되는 환경에서만 사용할 수 있습니다."
#else

#include <cmath>
#include <stdexcept>
#include <string>
#include <utility>

#include <Windows.h>
#include <tchar.h>

#define CT_WINAPI_SAFELY(expression) ((SetLastError(0), (expression), GetLastError()) == 0)

namespace turtle {
	class Vector2 {
	public:
		int X = 0, Y = 0;

	public:
		Vector2() noexcept = default;
		Vector2(int x, int y) noexcept
			: X(x), Y(y) {}
		Vector2(const Vector2& other) noexcept = default;
		~Vector2() = default;

	public:
		Vector2& operator=(const Vector2& other) noexcept = default;
		bool operator==(const Vector2& rhs) const noexcept {
			return X == rhs.X && Y == rhs.Y;
		}
		bool operator!=(const Vector2& rhs) const noexcept {
			return X != rhs.X || Y != rhs.Y;
		}

	public:
		float GetSize() const {
			return std::sqrtf(X * X + Y * Y);
		}
		int Dot(const Vector2& rhs) const noexcept {
			return X * rhs.X + Y * rhs.Y;
		}
	};

	Vector2 operator+(const Vector2& lhs, const Vector2& rhs) noexcept {
		return { lhs.X + rhs.X, lhs.Y + rhs.Y };
	}
	Vector2 operator-(const Vector2& lhs, const Vector2& rhs) noexcept {
		return { lhs.X - rhs.X, lhs.Y - rhs.Y };
	}
	Vector2 operator*(const Vector2& lhs, int rhs) noexcept {
		return { lhs.X * rhs, lhs.Y * rhs };
	}
	Vector2 operator*(int lhs, const Vector2& rhs) noexcept {
		return { lhs * rhs.X, lhs * rhs.Y };
	}

	class Vector2f {
	public:
		float X = 0, Y = 0;

	public:
		Vector2f() noexcept = default;
		Vector2f(float x, float y) noexcept
			: X(x), Y(y) {}
		Vector2f(const Vector2& other) noexcept
			: X(other.X), Y(other.Y) {}
		Vector2f(const Vector2f& other) noexcept = default;
		~Vector2f() = default;

	public:
		Vector2f& operator=(const Vector2f& other) noexcept = default;
		bool operator==(const Vector2f& rhs) const noexcept {
			return X == rhs.X && Y == rhs.Y;
		}
		bool operator!=(const Vector2f& rhs) const noexcept {
			return X != rhs.X || Y != rhs.Y;
		}

	public:
		float GetSize() const {
			return std::sqrtf(X * X + Y * Y);
		}
		float Dot(const Vector2f& rhs) const noexcept {
			return X * rhs.X + Y * rhs.Y;
		}
	};

	Vector2f operator+(const Vector2f& lhs, const Vector2f& rhs) noexcept {
		return { lhs.X + rhs.X, lhs.Y + rhs.Y };
	}
	Vector2f operator-(const Vector2f& lhs, const Vector2f& rhs) noexcept {
		return { lhs.X - rhs.X, lhs.Y - rhs.Y };
	}
	Vector2f operator*(const Vector2f& lhs, float rhs) noexcept {
		return { lhs.X * rhs, lhs.Y * rhs };
	}
	Vector2f operator*(float lhs, const Vector2f& rhs) noexcept {
		return { lhs * rhs.X, lhs * rhs.Y };
	}

	Vector2f operator+(const Vector2& lhs, const Vector2f& rhs) noexcept {
		return { lhs.X + rhs.X, lhs.Y + rhs.Y };
	}
	Vector2f operator+(const Vector2f& lhs, const Vector2& rhs) noexcept {
		return { lhs.X + rhs.X, lhs.Y + rhs.Y };
	}
	Vector2f operator-(const Vector2& lhs, const Vector2f& rhs) noexcept {
		return { lhs.X - rhs.X, lhs.Y - rhs.Y };
	}
	Vector2f operator-(const Vector2f& lhs, const Vector2& rhs) noexcept {
		return { lhs.X - rhs.X, lhs.Y - rhs.Y };
	}
	Vector2f operator*(const Vector2& lhs, float rhs) noexcept {
		return { lhs.X * rhs, lhs.Y * rhs };
	}
	Vector2f operator*(float lhs, const Vector2& rhs) noexcept {
		return { lhs * rhs.X, lhs * rhs.Y };
	}
}

namespace turtle {
	class Window {
	private:
		HWND m_Handle = nullptr;

	public:
		Window() {
			CreateHandle();
		}
		Window(Window&& other) {
			MoveHandle(std::move(other));
		}
		~Window() {
			DestroyWindow(m_Handle);
		}

	public:
		Window& operator=(Window&& other) {
			MoveHandle(std::move(other));
			return *this;
		}

	private:
		static HINSTANCE GetModule() noexcept {
			static HINSTANCE module = GetModuleHandle(nullptr);
			return module;
		}
		static LPCTSTR CreateWindowClass() {
			WNDCLASS wndClass{};
			wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
			wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
			wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
			wndClass.hInstance = GetModule();
			wndClass.lpfnWndProc = WndProcStatic;
			wndClass.lpszClassName = _T("ctWindow");
			wndClass.style = CS_HREDRAW | CS_VREDRAW;

			if (RegisterClass(&wndClass)) return wndClass.lpszClassName;
			else throw std::runtime_error("윈도우 클래스를 생성하지 못했습니다.");
		}
		void CreateHandle() {
			static LPCTSTR className = CreateWindowClass();

			if (!CreateWindowEx(0, className, _T("cppturtle"), WS_OVERLAPPEDWINDOW | WS_VISIBLE,
				CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, nullptr, nullptr, GetModule(), this))
				throw std::runtime_error("윈도우를 생성하지 못했습니다.");
		}
		void MoveHandle(Window&& other) {
			if (CT_WINAPI_SAFELY(SetWindowLongPtr(other.m_Handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)))) {
				DestroyWindow(m_Handle);

				m_Handle = other.m_Handle;
				other.m_Handle = nullptr;
			} else throw std::runtime_error("윈도우를 이동하지 못했습니다.");
		}

		static LRESULT CALLBACK WndProcStatic(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) {
			Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(handle, GWLP_USERDATA));
			if (!window && message == WM_CREATE) {
				CREATESTRUCT* const createStruct = reinterpret_cast<CREATESTRUCT*>(lParam);

				window = reinterpret_cast<Window*>(createStruct->lpCreateParams);
				window->m_Handle = handle;

				if (!CT_WINAPI_SAFELY(SetWindowLongPtr(handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window)))) {
					DestroyWindow(handle);
					throw std::runtime_error("윈도우를 초기화하지 못했습니다.");
				}
			}

			return window ? window->WndProc(message, wParam, lParam) : DefWindowProc(handle, message, wParam, lParam);
		}
		LRESULT WndProc(UINT message, WPARAM wParam, LPARAM lParam) {
			static unsigned windowCount = 0;

			switch (message) {
			case WM_CREATE:
				++windowCount;
				return 0;

			case WM_CLOSE:
				DestroyWindow(m_Handle);
				return 0;

			case WM_DESTROY:
				if (GetWindowLongPtr(m_Handle, GWLP_USERDATA) && --windowCount == 0) {
					PostQuitMessage(0);
				}

				m_Handle = nullptr;
				return 0;

			default:
				return DefWindowProc(m_Handle, message, wParam, lParam);
			}
		}

	public:
		int MainLoop() {
			MSG message;
			BOOL success;
			while (true) {
				success = GetMessage(&message, nullptr, 0, 0);
				if (success == 0) break;
				else if (success == -1) throw std::runtime_error("메세지를 가져오지 못했습니다.");

				TranslateMessage(&message);
				DispatchMessage(&message);
			}

			return message.wParam;
		}
	};
}

#endif