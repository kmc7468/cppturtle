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

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <utility>
#include <vector>

#include <Windows.h>
#include <tchar.h>

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
			return std::sqrtf(static_cast<float>(X) * static_cast<float>(X) +
				static_cast<float>(Y) * static_cast<float>(Y));
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
			: X(static_cast<float>(other.X)), Y(static_cast<float>(other.Y)) {}
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

#define CT_WINAPI_SAFELY(expression) ((SetLastError(0), (expression), GetLastError()) == 0)

#define CT_WM_DESTROY WM_APP + 0

namespace turtle {
	namespace detail {
		struct UserWindowClass {
			UserWindowClass(void generator()) {
				static bool dummy = (generator(), true);
			}
		};

		template<typename T>
		class WindowBuilder {
		private:
			Vector2 m_Location, m_Size;

		public:
			const Vector2& Location() const noexcept {
				return m_Location;
			}
			T& Location(const Vector2& newLocation) noexcept {
				m_Location = newLocation;
				return static_cast<T&>(*this);
			}
			const Vector2& Size() const noexcept {
				return m_Size;
			}
			T& Size(const Vector2& newSize) noexcept {
				m_Size = newSize;
				return static_cast<T&>(*this);
			}
		};

		class Window {
		private:
			HWND m_Handle = nullptr;
			HMENU m_Menu = nullptr;
			WNDPROC m_WndProc = nullptr;
			std::vector<HWND> m_Children;

		public:
			template<typename T>
			Window(HWND parent, LPCTSTR className, LPCTSTR windowName, DWORD style, DWORD exStyle, const WindowBuilder<T>& builder) {
				Window* const parentWrapper = GetWrapper(parent);
				if (parentWrapper) {
					m_Menu = reinterpret_cast<HMENU>(parentWrapper->m_Children.size());
				}

				m_Handle = CreateWindowEx(exStyle, className, windowName, style,
					builder.Location().X, builder.Location().Y, builder.Size().X, builder.Size().Y, parent, m_Menu, GetModule(), nullptr);
				if (!m_Handle) throw std::runtime_error("윈도우를 생성하지 못했습니다.");

				if (!CT_WINAPI_SAFELY(SetWindowLongPtr(m_Handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)))) {
					DestroyWindow(m_Handle);
					throw std::runtime_error("윈도우를 초기화하지 못했습니다.");
				}

				m_WndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(m_Handle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProcStatic)));
				if (!m_WndProc) {
					DestroyWindow(m_Handle);
					throw std::runtime_error("윈도우를 초기화하지 못했습니다.");
				}

				if (parentWrapper) {
					try {
						parentWrapper->m_Children.push_back(m_Handle);
					} catch (...) {
						DestroyWindow(m_Handle);
						throw std::runtime_error("윈도우를 초기화하지 못했습니다.");
					}
				}
			}
			Window(Window&& other) {
				Move(std::move(other));
			}
			virtual ~Window() {
				Destroy();
			}

		public:
			Window& operator=(Window&& other) {
				Move(std::move(other));
				return *this;
			}

		public:
			void Destroy() noexcept {
				SendMessage(m_Handle, CT_WM_DESTROY, 0, 0);

				Window* const parent = GetWrapper(GetParent(m_Handle));
				if (parent) {
					*std::find(parent->m_Children.begin(), parent->m_Children.end(), m_Handle) = nullptr;
				}

				for (auto child : m_Children) {
					if (!child) continue;

					GetWrapper(child)->Destroy();
				}

				SetWindowLongPtr(m_Handle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_WndProc));

				DestroyWindow(m_Handle);

				m_Handle = nullptr;
				m_Menu = nullptr;
				m_WndProc = nullptr;
				m_Children.clear();
			}

		protected:
			static HINSTANCE GetModule() noexcept {
				static HINSTANCE module = GetModuleHandle(nullptr);
				return module;
			}

			HWND GetHandle() const noexcept {
				return m_Handle;
			}
			static Window* GetWrapper(HWND handle) noexcept {
				return reinterpret_cast<Window*>(GetWindowLongPtr(handle, GWLP_USERDATA));
			}

			static LRESULT CALLBACK WndProcStatic(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) {
				return reinterpret_cast<Window*>(GetWindowLongPtr(handle, GWLP_USERDATA))->WndProc(handle, message, wParam, lParam);
			}
			virtual LRESULT WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) {
				return CallWindowProc(m_WndProc, m_Handle, message, wParam, lParam);
			}

		private:
			void Move(Window&& other) {
				if (CT_WINAPI_SAFELY(SetWindowLongPtr(other.m_Handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)))) {
					Destroy();

					std::swap(m_Handle, other.m_Handle);
					std::swap(m_Menu, other.m_Menu);
					std::swap(m_WndProc, other.m_WndProc);
					std::swap(m_Children, other.m_Children);
				} else throw std::runtime_error("윈도우를 이동하지 못했습니다.");
			}
		};
	}

	class MainWindowBuilder final : public detail::WindowBuilder<MainWindowBuilder> {
	public:
		MainWindowBuilder() noexcept {
			Location({ CW_USEDEFAULT, CW_USEDEFAULT });
			Size({ 640, 480 });
		}
	};

	class MainWindow : public detail::UserWindowClass, public detail::Window {
	public:
		MainWindow(const MainWindowBuilder& builder = MainWindowBuilder())
			: UserWindowClass(CreateWindowClass),
			Window(nullptr, _T("ctWindow"), _T("cppturtle"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, builder) {
			++GetWindowCount();
		}
		MainWindow(int width, int height)
			: MainWindow(MainWindowBuilder().Size({ width, height })) {}
		MainWindow(MainWindow&& other) = default;
		virtual ~MainWindow() override = default;

	public:
		MainWindow& operator=(MainWindow&& other) = default;

	protected:
		virtual LRESULT WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam) override {
			switch (message) {
			case WM_CLOSE:
				Destroy();
				return 0;

			case CT_WM_DESTROY:
				if (--GetWindowCount() == 0) {
					PostQuitMessage(0);
				}
				return 0;

			default:
				return Window::WndProc(handle, message, wParam, lParam);
			}
		}

	private:
		static void CreateWindowClass() {
			WNDCLASS wndClass{};
			wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
			wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
			wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
			wndClass.hInstance = GetModule();
			wndClass.lpfnWndProc = DefWindowProc;
			wndClass.lpszClassName = _T("ctWindow");
			wndClass.style = CS_HREDRAW | CS_VREDRAW;

			if (!RegisterClass(&wndClass)) throw std::runtime_error("윈도우 클래스를 생성하지 못했습니다.");
		}
		static unsigned& GetWindowCount() noexcept {
			static unsigned count = 0;
			return count;
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

			return static_cast<int>(message.wParam);
		}
	};
}

#endif